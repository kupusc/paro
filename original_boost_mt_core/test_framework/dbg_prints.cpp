
#include <cstdarg>
#include <cstdlib>
#include <iostream>

#include "dbg_prints.h"
#include "logchecker.h"
#include "print_writer.h"
#include "log_barrier.h"
#include "console_output.h"  
#include "env_time.h"
#include "CrashHandler.h"
#include "MessageQueue.h"
#include <boost/date_time/posix_time/posix_time_types.hpp>
#include "logformatting.h"

using namespace std;


dbg_prints::~dbg_prints()
{
}


dbg_prints::dbg_prints() 
{
}

void dbg_prints::clear_buffer()
{
	boost::recursive_mutex::scoped_lock lock(m_mutex);

	m_log_buffer.clear();
	m_log_check_position.clear();

}


bool dbg_prints::check_log(LogCheckerBase* log_checker)
{
	boost::thread::id thread_id = boost::this_thread::get_id();
	std::string & log =   m_log_buffer[ m_log_check_position[thread_id] ]  ;
	m_log_check_position[thread_id]++;

	if ( log_checker->checkLog(log) )
	{
		// log_checker->printMatchMessage();
		m_lastResults.setResults(log_checker);
		return true;
	}
	return false;
}

LogCheckerBase::TMatches dbg_prints::wait4print(LogCheckerBase* logChecker, std::string filename, int line, boost::posix_time::time_duration wait_time )
{
	assert(logChecker);

	// logChecker->printWaitMessage();
	boost::thread::id thread_id = boost::this_thread::get_id();
	boost::recursive_mutex::scoped_lock lock(m_mutex);

	if (wait_time == boost::posix_time::seconds(0)) 
	{
		wait_time =  boostMT::LogCheckTimeout::get_instance().get_default_timeout() ;
	}

	boost::system_time const expire_time = boost::get_system_time() + wait_time;

	while (true)
	{
		while ( m_log_check_position[thread_id] < m_log_buffer.size() )
		{
			if (check_log(logChecker)) 
			{
				return logChecker->getMatches();
			}
		}
		if (!m_condition.timed_wait(lock,expire_time))
		{
			check_fail(filename,line,">> Timeout (" + boost::lexical_cast<string>(wait_time.total_seconds() ) + " seconds) while waiting for " + logChecker->getExpected() );
		}
	} 
	return logChecker->getMatches();
}

void dbg_prints::addPrint(string line)
{
    using namespace boost::posix_time;
    static ptime testStartupTime = microsec_clock::universal_time();
    ptime currentTime = microsec_clock::universal_time();
    std::string currentRealTime = boostMT::formatTime(time_duration(currentTime - testStartupTime));

    std::ostringstream os;
    os << boost::this_thread::get_id();
    std::string currentEnvTime = boostMT::getElapsedTime();
    std::string full(currentRealTime + " <" + currentEnvTime + "> " + os.str() + " " + line) ;

    //remove trailing '\n' // make dbg_prints("ala\nma\nkota") split to 3 separte lines?
    size_t pos=full.find('\n');
    if ( pos == (full.size()-1))
    {
        full.erase(pos ,1);
    }
    {
        boost::recursive_mutex::scoped_lock lock(m_mutex);
        Print_writer::get_instance()->write(full);
        m_log_buffer.push_back(full);
    }
    m_condition.notify_all();

    notifyListeners(full);

    LogBarrierManager::get_instance().pass_barriers(full);
}

Results dbg_prints::getLastResults()
{
    return m_lastResults;
}

void dbg_prints::addListener(LogListener *listener) 
{
	boost::mutex::scoped_lock lock(m_listenersMutex);
	m_listeners.push_back(listener);
};

void dbg_prints::removeListener(LogListener *listener) {
	boost::mutex::scoped_lock lock(m_listenersMutex);
	m_listeners.remove(listener);
}

void dbg_prints::check_fail(std::string filename,int line,std::string msg)
{
	using boostMT::cout;
	using boostMT::endl;
	
	{
		boost::recursive_mutex::scoped_lock lock(cout.get_mutex() );
		ostringstream errorStream;
		errorStream << "LOG_CHECK_FAILED file: " << filename << " line: " << line;
		cout << msg ;	
		cout << endl << errorStream.str() << endl << endl;
				
		// store error string in GlobalMessage
		GlobalMessage::getSingleton().errorString = errorStream.str();
		
		// save return code and send result to TestRunner message queue
		GlobalMessage::getSingleton().returnCode = 201;
		GlobalMessage::getSingleton().sendMessageIfQueueAssigned();
	}
	//TODO: this is a lame solution
#ifdef _WIN32
	CrashHandler::getInstance()->setCatchesExceptions(false);
#endif
	
	abort();


}

void dbg_prints::notifyListeners(const std::string &logMessage) 
{
	vector<LogListener*> tmpListeners;
	{
		boost::mutex::scoped_lock lock(m_listenersMutex);
		for(std::list<LogListener*>::iterator i = m_listeners.begin(); i != m_listeners.end(); ++i)
			tmpListeners.push_back(*i);
	}

	for(std::vector<LogListener*>::iterator i = tmpListeners.begin(); i != tmpListeners.end(); ++i) {
		(*i)->onLog(logMessage);
	}
}

