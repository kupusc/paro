#include <boost/test/unit_test.hpp>
#include "xml_output_integrator.h"
#include <boost/tokenizer.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/functional/hash.hpp>
#include <iostream>

XmlOutputIntegrator::XmlOutputIntegrator(const std::string& test, bool xmlOutput):
xml_output(xmlOutput), file_name(XmlOutputIntegrator::genFileLocation(test))
{
    if (xml_output)
    {
        test_log.open(file_name.c_str());
        assert(!test_log.fail());
        boost::unit_test::unit_test_log.set_stream(test_log);
    }
}
XmlOutputIntegrator::~XmlOutputIntegrator()
{
    if (xml_output)
    {
        test_log.close();
        boost::unit_test::unit_test_log.set_stream(std::cout);        
    }
}

/*
* Static method used to generate name of xml output with full path  (e. g. SomeTest -> ../../logs/SomeTest.xml)
*/

std::string XmlOutputIntegrator::genFileLocation(const std::string& test)
{
    boost::hash<std::string> hashedValue;
    return "../../logs/" + extractUnitTestName(test) + "_" + boost::lexical_cast<std::string>(hashedValue(test)) + ".xml";
}

std::string XmlOutputIntegrator::extractUnitTestName(std::string test)
{
    std::replace(test.begin(), test.end(), '*', '_');
    std::replace(test.begin(), test.end(), '?', '_');
    typedef boost::tokenizer< boost::char_separator<char> > Tokenizer;
    Tokenizer tok(test, boost::char_separator<char>("/"));
    Tokenizer::iterator token;
    for (Tokenizer::iterator tok_it = tok.begin(); tok_it != tok.end(); ++tok_it)
    {
        token = tok_it;  // set the test unit name to the last token
    }

    return std::string(*token); 
}
std::string XmlOutputIntegrator::extractTestSuite(const std::string& test)
{
    typedef boost::tokenizer< boost::char_separator<char> > Tokenizer;
    Tokenizer tok(test, boost::char_separator<char>("/"));    

    std::string suite(""); 
    std::string testCase = XmlOutputIntegrator::extractUnitTestName(test); 
    for (Tokenizer::iterator tok_it = tok.begin(); tok_it != tok.end(); ++tok_it)
    {
        std::string item(*tok_it); 
        if(item == testCase)
        {
            int size = suite.size(); 
            if(size > 0)
            {
                suite.resize(size - 1); // delete last character "/"
            }
            break; 
        }
        suite += item + "/";

    }

    return suite; 
}
/**
* Static method used to create *.xml file with error message
*/
void XmlOutputIntegrator::makeFakeXml(const std::string& test)
{
        std::ofstream log;
        std::string filePath = XmlOutputIntegrator::genFileLocation(test);         
        log.open(filePath.c_str());
        assert(!log.fail());
        boost::unit_test::unit_test_log.set_stream(log);

        std::string testCase = XmlOutputIntegrator::extractUnitTestName(test); 
        GhostTestCase fakeTest(testCase);
        GhostTestCase::run(fakeTest, test);

        log.close();
        boost::unit_test::unit_test_log.set_stream(std::cout);
}

void GhostTestCase::run(const boost::unit_test::test_unit& test, const std::string& testName)
{

    boost::unit_test::log_level level(boost::unit_test::log_fatal_errors);

    GhostTestCase myTest(boost::unit_test::framework::master_test_suite().p_name.value, boost::unit_test::tut_suite);

    std::string suite = XmlOutputIntegrator::extractTestSuite(testName);
    GhostTestCase testSuite(suite, boost::unit_test::tut_suite); 
    boost::unit_test::log::begin begin_log(testName, 0);
    boost::unit_test::log::end end_log; 

    boost::unit_test::unit_test_log.test_start(1);
    boost::unit_test::unit_test_log.test_unit_start(myTest);
    boost::unit_test::unit_test_log.test_unit_start(testSuite); 
    boost::unit_test::unit_test_log.test_unit_start(test);

    boost::unit_test::unit_test_log << begin_log << level << "Test case crashed!" << end_log;

    boost::unit_test::unit_test_log.test_unit_finish(test, 0);
    boost::unit_test::unit_test_log.test_unit_finish(testSuite,0); 
    boost::unit_test::unit_test_log.test_unit_finish(myTest, 0);
    boost::unit_test::unit_test_log.test_finish();
}
