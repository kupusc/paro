#ifndef __TEST__RUNNER_H_
#define __TEST__RUNNER_H_

#include <boost/test/unit_test.hpp>

#include <list>
#include <string>
#include <map>
#include <fstream>
#include <deque>
#include <boost/test/progress_monitor.hpp>
#include <boost/scoped_ptr.hpp>
#include <boost/function.hpp>
#include <ostream>

//! Class for running multiple tests
class TestRunner
{
public:
    //! Type for result of testcase possibly returned by other process
    struct TestCaseResult {
        int returnValue; //!< 0 if success, 2 crashed, failed otherwise
        std::string errorString; //!< in case of error, this may contain string description of problem
        unsigned long elapsedTime; //!< how long the test took
    };
public:
    TestRunner(int argc, char* argv[]);
    ~TestRunner(void);

    //! Runs multiple tests
    /*!
    * \param argc Program argument count
    * \param argv Program arguments
    * \param repeatCount How many times should testcases be repeated (for finding random fcukups)
    * \param concurrentCount How many concurrent processes should run the tests
    * \param tryTest How many times each test should be started before failure is reported
    * \return True if no tests failed
    */ 
    static bool runSelectedTestCases(int argc, char* argv[], unsigned int repeatCount, unsigned int concurrentCount, unsigned int tryTest);

    //! Prints testcase names matching program arguments
    /*!
    * \param argc Program argument count
    * \param argv Program arguments
    */
    static void listSelectedTestCases(int argc, char* argv[]);

    void addTestCase(std::string tcName);

    //! Returns list full testcase names that will be run by this instance
    std::deque<std::string> getFilteredTestcases() const;

    //! Generates makefile for running testcases on cloud
    void generateMakefile(std::ostream &stream);

    //! For dev partner
    bool isCoverage() const { return m_coverage; }

    //! For dev partner
    bool isPerformance() const { return m_prf; }

    //! Gets full executable path
    const std::string &getProcessName() const { return m_processName; }

    //! Gets commands with --spawn, --repeat, -t etc. excluded
    /*! Useful when trying to pass commands to spawned test executables.
     */
    const std::string &getCommands() const { return m_cmd; }

private:
    //! Retruns true on success
    bool runTestCasesList(unsigned int concurrentCount);
    void listTestCasesList();

    std::string m_processName;
    std::string m_cmd;
    std::string m_xmlOutputFile;


    typedef std::map<std::string, TestCaseResult> TestResults;
    TestResults m_testResults;
    std::list<std::string> m_availableTestCases;
    bool m_coverage;
    bool m_prf;
    bool m_listTestcases;
    bool m_xmlOutput;
    static unsigned int m_try_test;

public:
    static const char * spawnCommand;            //!< runs every test case in separate proccess
    static const char * repeatCommand;           //!< repeats tests until anyone has failed or n times has been run.
    static const char * listCommand;             //!< only list all matching testcases, do not run them
    static const char * defaulfTimeoutCommand;   //!< default wait time for log check 
    static const char * xmlOutputCommand;        //!< generate xml log files to jenkins
    static const std::string GenerateMakefileCommand; //!< generates makefile for cloud compilation

    static const int message_queue_max_num_msg;  // max. number of messages in message queue
    static const int message_queue_max_msg_size; // max. message size of message queue


};


class test_case_collector: public boost::unit_test::test_tree_visitor {
public:
    test_case_collector(const boost::function<void(const std::string &name)> &onTestcase):mOnTestcase(onTestcase)
    {
    }
private:
    // test tree visitor interface
    virtual void visit(boost::unit_test::test_case const& tc);
    virtual bool test_suite_start(boost::unit_test::test_suite const& t);
    virtual void test_suite_finish(boost::unit_test::test_suite const& t);

    boost::function<void(const std::string &name)> mOnTestcase;
    std::deque<std::string> m_test_case_path;
};


class log_files_maker : public boost::unit_test::test_observer
{
public:
    // test observer interface
    virtual void    test_start( boost::unit_test::counter_t /* test_cases_amount */ );
    virtual void    test_finish();
    virtual void    test_unit_start( boost::unit_test::test_unit const& );
    virtual void    test_unit_finish( boost::unit_test::test_unit const&, unsigned long elapsed );
    void create_dir();
private:
    std::list<std::string> m_test_case_path;
};


class output_formater_set : public boost::unit_test::test_observer
{
    void test_start( boost::unit_test::counter_t /* test_cases_amount */ );

};     


class log_buffer_clear : public boost::unit_test::test_observer
{
    void test_unit_finish( boost::unit_test::test_unit const& t, unsigned long /* elapsed */ );

};


#endif //__TEST__RUNNER_H_

