#ifndef _XML_OUTPUT_INTEGRATOR
#define _XML_OUTPUT_INTEGRATOR

#include <boost/test/unit_test.hpp>
#include <boost/filesystem.hpp>
#include <fstream>
#include "init.h"

//! Class used to integrate .xml files when test has been crushed
class XmlOutputIntegrator
{
    public:
        XmlOutputIntegrator(const std::string& test, bool xmlOutput);
        ~XmlOutputIntegrator();

        static void makeFakeXml(const std::string& test);
        static std::string genFileLocation(const std::string& test);
        static std::string extractUnitTestName(std::string test); 
        static std::string extractTestSuite(const std::string& test); 

    private:
        std::ofstream test_log;
        std::string const file_name;
        bool const xml_output;
};

//! Class creates fake unit test case with correct data in xml file structure
class GhostTestCase: public boost::unit_test::test_unit
{
    public:
        GhostTestCase(const std::string& name, boost::unit_test::test_unit_type type = boost::unit_test::tut_case):
            boost::unit_test::test_unit(name, type)
        {
        }
        static void run(const boost::unit_test::test_unit& test, const std::string& testName);
};

#endif
