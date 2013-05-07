#ifndef _WAIT_FUNCTIONS_77056A87_D319_423A_8789_2DB5ED9FB384_H_
#define _WAIT_FUNCTIONS_77056A87_D319_423A_8789_2DB5ED9FB384_H_

#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/function.hpp>

class OMReactive;
class OMState;

namespace original_boost_mt_core {

    namespace helpers {

        //! Waits till OMReactive has finnished processing it's events on queue.
        /*! You should use it this way:
        * BOOST_REQUIRE(waitForEmptyQueue(someOMRInstance));
        * This function isn't intended to validate test results - it's only for synchronization. It has timeout just
        so MT won't be blocked if something goes really wrong.
        * Note this is more white box than waitForState - here no knowledge is required on what states statechart has.
        * \param reactive OMReactive instance        
        * \return True if current = targetAtLeast, false if timeout occured
        */
        bool waitForEmptyQueue(OMReactive *reactive, boost::posix_time::time_duration waitFor = boost::posix_time::seconds(60));

        //! Waits till OMReactive is in state and optionally has nothing on queue
        /*! You should use it this way:
        * BOOST_REQUIRE(waitForState(someInstance, someInstance->stSomeState));
        * This function isn't intended to validate test results - it's only for synchronization. It has timeout just
        so MT won't be blocked if something goes really wrong.
        * \param reactive OMReactive instance
        * \param state State in that instance
        * \param waitFor Timeout after which function will fail (by default 60s)
        * \param requireEmptyEventQueue If true event queue of its thread must be empty for function to succeed (by default true)
        * \return True if current = targetAtLeast, false if timeout occured
        * \sa waitForEmptyQueue
        */
        bool waitForState(OMReactive *reactive, OMState *state, boost::posix_time::time_duration waitFor = boost::posix_time::milliseconds(60000), bool requireEmptyEventQueue = true);

        //! Waits till all OMThreads don't process events and their event queues are empty
        /*! This should be last resort, if possible use waitForState.
        * This function isn't intended to validate test results - it's only for synchronization. It has timeout just
        so MT won't be blocked if something goes really wrong.
        * At the time of writting this is a safest way to ensure correctly written statechart terminates at the end of test.
        * \warning This function is still experimental
        * \warning This function should work on assumption that threads are not destroyed (new ones can be created)
        * \sa waitForState
        */
        bool waitForAllThreadsPending(boost::posix_time::time_duration waitFor = boost::posix_time::milliseconds(60000));

        //! Waits till current >= targetAtLeast or timeout occurs
        /*! You should use it this way:
        * BOOST_REQUIRE(waitForTargetValue(someInstance->variable, 5));
        * But it is best to not use it at all, use condition variables when possible or waitForState.
        * \param current Simple value that changes
        * \param targetAtLeast Constant value that is a target of current
        * \param waitFor Timeout after which function will fail (by default 5s)
        * \return True if current = targetAtLeast, false if timeout occured
        * \sa waitForState
        */
        bool waitForTargetValue(volatile int &current, int targetAtLeast, 
            boost::posix_time::time_duration waitFor = boost::posix_time::milliseconds(5000));

        //! Waits till current == targetAtLeast or timeout occurs
        /*! You should use it this way:
        * BOOST_REQUIRE(waitForTargetValueEq(someInstance->variable, 5));
        * But it is best to not use it at all, use condition variables when possible or waitForState.
        * \param current Simple value that changes
        * \param targetEquals Constant value that is a target of current
        * \param waitFor Timeout after which function will fail (by default 5s)
        * \return True if current = targetAtLeast, false if timeout occured
        * \sa waitForState
        */	
        bool waitForTargetValueEq(volatile int &current, int targetEquals, 
            boost::posix_time::time_duration waitFor = boost::posix_time::milliseconds(5000));

        //! Waits till predicate is fullfilled forwarding time when all threads are pending.
        /*! This function isn't yet well tested - it's best to not use it unless absolutely necessary.
        * Uses waitForAllThreadsPending to know when it's ok to forward time. On exit threads are pending (if true was returned).
        * Should be used like this:
        *   BOOST_REQUIRE(pendingThreadsTimeForwarder(finished));
        * Note that under normal circumstances it shouldn't fail because of timeout - that should indicate badly written test and not
        an usual test failure. In other words, it shoudn't be used for test validation, but only as a helper for white box tests.
        * \param stop Waits till this is true
        * \param waitFor After this time function will fail returning false
        * \return True on success (predicate returned true), false on timeout or other errors
        * \sa waitForAllThreadsPending
        * @{
        */
        bool pendingThreadsTimeForwarder(boost::function<bool()> stop, boost::posix_time::time_duration waitFor = boost::posix_time::minutes(1));
        bool pendingThreadsTimeForwarder(bool &stop, boost::posix_time::time_duration waitFor = boost::posix_time::minutes(1));
        /* @} */

    } //helpers

} //original_boost_mt_core     

#endif //_WAIT_FUNCTIONS_77056A87_D319_423A_8789_2DB5ED9FB384_H_
