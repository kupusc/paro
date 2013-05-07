#ifndef STRINGLOGCHECKER_H
#define STRINGLOGCHECKER_H

#include "logchecker.h"


class StringLogChecker : public LogCheckerBase
{
    public:
        StringLogChecker(string logLine);
        virtual ~StringLogChecker();
        virtual bool checkLog(string line );
		virtual void printMatchMessage();
		virtual void printWaitMessage();
		virtual string getExpected();
    protected:
    private:
    string m_logLine;
};

#endif // STRINGLOGCHECKER_H
