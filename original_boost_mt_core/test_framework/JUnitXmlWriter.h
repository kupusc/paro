#ifndef __JUNIT_XML_WRITER_H__
#define __JUNIT_XML_WRITER_H__

#ifndef TIXML_USE_STL
#define TIXML_USE_STL
#endif
#include <tinyxml.h>

// class for writing an XML file in JUnit XML format
class JUnitXmlWriter
{
public:
	JUnitXmlWriter(void);
	~JUnitXmlWriter(void);
	void init(void);
	void clearAll(void);
	int  getNumberOfTestcases(void);
	void saveFile(const char * filename);
	void addTestcase(const std::string& testcaseName, int retValue, unsigned long elapsedTime,
	                 const std::string& errorString);
	
protected:
	void addTestsuiteTag(const char * name);
	void addTestcaseTag(const char * name, unsigned long time = 0);
	void addErrorTag();
	void addFailureTag(const char * text);
	void setTestsuiteAttr(int tests, int failures, int errors, unsigned long time, int skipped=0);

private:
	int            m_numberOfTestcases;
	TiXmlDocument  m_xmlDoc;
	TiXmlElement*  m_xmlRoot;
	TiXmlElement*  m_xmlCurrentTestsuite;
	TiXmlElement*  m_xmlCurrentTestcase;
	std::string    m_testSuiteName;
	int            m_passedCases;
	int            m_passedCasesSum;
	int            m_crashedCases;
	int            m_failedCases;
	unsigned long  m_testsuiteTime;
};

#endif

