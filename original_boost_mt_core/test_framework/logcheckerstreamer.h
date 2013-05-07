
#ifndef _LOGCHECKER_STREAMER_H
#define _LOGCHECKER_STREAMER_H

#include <boost/thread/thread.hpp>

#include "string_logchecker.h"
#include "substring_logchecker.h"
#include "list_logchecker.h"
#include <string>

class RegexLogChecker;
class MultiRegexLogChecker;
class DBChangeLogChecker;
class SOAPLogChecker;

typedef RegexLogChecker regex;
typedef MultiRegexLogChecker multiregex;
typedef DBChangeLogChecker dbchange;
typedef SOAPLogChecker soap;
typedef SubStringLogChecker substring;

struct LogCheckResult;

class LogCheckerStreamer
{
	friend struct LogCheckResult;
public:
	LogCheckerStreamer(std::string filename, int line);
	~LogCheckerStreamer(void);

	LogCheckerStreamer& operator<<(const char*);
	LogCheckerStreamer& operator<<(const std::string);
	LogCheckerStreamer& operator<<(boost::posix_time::time_duration);
	LogCheckerStreamer& operator<<(LogCheckerBase*);
	LogCheckerStreamer& operator<<(const StringLogChecker&);
	LogCheckerStreamer& operator<<(const RegexLogChecker&);
	LogCheckerStreamer& operator<<(const MultiRegexLogChecker&);
	LogCheckerStreamer& operator<<(const DBChangeLogChecker&);
	LogCheckerStreamer& operator<<(const SOAPLogChecker&);
	LogCheckerStreamer& operator<<(const SubStringLogChecker&);

	LogCheckerBase* getLogChecker()
	{
		return &m_listLogChecker;
	}
	boost::posix_time::time_duration getTimeout()
	{
		return m_timeout;
	}
	static boost::posix_time::seconds getTimeoutHelper(int seconds=0)
	{
		return boost::posix_time::seconds(seconds);
	}
protected:
	LogCheckerBase::TMatches waitForPrint();

private:
	ListLogChecker m_listLogChecker;
	boost::posix_time::time_duration m_timeout;
	std::string m_filename;
	int m_line;
	bool waitedForPrint;
};

struct LogCheckResult {
public:
	LogCheckerBase::TMatches mResults;
public:
	LogCheckResult() {}
	LogCheckResult(const LogCheckResult &other):mResults(other.mResults) {}
	LogCheckResult(LogCheckerStreamer &lcs) {
		mResults = lcs.waitForPrint();
	}
	LogCheckResult &operator=(LogCheckerStreamer &lcs) {
		mResults = lcs.waitForPrint();
		return *this;
	}

	LogCheckResult &operator=(const LogCheckResult &other) {
		mResults = other.mResults;
		return *this;
	}
};


#endif //_LOGCHECKER_STREAMER_H
