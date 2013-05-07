
#include "substring_logchecker.h"
#include "console_output.h"

#include <iostream>
using namespace std;

SubStringLogChecker::SubStringLogChecker(string logLine) : m_sublog(logLine)
{
    //ctor
}

SubStringLogChecker::~SubStringLogChecker()
{
    //dtor
}

void SubStringLogChecker::printMatchMessage()
{
        using boostMT::cout;
        using boostMT::endl;

        boost::recursive_mutex::scoped_lock lock(cout.get_mutex() );
		cout << "got matching print " << "\"" << m_matched_log <<  "\"" << endl;
}

void SubStringLogChecker::printWaitMessage()
{
        using boostMT::cout;
        using boostMT::endl;

        boost::recursive_mutex::scoped_lock lock(cout.get_mutex() );
		cout << "wait for print containing string "<< "\"" << m_sublog << "\"" << endl;
}

string SubStringLogChecker::getExpected()
{
	string s = "print containing string\"" + m_sublog + "\"";
	return s;
}


bool SubStringLogChecker::checkLog(string logLine)
{
    if ( logLine.find(m_sublog) != string::npos )
	{
		m_matched_log = logLine;
		return true;
	}
	else
	{
		return false;
	}
}


