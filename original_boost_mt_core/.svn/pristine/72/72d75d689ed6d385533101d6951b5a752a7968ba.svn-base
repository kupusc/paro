#ifndef __ENV_TIME_H__
#define __ENV_TIME_H__

#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/thread/thread.hpp>
#include <boost/thread/condition.hpp>

#include <set>

#include "console_output.h"


namespace boostMT
{


    /**
     * @brief Forwards time in OMTimerManager (OXF) by a given number of milliseconds
     *
     * @param milliseconds time in milliseconds
     */
    void forward_time_by(long long milliseconds);

    /**
     * @brief Returns elapsed time in print format
     *
     * @return Elasped time 
     */
    std::string getElapsedTime();


#define FORWARD_ENV_TIME(x) boostMT::EnvTime::get_instance().forward_time(x, boost::this_thread::get_id())

#define ENV_TIME_REGISTER_THREAD(x) boostMT::EnvTime::get_instance().register_thread(x)

#define ENV_TIME_UNREGISTER_THREAD(x) boostMT::EnvTime::get_instance().unregister_thread(x)



class EnvTime
{
public: 
    enum thread_state
    {
        thread_idle,
        thread_running
    
    };

public:
    EnvTime() : m_env_current_time(0,0,0,0)
    {
    
    }

    void register_thread(boost::thread::id id );

    void unregister_thread(boost::thread::id id );

    static EnvTime & get_instance()
    {
        static EnvTime instance;
        return instance;
    }
    
    boost::posix_time::time_duration get_current_time()
    {
        boost::mutex::scoped_lock lock(m_mutex);
        return m_env_current_time;
    }
    
    void forward_time(boost::posix_time::time_duration time, boost::thread::id id ) ;

private:    
    
    void forward_next_time( ) ;
    
private:
    int get_running_thread_count() ;
    
private:    
    std::set<boost::posix_time::time_duration>  m_forward_requests;
    std::map<boost::thread::id, thread_state> m_threads;
    typedef std::map<boost::thread::id, boost::posix_time::time_duration> Tm_threadsTimes;
    Tm_threadsTimes m_threadsTimes;
    boost::posix_time::time_duration m_env_current_time;
    boost::mutex m_mutex;
    boost::condition m_condition;
};







}

#endif // __ENV_TIME_H__


