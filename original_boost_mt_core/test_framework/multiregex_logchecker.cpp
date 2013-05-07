

#include "multiregex_logchecker.h"

#include <boost/tokenizer.hpp>
#include <iostream>
#include "console_output.h"

using namespace std;

MultiRegexLogChecker::MultiRegexLogChecker(string regex, bool fullLineMatch) : RegexLogChecker(regex,fullLineMatch)
{
}

MultiRegexLogChecker::~MultiRegexLogChecker(void)
{
}
bool MultiRegexLogChecker::checkLog(string line)
{
	m_joinedLogs += line;
	//cout <<endl << m_joinedLogs <<endl;
	return RegexLogChecker::checkLog(m_joinedLogs);
}

void MultiRegexLogChecker::printWaitMessage()
{
        using boostMT::cout;
        using boostMT::endl;

        boost::recursive_mutex::scoped_lock lock(cout.get_mutex() );
	cout << "wait for multiline print matching regex "<< "\"" << m_regex << "\"" << endl;
}
string MultiRegexLogChecker::getExpected()
{
	string s = "multiline print matching regex \"" + m_regex.str() + "\"";
	return s;
}
