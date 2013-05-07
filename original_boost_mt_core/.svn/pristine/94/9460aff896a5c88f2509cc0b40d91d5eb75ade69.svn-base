#include "soap_logchecker.h"
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

//------------------------- SimpleMO

SimpleMO::SimpleMO(string distName, string classMO, string operation, string params) :
	m_distName(distName), m_classMO(classMO), m_operation(operation), m_params(parseParams(params))
{
}

SimpleMO::SimpleMO(string distName, string classMO, string operation, map<string, string> params) :
	m_distName(distName), m_classMO(classMO), m_operation(operation), m_params(params)
{
}

//SimpleMO::SimpleMO(string distName, string classMO, string operation, list<CParameter> params) :
//	m_distName(distName), m_classMO(classMO), m_operation(operation), m_params(parseParams(params))
//{
//}
//
//SimpleMO::SimpleMO(CManagedObject MO) :
//	m_distName(MO.getDistName()), m_classMO(MO.getClass()), m_operation(MO.getOperation), m_params(parseParams(MO.getParameter()))
//{
//}

bool SimpleMO::matchSOAP(string soap)
{
	static const regex MO_regex("<managedObject([^>]*)>(.*?)</managedObject>");
	
	sregex_iterator it = make_regex_iterator(soap, MO_regex);
	sregex_iterator end;
	
	for (it; it != end; ++it)
	{
		string mo = (*it)[0];
		string mo_attr = (*it)[1];
		string mo_children = (*it)[2];
		if (mo_attr.find("distName=\""+m_distName+"\"") != string::npos)
		{
			if (!m_classMO.empty())
				if (mo_attr.find("class=\""+m_classMO+"\"") == string::npos)
					return false;
			if (!m_operation.empty())
				if (mo_children.find("<operation>"+m_operation+"</operation>") == string::npos)
					return false;
			for (map<string,string>::iterator it = m_params.begin(); it != m_params.end(); ++it)
				if (!regex_search(mo_children, regex("<parameterName>" + it->first + "</parameterName><newValue>" + it->second + "</newValue>")))
					return false;
			return true;
		}
	}
	
	return false;
}

std::map<string, string> SimpleMO::parseParams(string params)
{
	typedef tokenizer<boost::char_separator<char> > tokenizer;
	static const regex param_regex("(.*?)=(.*)");
	map<string, string> result;
	smatch match;
	char_separator<char> sepSemicolon(";");
	tokenizer tokens(params, sepSemicolon);
	for (tokenizer::iterator it = tokens.begin(); it != tokens.end(); ++it)
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

//static std::map<string, string> SimpleMO::parseParams(list<CParameter> params)
//{
//	map<string, string> result;
//	list<CParameter>::const_iterator it;
//	for (it = params.begin(); it != params.end(); ++it)
//	{
//		result[it->getParameterName()] = it->getNewValue().opEncodeParameterValue();
//	}
//	return result;
//}


//------------------------- SOAPLogChecker

SOAPLogChecker::SOAPLogChecker(string type) : m_type(type)
{
}

SOAPLogChecker::SOAPLogChecker(string type, SimpleMO MO) : m_type(type), m_listMO(1, MO)
{
}

SOAPLogChecker::SOAPLogChecker(string type, list<SimpleMO> listMO) : m_type(type), m_listMO(listMO)
{
}

SOAPLogChecker::~SOAPLogChecker()
{
}

void SOAPLogChecker::printMatchMessage()
{
	using boostMT::cout;
	using boostMT::endl;

	recursive_mutex::scoped_lock lock(cout.get_mutex());
	cout << "got matching print \"" << m_soap <<  "\"" << endl;
}

void SOAPLogChecker::printWaitMessage()
{
	using boostMT::cout;
	using boostMT::endl;

	recursive_mutex::scoped_lock lock(cout.get_mutex() );
	cout << "wait for print matching soap type: \"" << m_type << "\"" << endl;
}

string SOAPLogChecker::getExpected()
{
	ostringstream os;
	os << "print matching soap type: \"" << m_type << "\"";
	return os.str();
}

bool SOAPLogChecker::checkLog(string logLine)
{
	static const regex soap_regex(".*APW, - (.*)");

	smatch match;
	if (regex_match(logLine, match, soap_regex))
	{	// SOAP part
		string soapPart = match[1];
		if (soapPart.find("<SOAP-ENV:Envelope") != string::npos)
		{	// SOAP start, discard previously collected parts
			m_soap = "";
		}
		m_soap.append(soapPart);
		if (m_soap.find("</SOAP-ENV:Envelope>") != string::npos)
		{	// SOAP end, time to check params
			bool ok = true;
			regex message_regex("<SOAP-ENV:Body><(" + m_type + ")>(.*?)</\\1></SOAP-ENV:Body>");
			if (regex_search(m_soap, match, message_regex))
			{
				string params = match[2];
				for (list<SimpleMO>::iterator it = m_listMO.begin(); it != m_listMO.end(); ++it)
					if (!(it->matchSOAP(params)))
						ok = false;
			}
			else
			{
				ok = false;
			}
			if (!ok)
				m_soap = "";
			else
				return true;
		}
	}
	return false;
}
