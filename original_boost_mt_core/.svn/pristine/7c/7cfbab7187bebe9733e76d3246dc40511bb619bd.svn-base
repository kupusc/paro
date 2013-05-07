
#include <ThreadPool.h>
#include <assert.h>
#include <functional>
#include <boost/bind.hpp>
#include <boost/shared_ptr.hpp>

// -------------------------------- ThreadPool::ThreadProc -----------------------------------

class ThreadPool::ThreadProc {
public:
    ThreadProc(ThreadPool &pool):m_pool(pool),m_die(false),m_task(0) {}

    void setTask(ThreadPool::Task task) 
    {
        {
            boost::lock_guard<boost::mutex> lock(m_taskMutex);
            m_task = task;
        }
        m_condTask.notify_all();        
    }

    void notifyDie() 
    {
        {
            boost::lock_guard<boost::mutex> lock(m_taskMutex); 
            m_die = true;
        }
        m_condTask.notify_all();
    }

    void operator()()
    {
        while(true)
        {
            {
                boost::unique_lock<boost::mutex> lock(m_taskMutex);
                while(!m_die && !m_task)
                {
                    m_condTask.wait(lock);
                }
            
                if(m_die)
                {
                    break;
                }

                m_task();
                m_task.clear();
            }

            m_pool.returnFreeThread(this);
        }
        
    }

private:
    ThreadPool &m_pool;
    bool m_die;
    ThreadPool::Task m_task;
    boost::mutex m_taskMutex;
    boost::condition_variable m_condTask;

};

// -------------------------------- ThreadPool::Holder -----------------------------------

struct ThreadPool::Holder {
    Holder(boost::shared_ptr<ThreadPool::ThreadProc> proc):m_proc(proc) {}

    void operator()()
    {
        (*m_proc)();
    }
    boost::shared_ptr<ThreadPool::ThreadProc> m_proc;
};

// -------------------------------- ThreadPool -----------------------------------

ThreadPool::ThreadPool(size_t numThreads)
{
    assert(numThreads > 0);
    for(size_t i = 0; i < numThreads; ++i)
    {
        boost::shared_ptr<ThreadPool::ThreadProc> proc(new ThreadProc(*this));
        m_freeThreads.push_back(proc.get());
        m_allThreadProcs.push_back(proc.get());
        m_threads.create_thread(Holder(proc));
    }
}

ThreadPool::~ThreadPool()
{
    waitForCompletion();
    
    std::for_each(m_allThreadProcs.begin(), m_allThreadProcs.end(), boost::bind(&ThreadProc::notifyDie, _1));    

    m_threads.join_all();
}

void ThreadPool::addTask(Task task) 
{
    if(ThreadProc *proc = tryGetFreeThread())
    {
        proc->setTask(task);
    } else
    {
        boost::mutex::scoped_lock guard(m_tasksMutex);

        m_tasks.push(task);
    }
}

void ThreadPool::waitForCompletion()
{
    boost::unique_lock<boost::mutex> lock(m_freeThreadsMutex);

    while(m_threads.size() > m_freeThreads.size())
    {
        m_condAllThreadsFree.wait(lock);
    }
}

void ThreadPool::returnFreeThread(ThreadProc *threadProc)
{
    boost::mutex::scoped_lock guard(m_tasksMutex);

    if(!m_tasks.empty())
    {
        threadProc->setTask(m_tasks.front());
        m_tasks.pop();
    } else
    {
        {
            boost::mutex::scoped_lock guard(m_freeThreadsMutex);

            m_freeThreads.push_back(threadProc);
        }

        m_condAllThreadsFree.notify_all();
    }    
}

ThreadPool::ThreadProc *ThreadPool::tryGetFreeThread() 
{
    boost::mutex::scoped_lock guard(m_freeThreadsMutex);

    ThreadProc *result(NULL);
    if(!m_freeThreads.empty())
    {
        result = m_freeThreads.back();
        m_freeThreads.pop_back();
    }
    return result;
}