#ifndef __RESULTS_H__
#define __RESULTS_H__

#include <vector>
#include <string>
#include <list>

class LogCheckerBase;

using std::vector;
using std::string;
using std::list;

class Results
{
public:

	Results& operator>> (string&);
	Results& operator>> (vector<string>&);
	void setResults(LogCheckerBase*);
	static Results& getInstance()
	{
		return m_instance;
	}
	Results(void);
	~Results(void);

private:
	list<string> m_results;
	static Results& m_instance;
};


#endif //__RESULTS_H__