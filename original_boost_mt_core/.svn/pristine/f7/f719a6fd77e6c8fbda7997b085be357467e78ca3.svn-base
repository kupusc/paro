
#include "list_logchecker.h"

#include <iostream>
#include <sstream>
#include "console_output.h"

using namespace std;

ListLogChecker::ListLogChecker(void)
{
}

ListLogChecker::~ListLogChecker(void)
{
	for (list<LogCheckerBase*>::iterator it = m_waiting.begin();it!= m_waiting.end();++it)
	{
		delete (*it);
	}
	
	for (list<LogCheckerBase*>::iterator it = m_matched.begin();it!= m_matched.end();++it)
	{
		delete *it;
	}
}

ListLogChecker::ListLogChecker(list<LogCheckerBase*> logCheckerList) : m_waiting(logCheckerList)
{
}

bool ListLogChecker::checkLog(string line)
{
	list<LogCheckerBase*>::iterator it = m_waiting.begin();

	while (it!=m_waiting.end())
	{
		if ((*it)->checkLog(line))
		{
			m_matched.push_back(*it);
			it = m_waiting.erase(it);
		}
		else
		{
			it++;
		}
	}
	return m_waiting.empty();
}

void ListLogChecker::addLogChecker(LogCheckerBase* logChecker)
{
	m_waiting.push_back(logChecker);
	m_ordered.push_back(logChecker);
}
void ListLogChecker::printWaitMessage()
{
        using boostMT::cout;
        using boostMT::endl;

        {
                boost::recursive_mutex::scoped_lock lock(cout.get_mutex() );
                cout << ">> waiting for " << m_waiting.size() << " matches: " <<endl;
                for( list<LogCheckerBase *>::iterator it=m_waiting.begin() ; it!=m_waiting.end() ; it++)
                {	
                        cout << ">> \t" ;
                        (*it)->printWaitMessage();
                }
        }        
}
string ListLogChecker::getExpected()
{
	ostringstream ss;
	ss <<  m_waiting.size()<< "/" << m_waiting.size()+ m_matched.size() << " matches: \n" ;
	string s=ss.str();
	for( list<LogCheckerBase *>::iterator it=m_waiting.begin() ; it!=m_waiting.end() ; it++)
	{	
		s+=">> \t";
		s+=(*it)->getExpected();
		s+='\n';
	}
	return s;
}

void ListLogChecker::printMatchMessage()
{
        using boostMT::cout;
        using boostMT::endl;

        {
                boost::recursive_mutex::scoped_lock lock(cout.get_mutex() );
                cout << ">> got " << m_matched.size() << "/" << m_matched.size()+ m_waiting.size() << " matches: " <<endl;
                for( list<LogCheckerBase *>::iterator it=m_matched.begin() ; it!=m_matched.end() ; it++)
                {	
                        cout << ">> \t" ;
                        (*it)->printMatchMessage();
                }
        }        
}

vector<string>& ListLogChecker::getMatches()
{
	m_matches.clear();
	for (vector<LogCheckerBase*>::iterator it = m_ordered.begin(); it!=m_ordered.end();++it)
	{
		copy((*it)->getMatches().begin(),(*it)->getMatches().end(),back_inserter(m_matches));
	}
	
	return m_matches;
}