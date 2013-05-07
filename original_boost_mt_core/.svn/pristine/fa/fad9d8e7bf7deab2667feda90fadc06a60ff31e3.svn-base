
#include "WaitFunctions.h"
#include <boost/thread.hpp>
#include <oxf/state.h>
#include <oxf/omreactive.h>
#include <oxf/omthread.h>
#include "os.h"
#include "OXFStatechartMacros.h"
#include "omlist.h"
#include "generic_stub.h"
#include "OMTimerManager.h"
#include "OMThreadManager.h"
#include <deque>
#include <boost/thread/condition_variable.hpp>
#include <boost/thread/mutex.hpp>
#include <boost/interprocess/sync/interprocess_semaphore.hpp>

namespace {

    class Dummy1: public OMEvent
    {
    public:
        Dummy1(boost::interprocess::interprocess_semaphore &notify):mWaitFor(0),mNotify(notify)
        {
        }

        ~Dummy1()
        {
            mNotify.post();
            mWaitFor.wait();
        }

        boost::interprocess::interprocess_semaphore mWaitFor;
        boost::interprocess::interprocess_semaphore &mNotify;

    };

    class Dummy2: public OMEvent
    {

    };

    //Dummy1 dummy1;
    Dummy2 dummy2;
    GenericStub dummyReceiver("dummyReceiver_for_waitForState");

    bool _waitState(OMState *state, boost::posix_time::ptime failAt)
    {
        while(!IS_IN(state))
        {
            if(boost::posix_time::microsec_clock::local_time() >= failAt)
            {
                return false;
            }
            boost::this_thread::yield();
        }
        return true;
    }

    bool _waitNoCurEv(OMReactive *reactive, boost::posix_time::ptime failAt)
    {
        while(reactive->getCurrentEvent())
        {
            if(boost::posix_time::microsec_clock::local_time() >= failAt)
            {
                return false;
            }
            boost::this_thread::yield();
        }
        return true;
    }

}

namespace original_boost_mt_core {

    namespace helpers {

        bool waitForEmptyQueue(OMReactive *reactive, boost::posix_time::time_duration waitFor)
        {
            boost::posix_time::ptime failAt = boost::posix_time::microsec_clock::local_time() + waitFor;

            bool good;
            dummy2.setDestination(&dummyReceiver);
            dummy2.setDeleteAfterConsume(false);

            do
            {
                IOxfActive * const context = reactive->getActiveContext();
                OMThread * const thread = dynamic_cast<OMThread*>(context);
                assert(thread);
                OMList<IOxfEvent*> events;
                const_cast<OMEventQueue*>(thread->getEventQueue())->reserveMessageList(events);
                good = events.isEmpty();

                const_cast<OMEventQueue*>(thread->getEventQueue())->releaseMessageList();

                if(good)
                {
                    boost::interprocess::interprocess_semaphore readyToLockList(0); //dummy1 is being processed, we should lock list
                    Dummy1 *dummy1 = new Dummy1(readyToLockList);
                    dummy1->setDestination(&dummyReceiver);
                    thread->queueEvent(dummy1);
                    thread->queueEvent(&dummy2);

                    readyToLockList.wait();	//wait till OMThread process dummy1 (and tries to destroy it)

                    const_cast<OMEventQueue*>(thread->getEventQueue())->reserveMessageList(events);
                    good = (events.getCount() == 1) && (events.getAt(0) == &dummy2); //it must be processing dummy1
                    const_cast<OMEventQueue*>(thread->getEventQueue())->releaseMessageList();

                    dummy1->mWaitFor.post();

                    if(!good) //someone added to queue, we give some cpu time for OMThread to process it
                    {
                        boost::this_thread::yield();
                    }
                } else
                {
                    boost::this_thread::yield();
                }
            }
            while(!good);

            return true;
        }


