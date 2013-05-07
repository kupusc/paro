#ifndef __MESSAGE_QUEUE_H__
#define __MESSAGE_QUEUE_H__

#include <iostream>
#include <string>
#include <boost/interprocess/ipc/message_queue.hpp>

// include headers that implement a archive in simple text format
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/scoped_ptr.hpp>


//----------------------------------------------------------------------------

// class for global storage of errorString, returnCode and elapsedTime of the current testcase
class GlobalMessage
{
public:
    std::string   errorString;
    int           returnCode;
    unsigned long elapsedTime;

    //! Send message to TestRunner message queue if queue name has been assigned
    void sendMessageIfQueueAssigned();

    static GlobalMessage &getSingleton() {
        return instance;
    }

    void setQueueName(const std::string &queue_name);

    const std::string &getQueueName() const { return message_queue_name; }

protected:
    //! Send message to TestRunner message queue.
    void sendMessage();

private:
    GlobalMessage():returnCode(0),elapsedTime(0) {}

    std::string message_queue_name;

    static GlobalMessage instance;
};


//----------------------------------------------------------------------------

// serializable class for storage of 1 interprocess message
class InterprocessMessage
{
public:
	InterprocessMessage() :
		m_errorString(""), m_returnCode(0), m_elapsedTime(0) {};
	InterprocessMessage(const std::string& errorStr, int retCode, unsigned long elapsed) :
		m_errorString(errorStr), m_returnCode(retCode), m_elapsedTime(elapsed) {};
	~InterprocessMessage() {};

	std::string    m_errorString;
	int            m_returnCode;
	unsigned long  m_elapsedTime;

private:
	friend class boost::serialization::access;
	
	template<class Archive>
	void serialize(Archive & ar, const unsigned int version)
	{
		ar & m_returnCode & m_elapsedTime & m_errorString;
	}
};


//----------------------------------------------------------------------------

// class for handling interprocess messages
class MessageQueue
{
public:
	MessageQueue(const std::string& name, int maxNumMsg = 1, int maxMsgSize = 256);
	~MessageQueue();
	void create(void);
	void open(void);
	int getNumMsg(void);
	void send(const InterprocessMessage& msg);
	bool receive(InterprocessMessage& msg);

private:
	void send(const char* msg, int size);
	bool receive(char* buffer, size_t& recvd_size);

	std::string m_queueName;
	boost::interprocess::message_queue* m_queue;
	size_t m_maxNumMsg;
	size_t m_maxMsgSize;
};

#endif

