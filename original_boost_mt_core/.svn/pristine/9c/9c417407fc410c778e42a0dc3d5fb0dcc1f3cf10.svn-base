#ifndef __DBG_PRINTS_H__
#define __DBG_PRINTS_H__

#include <list>
#include <string>
#include <vector>
#include <queue>

#include <boost/thread/thread.hpp>
#include <boost/thread/condition.hpp>
#include <boost/thread/recursive_mutex.hpp>

#include <Results.h>
#include "logcheck_timeout.h"

class LogCheckerBase;

using std::string;
using std::list;
using std::vector;


class dbg_prints;

class LogListener 
{
	friend class dbg_prints;
protected:
	virtual void onLog(const std::string &logMessage)=0;

};

class dbg_prints
{
	
private:
	dbg_prints();
   ~dbg_prints();
    void printPrints();
    bool check_log(LogCheckerBase*);
	void check_fail(std::string filename,int line,std::string msg);
	void notifyListeners(const std::string &logMessage); //< thread unsafe
	
public:
   static dbg_prints* instance()
   {
		static dbg_prints instance;
		return &instance;
   }
   vector<string> wait4print(LogCheckerBase*, std::string filename, int line, boost::posix_time::time_duration waitTimeOut = boost::posix_time::seconds(0) );
   void addPrint(string line);
	void clear_buffer();		
   Results getLastResults();
   void addListener(LogListener *listener);
   void removeListener(LogListener *listener);

private:
    boost::recursive_mutex m_mutex;
	boost::condition m_condition;
	std::vector<string> m_log_buffer;
	Results m_lastResults;
	std::map<boost::thread::id , unsigned int > m_log_check_position;
	std::list<LogListener*> m_listeners;
	boost::mutex m_listenersMutex;
	
};






#endif