        bool waitForState(OMReactive *reactive, OMState *state, boost::posix_time::time_duration waitFor, bool requireEmptyEventQueue)
        {
            boost::posix_time::ptime failAt = boost::posix_time::microsec_clock::local_time() + waitFor;

            bool good;
            dummy2.setDestination(&dummyReceiver);
            dummy2.setDeleteAfterConsume(false);

            do
            {
                if(!_waitState(state, failAt) || !_waitNoCurEv(reactive, failAt))
                {
                    return false;
                }

                IOxfActive * const context = reactive->getActiveContext();
                OMThread * const thread = dynamic_cast<OMThread*>(context);
                assert(thread);
                OMList<IOxfEvent*> events;
                const_cast<OMEventQueue*>(thread->getEventQueue())->reserveMessageList(events);
                good = events.isEmpty() && IS_IN(state) && !reactive->getCurrentEvent();

                const_cast<OMEventQueue*>(thread->getEventQueue())->releaseMessageList();

                if(good && requireEmptyEventQueue)
                {
                    boost::interprocess::interprocess_semaphore readyToLockList(0); //dummy1 is being processed, we should lock list
                    Dummy1 *dummy1 = new Dummy1(readyToLockList);
                    dummy1->setDestination(&dummyReceiver);
                    thread->queueEvent(dummy1);
                    thread->queueEvent(&dummy2);

                    readyToLockList.wait();	//wait till OMThread process dummy1 (and tries to destroy it)

                    const_cast<OMEventQueue*>(thread->getEventQueue())->reserveMessageList(events);
                    good = IS_IN(state) && !reactive->getCurrentEvent();
                    good = good && (events.getCount() == 1) && (events.getAt(0) == &dummy2); //it must be processing dummy1
                    const_cast<OMEventQueue*>(thread->getEventQueue())->releaseMessageList();

                    dummy1->mWaitFor.post();

                    if(!good) //someone added to queue, we give some cpu time for OMThread to process it
                    {
                        boost::this_thread::yield();
                    }
                }

            }
            while(!good && requireEmptyEventQueue);

            return true;
        }

    }

}

namespace {

    class DummyForThreads: public OMEvent
    {
    public:
        DummyForThreads(int &notify, boost::condition_variable &notifyCond, boost::mutex &notifyMutex):mWaitFor(false),
            mNotify(notify),mNotifyCond(notifyCond),mNotifyMutex(notifyMutex)
        {
        }

        ~DummyForThreads()
        {
            {
                boost::lock_guard<boost::mutex> lock(mNotifyMutex);
                --mNotify;

                mNotifyCond.notify_one(); //< intentionally putting it inside lock to prevent destroying when going out of scope in waitForAllThreadsPending
            }

            boost::unique_lock<boost::mutex> lock(mWaitForMutex);
            while(!mWaitFor)
            {
                mWaitForCond.wait(lock);
            }
        }

        volatile bool mWaitFor;
        boost::condition_variable mWaitForCond;
        boost::mutex mWaitForMutex;

        int &mNotify;
        boost::condition_variable &mNotifyCond;
        boost::mutex &mNotifyMutex;

        void stopWaiting()
        {
            boost::lock_guard<boost::mutex> lock(mWaitForMutex);
            mWaitFor = true;

            mWaitForCond.notify_one();  //< intentionally here so we won't delete mWaitForCond before calling notify_one
        }

    };

}

namespace original_boost_mt_core {

    namespace helpers {

