
#include "string_logchecker.h"
#include "console_output.h"

#include <iostream>
using namespace std;

StringLogChecker::StringLogChecker(string logLine) : m_logLine(logLine)
{
    //ctor
}

StringLogChecker::~StringLogChecker()
{
    //dtor
}

void StringLogChecker::printMatchMessage()
{
        using boostMT::cout;
        using boostMT::endl;

        boost::recursive_mutex::scoped_lock lock(cout.get_mutex() );
	cout << "got matching print " << "\"" << m_logLine <<  "\"" << endl;
}
void StringLogChecker::printWaitMessage()
{
        using boostMT::cout;
        using boostMT::endl;

        boost::recursive_mutex::scoped_lock lock(cout.get_mutex() );
	cout << "wait for print "<< "\"" << m_logLine << "\"" << endl;
}
string StringLogChecker::getExpected()
{
	string s = "print \"" + m_logLine + "\"";
	return s;
}


bool StringLogChecker::checkLog(string logLine)
{
    if (logLine == m_logLine )
	{
		return true;
	}
	else
	{
		return false;
	}
}


