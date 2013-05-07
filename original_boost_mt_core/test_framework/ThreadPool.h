#ifndef BOOSTMT_THREAD_POOL_H_
#define BOOSTMT_THREAD_POOL_H_

#include <boost/function.hpp>
#include <boost/thread/mutex.hpp>
#include <boost/thread.hpp>
#include <boost/shared_ptr.hpp>
#include <queue>
#include <deque>

//! Thread pool implementation for tests
/*! http://en.wikipedia.org/wiki/Thread_pool
 */
class ThreadPool {
public:
    //! Creates thread pool
    /* Threads are ready to work immidiately, no need to start them. Just add task with addTask() method.
     * \param numThreads Number of used threads
     */
    ThreadPool(size_t numThreads);
    ~ThreadPool();

    //! Type for generic task processed by thread pool
    typedef boost::function<void ()> Task;

    //! Queues task in pool.
    /*! When tasks are added threads start to process them immidiately, yet this function is thread-safe
     in regard to thread-pool itself.
     * \param task Task that will be executed by one of threads
     */
    void addTask(Task task);
        
    //! Waits till all queued tasks are processed.
    void waitForCompletion();

protected:
    class ThreadProc;
    struct Holder;
    friend struct Holder; 

    void returnFreeThread(ThreadProc *threadProc);

    ThreadProc *tryGetFreeThread();

private:
    typedef std::queue<Task> Tasks;
    Tasks m_tasks;
    boost::mutex m_tasksMutex;
    boost::thread_group m_threads;
                   
    typedef std::deque<ThreadProc*> FreeThreads;
    FreeThreads m_freeThreads;
    boost::condition_variable m_condAllThreadsFree;
    boost::mutex m_freeThreadsMutex;
    
    FreeThreads m_allThreadProcs;

};

#endif // BOOSTMT_THREAD_POOL_H_