

#include "regex_logchecker.h"
#include <iostream>
#include "console_output.h"

using namespace std;


 RegexLogChecker::~RegexLogChecker()
{

}


 RegexLogChecker::RegexLogChecker(string regex, bool fullLineMatch) : m_regex(regex), m_fullMatch(fullLineMatch)
{

}

 RegexLogChecker::RegexLogChecker(boost::regex regex, bool fullLineMatch) : m_regex(regex), m_fullMatch(fullLineMatch)
{

}

void RegexLogChecker::printMatchMessage()
{
        using boostMT::cout;
        using boostMT::endl;

        boost::recursive_mutex::scoped_lock lock(cout.get_mutex() );
        cout << "got matching print " << "\"" << m_matches[0] <<  "\"" << endl;
}
void RegexLogChecker::printWaitMessage()
{
        using boostMT::cout;
        using boostMT::endl;

        boost::recursive_mutex::scoped_lock lock(cout.get_mutex() );
        cout << "wait for print matching regex "<< "\"" << m_regex << "\"" << endl;
}
string RegexLogChecker::getExpected()
{
	string s = "print matching regex \"" + m_regex.str() + "\"";
	return s;
}


bool RegexLogChecker::checkLog(string logLine)
{
    boost::smatch matches;
    if (boost::regex_search(logLine,matches,m_regex))
    {
        //cout <<"match:>" << matches[0] <<"<"<<endl;
		if (!m_fullMatch || logLine == matches[0])
		{
			m_matches = vector<string>(matches.begin(),matches.end());
			return true;
		}       
    }
    return false;
}



