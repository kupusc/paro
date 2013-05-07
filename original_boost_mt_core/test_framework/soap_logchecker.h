#ifndef SOAP_LOGCHECKER_H
#define SOAP_LOGCHECKER_H

#include <map>
#include "logchecker.h"
       
class SimpleMO {
public:
	SimpleMO(string distName, string classMO, string operation, string params);
	SimpleMO(string distName, string classMO, string operation, std::map<string, string> params);
	//SimpleMO(string distName, string classMO, string operation, list<CParameter> params);
	//SimpleMO(CManagedObject MO);

	bool matchSOAP(string soap);

private:
	string m_distName;
	string m_classMO;
	string m_operation;
	std::map<string, string> m_params;
	static std::map<string, string> parseParams(string params);
	//static std::map<string, string> parseParams(const list<CParameter>& params);
};

class SOAPLogChecker : public LogCheckerBase
{
	public:
		SOAPLogChecker(string type);
		SOAPLogChecker(string type, SimpleMO MO);
		SOAPLogChecker(string type, list<SimpleMO> listMO);
		virtual ~SOAPLogChecker();

		virtual bool checkLog(string line);
		virtual void printMatchMessage();
		virtual void printWaitMessage();
		virtual string getExpected();

	private:
		string m_type;
		list<SimpleMO> m_listMO;
		string m_soap;
};

#endif