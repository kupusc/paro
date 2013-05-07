#ifndef _SUBSTRINGLOGCHECKER_H
#define _SUBSTRINGLOGCHECKER_H

#include "logchecker.h"


class SubStringLogChecker : public LogCheckerBase
{
    public:
        SubStringLogChecker(string logLine);
        virtual ~SubStringLogChecker();
        virtual bool checkLog(string line );
		virtual void printMatchMessage();
		virtual void printWaitMessage();
		virtual string getExpected();
    protected:
    private:
    string m_sublog;
	string m_matched_log;
};

#endif // _SUBSTRINGLOGCHECKER_H
