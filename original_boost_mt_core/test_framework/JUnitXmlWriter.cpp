#include "JUnitXmlWriter.h"


// helper function
std::string getFolderName(const std::string& name)
{
	size_t pos = name.find_last_of("/\\");
	std::string folder = name.substr(0, pos);
	return folder;
}

// helper function
std::string getBaseName(const std::string& name)
{
	size_t pos = name.find_last_of("/\\");
	std::string base = name.substr(pos+1);
	return base;
}


// Constructor
JUnitXmlWriter::JUnitXmlWriter(void)
{
	clearAll();
	init();
}


// Destructor
JUnitXmlWriter::~JUnitXmlWriter(void)
{
	clearAll();
}


// Initialization
void JUnitXmlWriter::init(void)
{
	// add <testsuites> tag (which is the XML root element)
	m_xmlRoot = new TiXmlElement("testsuites");  
	m_xmlDoc.LinkEndChild(m_xmlRoot);
}


// Clear all content of XML Doc
void JUnitXmlWriter::clearAll(void)
{
	m_xmlDoc.Clear();
	
	m_xmlRoot = NULL;
	m_xmlCurrentTestsuite = NULL;
	m_xmlCurrentTestcase = NULL;
	m_numberOfTestcases = 0;
	
	m_passedCases    = 0;
	m_passedCasesSum = 0;
	m_crashedCases   = 0;
	m_failedCases    = 0;
	m_testsuiteTime  = 0;
	m_testSuiteName  = "";
}


// add <testsuite> tag to the XML root element
void JUnitXmlWriter::addTestsuiteTag(const char * name)
{
	if (m_xmlRoot)
	{
		TiXmlElement * xmlTestsuite = new TiXmlElement("testsuite");  
		m_xmlRoot->LinkEndChild(xmlTestsuite);
		xmlTestsuite->SetAttribute("name", name);
		m_xmlCurrentTestsuite = xmlTestsuite;
	}
}


// add <testcase> tag to current testsuite
void JUnitXmlWriter::addTestcaseTag(const char * name, unsigned long time)
{
	if (m_xmlCurrentTestsuite)
	{
		// format elapsed time (in seconds with 2 digits after the decimal point)
		std::ostringstream timeStream;
		timeStream.precision(2);
		timeStream << std::showpoint << std::fixed << float(time)/1000000.0;
		
		// add <testcase> tag
		TiXmlElement * xmlTc = new TiXmlElement("testcase");
		m_xmlCurrentTestsuite->LinkEndChild(xmlTc);
		xmlTc->SetAttribute("name", name);
		xmlTc->SetAttribute("classname", getBaseName(m_testSuiteName));
		xmlTc->SetAttribute("time", timeStream.str());
		m_xmlCurrentTestcase = xmlTc;
		m_numberOfTestcases++;
	}
}


// add <error> tag to current testcase
void JUnitXmlWriter::addErrorTag()
{
	if (m_xmlCurrentTestcase)
	{
		TiXmlElement * xmlError = new TiXmlElement("error");
		m_xmlCurrentTestcase->LinkEndChild(xmlError);
		xmlError->SetAttribute("type", "crashed");
	}
}


// add <failure> tag to current testcase
void JUnitXmlWriter::addFailureTag(const char * text)
{
	if (m_xmlCurrentTestcase)
	{
		TiXmlElement * xmlFailure = new TiXmlElement("failure");
		m_xmlCurrentTestcase->LinkEndChild(xmlFailure);
		xmlFailure->SetAttribute("type", "failed");
		xmlFailure->LinkEndChild(new TiXmlText(text));
	}
}


// set attributes of current testsuite
void JUnitXmlWriter::setTestsuiteAttr(int tests, int failures, int errors, unsigned long time, int skipped)
{
	if (m_xmlCurrentTestsuite)
	{
		std::ostringstream timeStream;
		timeStream.precision(2);
		timeStream << std::showpoint << std::fixed << float(time)/1000000.0;
		
		m_xmlCurrentTestsuite->SetAttribute("tests", tests);
		m_xmlCurrentTestsuite->SetAttribute("errors", errors);
		m_xmlCurrentTestsuite->SetAttribute("failures", failures);
		m_xmlCurrentTestsuite->SetAttribute("time", timeStream.str());
		m_xmlCurrentTestsuite->SetAttribute("skipped", skipped);
	}
}


// get number of testcases
int JUnitXmlWriter::getNumberOfTestcases(void)
{
	return m_numberOfTestcases;
}


// save XML file to disc
void JUnitXmlWriter::saveFile(const char * filename)
{
	// set attributes for <testsuite> tag
	setTestsuiteAttr(m_passedCases + m_crashedCases + m_failedCases, m_failedCases,
	                 m_crashedCases, m_testsuiteTime);
	m_xmlDoc.SaveFile(filename);
}


// add 1 testcase to XML doc
void JUnitXmlWriter::addTestcase(const std::string& testcaseName, int retValue,
                                 unsigned long elapsedTime, const std::string& errorString)
{
	std::string folderName = getFolderName(testcaseName);
	
	// check if testsuite has changed 
	if (m_testSuiteName.compare(folderName) != 0)
	{
		if (getNumberOfTestcases() > 0)
		{
			// set attributes for <testsuite> tag
			setTestsuiteAttr(m_passedCases + m_crashedCases + m_failedCases,
			                 m_failedCases, m_crashedCases, m_testsuiteTime); 
			m_passedCases = 0;
			m_crashedCases = 0;
			m_failedCases = 0;
			m_testsuiteTime = 0;
		}
		
		m_testSuiteName = folderName;
		//std::cout << "test suite " << m_testSuiteName.c_str() << ":" << std::endl;
		addTestsuiteTag(m_testSuiteName.c_str());
	}
	
	// add <testcase> tag
	addTestcaseTag(getBaseName(testcaseName).c_str(), elapsedTime);
	m_testsuiteTime += elapsedTime;
	
	if (retValue == 2)
	{
		m_crashedCases++;
		addErrorTag();
	}
	else if (retValue == 0)
	{
		m_passedCases++;
		m_passedCasesSum++;
	}
	else
	{
		m_failedCases++;
		addFailureTag(errorString.c_str());
	}
}

