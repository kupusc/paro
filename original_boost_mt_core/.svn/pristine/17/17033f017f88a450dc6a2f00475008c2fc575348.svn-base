#include "dbchange_logchecker.h"
#include <iostream>
#include <boost/regex.hpp>
#include <boost/tokenizer.hpp>
#include "console_output.h"

using namespace std;
using namespace boost;

namespace {
ostream& operator<<(ostream& o, const map<string, string> m)
{
	map<string, string>::const_iterator it = m.begin();
	if (it != m.end())
	{
		o << it->first << "=" << it->second;
		it++;
		while (it != m.end())
		{
			o << ";" << it->first << "=" << it->second;
			it++;
		}
	}
	return o;
}
}

DBChangeLogChecker::DBChangeLogChecker(map<string, string> params) : m_type("\\w+"), m_params(params)
{
}

DBChangeLogChecker::DBChangeLogChecker(string params) : m_type("\\w+"), m_params(parseParams(params))
{
}

DBChangeLogChecker::DBChangeLogChecker(string type, map<string, string> params) : m_type(type), m_params(params)
{
}

DBChangeLogChecker::DBChangeLogChecker(string type, string params) : m_type(type), m_params(parseParams(params))
{
}

DBChangeLogChecker::~DBChangeLogChecker()
{
}

void DBChangeLogChecker::printMatchMessage()
{
	using boostMT::cout;
	using boostMT::endl;

	recursive_mutex::scoped_lock lock(cout.get_mutex());
	cout << "got matching print \"" << m_dbchange <<  "\"" << endl;
}

void DBChangeLogChecker::printWaitMessage()
{
	using boostMT::cout;
	using boostMT::endl;

	recursive_mutex::scoped_lock lock(cout.get_mutex() );
	cout << "wait for print matching dbchange type:\"" << m_type << "\" params:\"" << m_params << "\"" << endl;
}

string DBChangeLogChecker::getExpected()
{
	ostringstream os;
	os << "print matching dbchange type:\"" << m_type << "\" params:\"" << m_params << "\"";
	return os.str();
}

bool DBChangeLogChecker::checkLog(string logLine)
{
	static const regex dbchange_regex(".*DB_CHANGE_LOG, -(.*)");

	smatch match;
	if (regex_match(logLine, match, dbchange_regex))
	{	// DB change part
		string dbChangePart = match[1];
		if (dbChangePart.find("<DBChange>") != string::npos)
		{	// DB change start, discard previously collected parts
			m_dbchange = "";
		}
		m_dbchange.append(dbChangePart);
		if (m_dbchange.find("</DBChange>") != string::npos)
		{	//DB change end, time to check params
			bool ok = true;
			regex dbObject_regex("<((?:UpdatedObject)|(?:ObjectInfo))><(" + m_type + ")>(.*?)</\\2></\\1>");
			if (regex_search(m_dbchange, match, dbObject_regex))
			{
				string params = match[3];
				for (map<string,string>::iterator it = m_params.begin(); it != m_params.end(); it++)
					if (!regex_search(params, regex("<" + it->first + ">" + (it->second.empty() ? ".*?" : it->second) + "</" + it->first + ">")))
						ok = false;
			}
			else
			{
				ok = false;
			}
			if (!ok)
				m_dbchange = "";
			else
				return true;
		}
	}
	return false;
}

map<string, string> DBChangeLogChecker::parseParams(string params)
{
	typedef tokenizer<boost::char_separator<char> > tokenizer;
	static const regex param_regex("(.*?)=(.*)");
	map<string, string> result;
	smatch match;
	char_separator<char> sepSemicolon(";");
	tokenizer tokens(params, sepSemicolon);
	for (tokenizer::iterator it = tokens.begin(); it != tokens.end(); it++)
	{
		if (regex_match((*it), match, param_regex))
		{
			string name = match[1];
			string value = match[2];
			result[name] = value;
		}
	}
	return result;
}
