#ifndef DBCHANGE_LOGCHECKER_H
#define DBCHANGE_LOGCHECKER_H

#include <map>
#include "logchecker.h"

class DBChangeLogChecker : public LogCheckerBase
{
	public:
		DBChangeLogChecker(std::map<string, string> params);
		DBChangeLogChecker(string params);
		DBChangeLogChecker(string type, std::map<string, string> params);
		DBChangeLogChecker(string type, string params);
		virtual ~DBChangeLogChecker();

		virtual bool checkLog(string line);
		virtual void printMatchMessage();
		virtual void printWaitMessage();
		virtual string getExpected();
	private:
		std::map<string, string> m_params;
		string m_dbchange;
		string m_type;
		std::map<string, string> parseParams(string params);
};

#endif