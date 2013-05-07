
#include "Results.h"

#include "logchecker.h"
#include <iterator>

Results::Results(void)
{
}

Results::~Results(void)
{
}

Results& Results::operator>>(string& result)
{
	if (m_results.size())
	{
		result = m_results.front();
		m_results.pop_front();
	}
	return *this;
}

Results& Results::operator>>(vector<string>& resultvec)
{
	while (m_results.size())
	{
		resultvec.push_back(m_results.front());
		m_results.pop_front();
	}
	return *this;
}

void Results::setResults(LogCheckerBase* logChecker)
{
	m_results.clear();
	vector<string> matches = logChecker->getMatches();
	copy(matches.begin(),matches.end(), std::back_inserter(m_results));
}