
#ifndef _MULTI_REGEXLOGCHECKER_H
#define _MULTI_REGEXLOGCHECKER_H

#include "regex_logchecker.h"

class MultiRegexLogChecker :
	public RegexLogChecker
{
public:
	MultiRegexLogChecker(string regex, bool fullLineMatch=false);
	virtual bool checkLog(string line);
	virtual void printWaitMessage();
	virtual string getExpected();
	~MultiRegexLogChecker(void);
private:
	string m_joinedLogs;
};

#endif //_MULTI_REGEXLOGCHECKER_H