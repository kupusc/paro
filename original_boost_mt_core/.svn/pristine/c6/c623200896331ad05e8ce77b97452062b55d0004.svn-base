
#ifndef REGEXLOGCHECKER_H
#define REGEXLOGCHECKER_H

#include <boost/regex.hpp>
#include "logchecker.h"


class RegexLogChecker : public LogCheckerBase
{
    public:
        RegexLogChecker(string stringRegex, bool fullLineMatch=false);
		RegexLogChecker(boost::regex regex, bool fullLineMatch=false);
        virtual ~RegexLogChecker();

        virtual bool checkLog(string line);
		virtual void printMatchMessage();
		virtual void printWaitMessage();
		virtual string getExpected();
    protected:
    boost::regex m_regex;
    bool m_fullMatch;
};

#endif // REGEXLOGCHECKER_H
