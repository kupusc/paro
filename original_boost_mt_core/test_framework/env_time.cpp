#include "env_time.h"
#include "OMTimerManager.h"
#include <boost/date_time/posix_time/posix_time_types.hpp>
#include "logformatting.h"

namespace boostMT
{


	void EnvTime::register_thread(boost::thread::id id )
	{
		boost::mutex::scoped_lock lock(m_mutex);
		std::map<boost::thread::id, thread_state>::iterator it=m_threads.find (id);
		assert(m_threads.end() == it);
		m_threads[id]=thread_running;
	}

	void EnvTime::unregister_thread(boost::thread::id id )
	{
		boost::mutex::scoped_lock lock(m_mutex);

		std::map<boost::thread::id, thread_state>::iterator it=m_threads.find (id);
		assert(it!=m_threads.end() );
		assert( m_threads[id] == thread_running  );

		m_threads.erase(it);

		if ( get_running_thread_count() == 0 &&  m_forward_requests.size() > 0)
		{
			forward_next_time();
		}
	}

	
		struct running_threads
		{
		bool operator() ( std::pair<boost::thread::id, EnvTime::thread_state>  p )
			{
				return  p.second == EnvTime::thread_running ; 	
			}
		};
	int EnvTime::get_running_thread_count()
	{

		//count_if(	m_threads.begin() , m_threads.end(), boost::bind(  &std::pair<boost::thread::id, thread_state>::second  , _1  ) == thread_running ); 
		return count_if(	m_threads.begin() , m_threads.end(), running_threads() ); 
	}

	void EnvTime::forward_time(boost::posix_time::time_duration time, boost::thread::id id )
	{
		boost::mutex::scoped_lock lock(m_mutex);
		
		assert( m_threads.find(id) != m_threads.end() );
		assert( m_threads[id] == thread_running  );
	
		boost::posix_time::time_duration wake_time = m_env_current_time + time;
		m_forward_requests.insert(wake_time );
		
		m_threadsTimes[id] = wake_time;
		m_threads[id] = thread_idle;
		
		if ( get_running_thread_count() == 0 ) //cause we set possibly the last one to idle
		{

				forward_next_time();					
		}
		
		while( m_env_current_time < wake_time)
		{
			m_condition.wait(lock);
		}
		//m_threads[id] = thread_running;
		assert(m_threads[id] == thread_running);
		assert( m_env_current_time == wake_time );
		
	}

	
	void EnvTime::forward_next_time( )
	{
		assert( m_forward_requests.size() > 0 );

		boost::posix_time::time_duration next_time = *m_forward_requests.begin();
		m_forward_requests.erase ( m_forward_requests.begin() );

		assert( m_env_current_time <= next_time );
		boost::posix_time::time_duration dt = next_time - m_env_current_time;

		m_env_current_time = next_time;
		forward_time_by(  dt.total_milliseconds()  );

		for(Tm_threadsTimes::iterator i = m_threadsTimes.begin(); i != m_threadsTimes.end(); ) 
		{
			if(i->second == next_time) 
			{
				m_threads[i->first] = thread_running;
				m_threadsTimes.erase(i++);
			}
			else
			{
				++i;
			} 

		}
		
		m_condition.notify_all();	
	
		std::ostringstream os;
		os << ">> " << "current environment time is " << to_simple_string(m_env_current_time) 
			<< ". Time was forwarded by " <<  to_simple_string(dt) ;
		
		boost::recursive_mutex::scoped_lock lock2(boostMT::cout.get_mutex() );
		boostMT::cout << os.str() << boostMT::endl;
	}
	
	
    void forward_time_by(long long milliseconds) 
    {
        OMTimerManager::instance()->consumeTime(static_cast<OxfTimeUnit>(milliseconds)); //forward time by miliseconds
    }

    std::string getElapsedTime()
    {
        using namespace boost::posix_time;
        // timer manager can be null on startup and on shutdown (i.e. by thread safer termination)
        OMTimerManager *timerManager = OMTimerManager::instance();
        time_duration elapsedTime;
        if (timerManager)
        {
            elapsedTime = milliseconds(OMTimerManager::instance()->getElapsedTime());
        }
        std::string result = boostMT::formatTime(elapsedTime);
        return result;
    }
	
}
