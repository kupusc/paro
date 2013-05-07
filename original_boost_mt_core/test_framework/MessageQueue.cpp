#include "MessageQueue.h"
#include "TestRunner.h"

using namespace boost::interprocess;
using namespace std;


//------ Class GlobalMessage -------------------------------------------------

GlobalMessage GlobalMessage::instance;

void GlobalMessage::setQueueName(const std::string &queue_name)
{
    message_queue_name = queue_name;    
}

void GlobalMessage::sendMessageIfQueueAssigned()
{
    if(!message_queue_name.empty())
    {
        sendMessage();
    }
}

void GlobalMessage::sendMessage(void)
{
    assert(!message_queue_name.empty());

    InterprocessMessage msg(errorString, returnCode, elapsedTime);
    MessageQueue mq(message_queue_name);
    mq.open();
    mq.send(msg);
}


//------ Class MessageQueue --------------------------------------------------

// Constructor
MessageQueue::MessageQueue(const string& name, int maxNumMsg, int maxMsgSize)
{
    m_queueName = name;
    m_maxNumMsg = maxNumMsg;
    m_maxMsgSize = maxMsgSize;
    m_queue = NULL;
}

// Destructor
MessageQueue::~MessageQueue()
{
    if (m_queue)
    {
        delete m_queue;
    }
}

// Create a process shared message queue with name 'm_name'
void MessageQueue::create(void)
{
    try
    {
        message_queue::remove(m_queueName.c_str());
        m_queue = new message_queue(create_only, m_queueName.c_str(), m_maxNumMsg, m_maxMsgSize);
    }
    catch(interprocess_exception &ex)
    {
        std::cout << "Exception in MessageQueue::create(): " << ex.what() << "\" while creating queue named: \"" << m_queueName << "\"" << std::endl;
    }
    //assert(m_queue);
}

// Open a previously created process shared message queue with name 'm_name'
void MessageQueue::open(void)
{
    try
    {
        m_queue = new message_queue(open_only, m_queueName.c_str());
    }
    catch(interprocess_exception &ex)
    {
        std::cout << "Exception in MessageQueue::open(): \"" << ex.what() << "\" while opening queue named: \"" << m_queueName << "\"" << std::endl;
    }
    //assert(m_queue);
}

// get number of messages in message queue
int MessageQueue::getNumMsg(void)
{
    if (m_queue)
    {
        return m_queue->get_num_msg();
    }
    return 0;
}

// send a message to the process shared message queue previously created or openend
void MessageQueue::send(const InterprocessMessage& msg)
{
    ostringstream oss;
    boost::archive::text_oarchive outArchive(oss);  // open the archive
    outArchive << msg;                              // write class instance to archive

    // message length must not exceed the max. msg size
    std::size_t msgSize = (oss.str().size() > m_maxMsgSize) ? m_maxMsgSize : oss.str().size();

    send(oss.str().data(), msgSize);
    // archive and stream closed when destructors are called
}

// receive a message from the process shared message queue previously created or openend
bool MessageQueue::receive(InterprocessMessage& msg)
{
    char* buffer = new char[m_maxMsgSize];
    size_t receivedSize;

    bool ret = receive(buffer, receivedSize);
    if (ret)
    {
        std::istringstream iss(string(buffer, receivedSize));
        boost::archive::text_iarchive inArchive(iss);  // open the archive
        inArchive >> msg;                              // restore the message from the archive
    }

    delete[] buffer;
    return ret;
}


// private method to send a message to the process shared message queue previously created or openend
void MessageQueue::send(const char* msg, int size)
{
    if (m_queue)
    {
        try
        {
            m_queue->try_send(msg, size, 0); // return value ignored
        }
        catch(interprocess_exception &ex)
        {
            std::cout << "Exception in MessageQueue::send(): " << ex.what() << "\" while sending to queue named: \"" << m_queueName << "\"" << std::endl;
        }
    }
}

// private method to receive a message from the process shared message queue previously created or openend
bool MessageQueue::receive(char* buffer, size_t& recvd_size)
{
    bool ret = false;

    if (m_queue)
    {
        try
        {
            unsigned int priority;
            ret = m_queue->try_receive(buffer, m_maxMsgSize, recvd_size, priority);
        }
        catch(interprocess_exception &ex)
        {
            std::cout << "Exception in MessageQueue::receive(): " << ex.what() << "\" while sending to queue named: \"" << m_queueName << "\"" << std::endl;
            ret = false;
        }
    }

    return ret;
}
