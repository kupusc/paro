#ifndef __LOG_CHECK_TIMEOUT_H__
#define __LOG_CHECK_TIMEOUT_H__

#include <boost/thread/thread.hpp>
#include <boost/thread/condition.hpp>



namespace boostMT
{
	class LogCheckTimeout
	{
	private:
		LogCheckTimeout() : m_default_timeout(5)
		{
		}
	public:
		static LogCheckTimeout & get_instance()
		{
			static LogCheckTimeout instance;
			return instance;
		}
		boost::posix_time::seconds get_default_timeout()
		{
			return m_default_timeout;
		}
		void set_default_timeout( boost::posix_time::seconds timeout)
		{
			m_default_timeout=timeout;
		}
	private:
		boost::posix_time::seconds m_default_timeout;
	};

};


#define LOG_CHECK_DEFAULT_TIMEOUT ( boostMT::LogCheckTimeout::get_instance().get_default_timeout() )


#endif //__LOG_CHECK_TIMEOUT_H__


