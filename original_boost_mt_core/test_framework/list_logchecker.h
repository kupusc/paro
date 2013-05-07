
#ifndef _LIST_LOGCHECKER_H
#define _LIST_LOGCHECKER_H

#include "logchecker.h"

class ListLogChecker :
	public LogCheckerBase
{
public:
	ListLogChecker(list<LogCheckerBase*> logCheckerList);
	ListLogChecker(void);
	~ListLogChecker(void);

	virtual bool checkLog(string line);
	virtual void printMatchMessage();
	virtual void printWaitMessage();
	void addLogChecker(LogCheckerBase* logChecker);
	virtual string getExpected();
	virtual vector<string>& getMatches();
private:
	list<LogCheckerBase*> m_waiting;
	list<LogCheckerBase*> m_matched;
	vector<LogCheckerBase*> m_ordered;
};


#endif //_LIST_LOGCHECKER_H