        bool waitForAllThreadsPending(boost::posix_time::time_duration waitFor)
        {
            typedef std::vector<OMThread*> Threads;

            boost::posix_time::ptime failAt = boost::posix_time::microsec_clock::local_time() + waitFor;

            OMThreadManager &threadManager = OMThreadManager::instance();

            bool result = false;

            while(boost::posix_time::microsec_clock::local_time() < failAt)
            {
                Threads threads;
                int waitingForDummies(0);
                boost::condition_variable dummiesCond;
                boost::mutex dummiesMutex;

                boost::unique_lock<boost::mutex> lock(dummiesMutex);

                // after we're done, we want to make sure that threads will be left unlocked
                struct NotifyDummies
                {
                    ~NotifyDummies()
                    {
                        std::for_each(mDummies.begin(), mDummies.end(), std::mem_fun(&DummyForThreads::stopWaiting));
                    }
                    std::deque<DummyForThreads*> mDummies;
                } notifyDummies;

                {
                    // prevent creation of threads
                    OMGuard _omGuard(threadManager.getGuard());

                    // all current threads will receive dummy event to lock them its execution
                    for(OMIterator<OMThread*> iThreads = threadManager.getThreads(); *iThreads; ++iThreads)
                    {
                        // First check if thread is properly initialized
                        if ((*iThreads)->getEventQueue()->getOsQueue())
                        {
                            threads.push_back(*iThreads);

                            ++waitingForDummies;
                            DummyForThreads *dummy = new DummyForThreads(waitingForDummies, dummiesCond, dummiesMutex);
                            notifyDummies.mDummies.push_back(dummy);
                            dummy->setDestination(&dummyReceiver);

                            threads.back()->queueEvent(dummy);
                        }
                    }
                }

                // let threads run till all are locked by our dummy event
                while(waitingForDummies > 0)
                {
                    dummiesCond.wait(lock);
                }

                // check if thread list hasn't changed (if we have a new thread, start over)
                {
                    OMGuard _omGuard(threadManager.getGuard());

                    Threads newThreads;
                    for(OMIterator<OMThread*> iThreads = threadManager.getThreads(); *iThreads; ++iThreads)
                    {
                        newThreads.push_back(*iThreads);
                    }

                    if(newThreads != threads)
                    {
                        continue;
                    }

                    //  for each thread check if queue is empty (currently processed event is our dummy)
                    bool nonEmptyQueue = false;
                    for(Threads::iterator iThread = threads.begin(); threads.end() != iThread; ++iThread)
                    {
                        OMList<IOxfEvent*> events;
                        const_cast<OMEventQueue*>((*iThread)->getEventQueue())->reserveMessageList(events);
                        nonEmptyQueue = events.getCount() > 0;
                        const_cast<OMEventQueue*>((*iThread)->getEventQueue())->releaseMessageList();

                        if(nonEmptyQueue)
                        {
                            break;
                        }
                    }

                    if(nonEmptyQueue)
                    {
                        continue;
                    }
                }

                // if all above conditions are fulfilled, exit function
                result = true;
                break;
            }
            return result;
        }

        bool waitForTargetValue(volatile int &current, int targetAtLeast,
            boost::posix_time::time_duration waitFor)
        {
            //spinlock, should be replaced by semaphore of some kind since it can take a while
            boost::posix_time::ptime failAt = boost::posix_time::microsec_clock::local_time() + waitFor;
            while(current < targetAtLeast)
            {
                if(boost::posix_time::microsec_clock::local_time() >= failAt)
                {
                    return false;
                }
                boost::thread::yield();
            }
            return true;
        }

        bool waitForTargetValueEq(volatile int &current, int targetEquals,
            boost::posix_time::time_duration waitFor)
        {
            //spinlock, should be replaced by semaphore of some kind since it can take a while
            boost::posix_time::ptime failAt = boost::posix_time::microsec_clock::local_time() + waitFor;
            while(current != targetEquals)
            {
                if(boost::posix_time::microsec_clock::local_time() >= failAt)
                {
                    return false;
                }
                boost::thread::yield();
            }
            return true;
        }

        bool pendingThreadsTimeForwarder(boost::function<bool()> stop, boost::posix_time::time_duration waitFor)
        {
            boost::posix_time::ptime const failAt = boost::posix_time::microsec_clock::local_time() + waitFor;

            bool result = waitForAllThreadsPending();
            if(!result)
            {
                std::cout << "ERROR: pendingThreadsTimeForwarder: waitForAllThreadsPending failed" << std::endl;
            }

            while(result && (boost::posix_time::microsec_clock::local_time() < failAt))
            {  
                if(stop())
                {
                    break;
                }

                OMTimerManager::instance()->advanceTime();

                result = waitForAllThreadsPending();
                if(!result)
                {
                    std::cout << "ERROR: pendingThreadsTimeForwarder: waitForAllThreadsPending failed" << std::endl;
                }
            }
            return result && (boost::posix_time::microsec_clock::local_time() <= failAt);
        }

        struct BoolStop
        {
            BoolStop(const bool &stop):mStop(stop) {}

            bool operator()()
            {
                return mStop;
            }

            const bool &mStop;
        };

        bool pendingThreadsTimeForwarder(bool &stop, boost::posix_time::time_duration waitFor)
        {
            return pendingThreadsTimeForwarder(BoolStop(stop), waitFor);
        }

    } // helpers

} //original_boost_mt_core
