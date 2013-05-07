#ifndef LOGCHECKER_H
#define LOGCHECKER_H

#include <list>
#include <vector>
#include <string>

using std::string;
using std::list;
using std::vector;


class LogCheckerBase
{
public: 
	typedef /*vector<std::pair<string, boost::posix_time::time_duration> >*/std::vector<std::string> TMatches;
    public:
        virtual bool checkLog(string line) =0;
		virtual void printMatchMessage() = 0;
		virtual void printWaitMessage() =0;
		virtual string getExpected() =0;
		virtual TMatches& getMatches();
		virtual ~LogCheckerBase();
	protected:
        LogCheckerBase();
	    
		TMatches m_matches;
    private:

};

#endif // LOGCHECKER_H
