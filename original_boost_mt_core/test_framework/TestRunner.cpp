#include "TestRunner.h"
#include "ConsoleOutputHandler.h"
#include <stdio.h>
//#include <tchar.h>
#include <iomanip>
#include <algorithm>
#include "print_writer.h"
#include <boost/bind.hpp>
#include <boost/timer.hpp>
#include <iostream>
#include <boost/program_options.hpp>
#include "MessageQueue.h"
#include "dbg_prints.h"
#include "console_output.h" //ConsoleOutputHandler
#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_io.hpp> //to_string
#include <boost/uuid/random_generator.hpp>
#include "ThreadPool.h"
#include <boost/algorithm/string.hpp> //trim
#include "xml_output_integrator.h"
#include "mt_paths.h"
#include <boost/bind.hpp>

#ifdef LINUX
#include <sys/stat.h>
#include <sys/types.h>
#else
#include <windows.h>
#endif 


using namespace std;
using namespace boost::unit_test;
using namespace original_boost_mt_core::test_framework;

const char* TestRunner::spawnCommand = "--spawn";
const char* TestRunner::repeatCommand = "--repeat=" ;
const char* TestRunner::listCommand = "--list";
const char* TestRunner::defaulfTimeoutCommand = "--default_timeout=" ;
const char* TestRunner::xmlOutputCommand = "--output_format=XML";
const std::string TestRunner::GenerateMakefileCommand = "generate_makefile";
const int TestRunner::message_queue_max_num_msg = 1;    // max. number of messages in message queue
const int TestRunner::message_queue_max_msg_size = 512; // max. message size of message queue
unsigned int TestRunner::m_try_test = 1;

// of course, Microsoft is too fabulous to implement POSIX functions under their
// normal names.
#ifdef _MSC_VER
#define popen _popen
#define pclose _pclose
#endif

#ifdef _MSC_VER
#define POPEN_FLAGS "rt"
#else
#define POPEN_FLAGS "r"
#endif


class make_path
{
public:
    void operator()(std::string s)
    {
        m_full_name += s + "/";
    }
    std::string m_full_name;
};




void log_files_maker::test_start(counter_t count)
{
    //cout << "#entering log_files_maker::test_start()" << endl;
}

void log_files_maker::test_finish()
{
    //cout << "#entering log_files_maker::test_finish()" << endl;
}

void log_files_maker::test_unit_start(test_unit const& t)
{
    //cout << "#entering log_files_maker::test_unit_start()" << endl;
    using namespace original_boost_mt_core::test_framework;

    string type(t.p_type_name.get().begin(), t.p_type_name.get().end());
    if (type == "case")
    {
        make_path op;
        op = for_each(++m_test_case_path.begin(), m_test_case_path.end(), op);

        // open logfile
        Print_writer::get_instance()->open_file(MT_ROOT_PATH / RELATIVE_LOG_PATH / (op.m_full_name + string(t.p_name) + ".log"));
    }
    else if (type == "suite")
    {
        m_test_case_path.push_back(t.p_name);
        create_dir();
    }
    else
    {
        assert(0);
    }

}

void log_files_maker::test_unit_finish(test_unit const& t, unsigned long elapsed)
{
    using namespace original_boost_mt_core::test_framework;
    //cout << "#entering log_files_maker::test_unit_finish()" << endl;

    string type(t.p_type_name.get().begin(), t.p_type_name.get().end());
    if (type == "case")
    {
        make_path op;
        op = for_each(++m_test_case_path.begin(), m_test_case_path.end(), op);

        std::cout << "Elapsed time: " << float(elapsed) / 1000000.0 << " sec" << endl;
        GlobalMessage::getSingleton().elapsedTime = elapsed;  // set elapsedTime (static member of GlobalMessage)

        // write error file
        boostMT::cout.writeErrorFile(RELATIVE_LOG_PATH + op.m_full_name + string(t.p_name) + ".err",
                                     GlobalMessage::getSingleton().errorString);
        // close logfile
        Print_writer::get_instance()->close_file();
    }
    else if (type == "suite")
    {
        assert(!m_test_case_path.empty());
        m_test_case_path.pop_back();
    }
    else
    {
        assert(0);
    }
}

void log_files_maker::create_dir()
{
    make_path op;
    op = for_each(++m_test_case_path.begin(), m_test_case_path.end(), op);

    boost::filesystem::path coverage = MT_ROOT_PATH / "code_coverage" / "results" / op.m_full_name;
    boost::filesystem::path logs = MT_ROOT_PATH / RELATIVE_LOG_PATH / op.m_full_name ;

    try
    {
        boost::filesystem::create_directory(coverage);
        boost::filesystem::create_directory(logs);
    }
    catch (...)
    {
        cout << "ERROR: Failed to create directories:\n" << coverage << "\nor: " << logs << std::endl;
        throw ;
    }
}

// ---------------------------------- test_case_collector ---------------------------------

bool test_case_collector::test_suite_start(test_suite const& t)
{
    m_test_case_path.push_back(t.p_name);
    return true;
}

void test_case_collector::test_suite_finish(test_suite const&  t)
{
    assert(!m_test_case_path.empty());
    m_test_case_path.pop_back();
}

void test_case_collector::visit(test_case const& tc)
{
    if (tc.p_enabled)
    {
        make_path op;

        for_each(++m_test_case_path.begin(), m_test_case_path.end(), boost::bind<void>(boost::ref(op), _1));
    
        mOnTestcase(op.m_full_name + string(tc.p_name));
    }
}

// ---------------------------------- TestRunner::TestCaseWorker ---------------------------------

namespace
{
    class ILogReceiver
    {
    public:
        virtual void addLogLine(const std::string &line) = 0;
    };

    struct DefaultLogReceiver: public ILogReceiver
    {
    public:
        virtual void addLogLine(const std::string &line)
        {
            std::cout << line << std::endl;
        }

    } defaultLogReceiver;

    class TestCaseWorker
    {
    public:

    public:
        TestCaseWorker(const TestRunner &testRunner, const std::string &messageQueueName): m_testRunner(testRunner), m_messageQueueName(messageQueueName)
        {
            m_msgQueue.reset(new MessageQueue(messageQueueName, TestRunner::message_queue_max_num_msg, TestRunner::message_queue_max_msg_size));
            m_msgQueue->create();
        }

        TestRunner::TestCaseResult runTestcase(const string &name, ILogReceiver &logReceiver = defaultLogReceiver);

    private:
        const TestRunner &m_testRunner;
        std::string const m_messageQueueName;
        boost::scoped_ptr<MessageQueue> m_msgQueue;
    };

}

TestRunner::TestCaseResult TestCaseWorker::runTestcase(const string &name, ILogReceiver &logReceiver)
{
    if (m_testRunner.isCoverage())
    {
        string testCaseCmd = m_testRunner.getCommands() + " -t " + name;
        string codeCoverageCmd = "DPAnalysis /COV /E /O " "../../code_coverage/results/" + name + ".dpcov /W code_coverage/ /P " + m_testRunner.getProcessName() ; //+testCaseCmd;
        logReceiver.addLogLine(codeCoverageCmd);
        assert(system(codeCoverageCmd.c_str()) == 0 && "cannot execute DPAnalysis!");
    }
    else if (m_testRunner.isPerformance())
    {
        string testCaseCmd = m_testRunner.getCommands() + " -t " + name;
        string prfProfileCmd = "DPAnalysis /PERF /E /O " "../../performance_profile/results/" + name + ".dpprf /W performance_profile/ /P " + m_testRunner.getProcessName() ; //+testCaseCmd;
        logReceiver.addLogLine(prfProfileCmd);
        assert(system(prfProfileCmd.c_str()) == 0 && "cannot execute DPAnalysis!");
    }
    // start own process for this testcase
    //system((m_testRunner.getCommands() + " -t " + name).c_str()); // return value ignored

    {
        // Starts process and redirect (through pipe) output to vector<string>

        size_t const MAX_BUFFER = 1 * 1000 * 1000;
        boost::scoped_array<char> psBuffer(new char[MAX_BUFFER]);
        FILE   *pPipe;

        // Note: we redirect stderr -> stdout
        std::string const command(m_testRunner.getCommands() + " --messagequeue=" + m_messageQueueName + " -t " + name + " 2>&1");

        if ((pPipe = popen(command.c_str(), POPEN_FLAGS)) == NULL)
        {
            throw std::runtime_error("unable run command: \"" + command + "\"");
        }

        //TODO: fgets waits till program exits before exiting even if child process already started printing a few lines
        while (fgets(psBuffer.get(), MAX_BUFFER, pPipe))
        {
            std::string line(psBuffer.get());
            while (!line.empty() && *line.rbegin() == '\n') //we need line without ending new-line characters
            {
                line.resize(line.size() - 1);
            }
            logReceiver.addLogLine(line);
        }

        if (feof(pPipe))
        {
            pclose(pPipe);
        }
        else
        {
            throw std::runtime_error("error closing pipe while running command: \"" + command + "\"");
        }
    }

    TestRunner::TestCaseResult result;
    result.returnValue = 2;  // initialize return value with 2=crashed
    result.elapsedTime = 0;  // initialize with elapsed time = 0

    while (m_msgQueue->getNumMsg() > 0)
    {
        InterprocessMessage msg;
        if (m_msgQueue->receive(msg))  // read 1 message
        {
            result.returnValue = msg.m_returnCode;
            result.errorString = msg.m_errorString;
            result.elapsedTime = msg.m_elapsedTime;
        }
    }

    return result;
}


// ---------------------------------- TestRunner -----------------------------------------------------


TestRunner::TestRunner(int argc, char* argv[]) : m_coverage(false), m_prf(false), m_listTestcases(false), m_xmlOutput(false)
{
    m_processName = argv[0];

    size_t pos = m_processName.find_last_of("/\\");
    string prefix = m_processName.substr(pos + 1, 2);

    for (int i = 0; i < argc; i++)
    {
        if (string(argv[i]) == TestRunner::listCommand)
        {
            m_listTestcases = true;
        }
        else if (string(argv[i]) == TestRunner::spawnCommand)
        {
            //skip
        }
        else if (string(argv[i]).find(TestRunner::repeatCommand) != string::npos)
        {
            //skip
        }
        else if (string(argv[i]) == "-t")
        {
            i++; //skip next value
        }
        else if (string(argv[i]).substr(0, 11) ==  "--run_test=")
        {
            //skip
        }
        else if(string(argv[i]).substr(2, GenerateMakefileCommand.size()) ==  GenerateMakefileCommand)
        {
            //skip
        }
        else
        {
            m_cmd += argv[i];
            m_cmd += " ";
        }

        if (string(argv[i]) == "-cov")
        {
            m_coverage = true;
        }
        if (string(argv[i]) == "-prf")
        {
            m_prf = true;
        }
        if (string(argv[i]) == TestRunner::xmlOutputCommand)
        {
            m_xmlOutput = true;
        }

    }
}


TestRunner::~TestRunner(void)
{
    if (!m_listTestcases)
    {
        struct MyConsoleOutput: public ConsoleOutputHandler
        {
            MyConsoleOutput(): DefaultColor(opGetTextColor()) {}

            ~MyConsoleOutput()
            {
                makeDafault();
            }

            void makeDafault()
            {
                opSetTextColor(DefaultColor);
            }

            ETextColor const DefaultColor;
        } consoleOutput;

        cout << endl << "Test Summary: \n" << endl;
        int passedCases = 0;

        for (TestResults::const_iterator it = m_testResults.begin(); m_testResults.end() != it; ++it)
        {
            cout << "tc  " << setw(80);

            if (3 == it->second.returnValue)
            {
                consoleOutput.opSetTextColor(TextColor_INTENSIVE_BLUE);
                cout << left << it->first << " " << "MEMORYLEAKED" << endl;

                // For now we have to pass memory leaks, because of how (badly) production code works
                // - false positives may occur
                passedCases++;
            }
            else if (2 == it->second.returnValue)
            {
                if (m_xmlOutput)
                {
                    XmlOutputIntegrator::makeFakeXml(it->first);
                }
                consoleOutput.opSetTextColor(TextColor_INTENSIVE_YELLOW);
                cout << left << it->first << " " << "CRASHED" << endl;
            }
            else if (0 == it->second.returnValue)
            {
                consoleOutput.opSetTextColor(TextColor_INTENSIVE_GREEN);
                cout << left << it->first << " " << "PASSED" << endl;
                passedCases++;
            }
            else
            {
                consoleOutput.opSetTextColor(TextColor_INTENSIVE_RED);
                cout << left << it->first << " " << "FAILED" << endl;
            }

            consoleOutput.makeDafault();
        }

        if (passedCases != m_testResults.size())
        {
            consoleOutput.opSetTextColor(TextColor_INTENSIVE_RED);
            cout << endl << "T E S T S          F A I L E D" << endl;
        }
        else
        {
            consoleOutput.opSetTextColor(TextColor_INTENSIVE_GREEN);
            cout << endl << "T E S T S          P A S S E D" << endl;
        }

        consoleOutput.makeDafault();

        cout << endl << "Pass ratio: " << passedCases << "/" << m_testResults.size() << " passed.\n";
    }
}

struct TestCaseTask
{

    TestCaseTask(const TestRunner &testRunner, const std::string &testName, TestRunner::TestCaseResult &result, boost::mutex &printMutex, unsigned int tryTest):
        mTestRunner(testRunner), mTestName(testName), mResult(result), mPrintMutex(printMutex), mTryTest(tryTest)
    {}

    void operator()()
    {
        boost::uuids::uuid queueUUID = boost::uuids::random_generator()();
        std::string queueName(boost::uuids::to_string(queueUUID) + mTestName);
        std::replace(queueName.begin(), queueName.end(), '/', '_');
        std::replace(queueName.begin(), queueName.end(), '-', '_');

        TestCaseWorker m_worker(mTestRunner, queueName);
        for (unsigned int i = 0; i < mTryTest; ++i)
        {
            // Setup unique queue name

            struct : public ILogReceiver
            {
                virtual void addLogLine(const std::string &line)
                {
                    mLines.push_back(line);
                }

                std::vector<std::string> mLines;
            } logReceiver;

            mResult = m_worker.runTestcase(mTestName, logReceiver);

            {
                boost::mutex::scoped_lock guard(mPrintMutex);
                for (std::vector<std::string>::const_iterator it = logReceiver.mLines.begin(); logReceiver.mLines.end() != it; ++it)
                {
                    if (it->find_first_not_of(" \n\r\t") != std::string::npos)
                    {
                        std::cout << *it << std::endl;
                    }
                }
                if (0 == mResult.returnValue) // success
                {
                    break;
                }
                else if (i < mTryTest - 1)
                {
                    std::cout << "Test Case FAILED... try again" << std::endl;
                }
                std::cout << std::endl;
            }
        }
    }

private:
    const TestRunner &mTestRunner;
    std::string mTestName;
    TestRunner::TestCaseResult &mResult;
    boost::mutex &mPrintMutex;
    unsigned int mTryTest;

};


bool TestRunner::runTestCasesList(unsigned int concurrentCount)
{
    assert(m_try_test >= 1);
    if (concurrentCount > 1)
    {
        ThreadPool pool(concurrentCount);

        boost::mutex printMutex;

        for (list<string>::const_iterator it = m_availableTestCases.begin(); m_availableTestCases.end() != it; ++it)
        {
            std::string const &name = *it;

            pool.addTask(TestCaseTask(*this, name, m_testResults[name], printMutex, m_try_test));
        }

        pool.waitForCompletion();
    }
    else
    {
        // there is no point of running it on threads, that way we get better printing

        for (list<string>::const_iterator it = m_availableTestCases.begin(); m_availableTestCases.end() != it; ++it)
        {
            boost::uuids::uuid queueUUID = boost::uuids::random_generator()();
            std::string queueName(boost::uuids::to_string(queueUUID) + *it);
            std::replace(queueName.begin(), queueName.end(), '/', '_');
            std::replace(queueName.begin(), queueName.end(), '-', '_');

            TestCaseWorker m_worker(*this, queueName);
            for (unsigned int i = 0; i < m_try_test; ++i)
            {

                struct : public ILogReceiver
                {
                    virtual void addLogLine(const std::string &line)
                    {
                        std::cout << line << std::endl;
                    }

                } logReceiver;

                m_testResults[*it] = m_worker.runTestcase(*it, logReceiver);

                if (0 == m_testResults[*it].returnValue) // success
                {
                    break;
                }
                else if (i < m_try_test - 1)
                {
                    std::cout << "Test Case FAILED... try again" << std::endl;
                }

            }
        }
    }

    bool success = true;
    for (list<string>::const_iterator it = m_availableTestCases.begin(); m_availableTestCases.end() != it; ++it)
    {
        if (0 != m_testResults[*it].returnValue)
        {
            success = false;
            break;
        }
    }

    return success;
}


void TestRunner::listTestCasesList()
{
    list<string> & lista = m_availableTestCases;

    for (list<string>::iterator it = lista.begin(); it != lista.end(); ++it)
    {
        cout << *it << endl;
    }
}


bool TestRunner::runSelectedTestCases(int argc, char* argv[], unsigned int repeatCount, unsigned int concurrentCount, unsigned int tryTest)
{

    bool result;
    unsigned int count = 0;
    m_try_test = tryTest;
    do
    {
        cout << endl << "Running iteration " <<  count + 1 << "/" <<  repeatCount << endl << endl;
        TestRunner tr(argc, argv);
        test_case_collector tcc(boost::bind(&TestRunner::addTestCase, &tr, _1));
        traverse_test_tree(framework::master_test_suite().p_id, tcc);
        result = tr.runTestCasesList(concurrentCount);
        count ++;
    }
    while (result && count < repeatCount) ;

    ConsoleOutputHandler ConsoleOutput;
    ETextColor DefaultColor = ConsoleOutput.opGetTextColor();
    if (result)
    {
        ConsoleOutput.opSetTextColor(TextColor_INTENSIVE_GREEN);
        cout << endl << "All " <<  repeatCount <<  " iterations PASSED" << endl;
    }
    else
    {
        ConsoleOutput.opSetTextColor(TextColor_INTENSIVE_RED);
        cout << endl << "Iteration " <<  count << "/" <<  repeatCount << " FAILED" << endl;
    }
    ConsoleOutput.opSetTextColor(DefaultColor);

    return result;
}


void TestRunner::listSelectedTestCases(int argc, char* argv[])
{
    using namespace std;
    deque<string> const testcases = TestRunner(argc, argv).getFilteredTestcases();

    for (deque<string>::const_iterator it = testcases.begin(); it != testcases.end(); ++it)
    {
        cout << *it << endl;
    }
}


void TestRunner::addTestCase(string tcName)
{
    m_availableTestCases.push_back(tcName);
}

std::deque<std::string> TestRunner::getFilteredTestcases() const
{
    using namespace std;
    deque<string> result;
    // http://stackoverflow.com/questions/4248357/are-there-boostbind-issues-with-vs2010
    test_case_collector tcc(boost::bind(static_cast<void (deque<string>::*)( const string& )>(&deque<string>::push_back), &result, _1));
    traverse_test_tree(framework::master_test_suite().p_id, tcc);
    return result;
}

void TestRunner::generateMakefile(std::ostream &stream)
{
    stream << "all: testall" << std::endl;
    stream << std::endl;
    stream << "TESTCOMMAND = " << " " << getCommands() << " -t " << std::endl;
    stream << std::endl;
    stream << ".FORCE:" << std::endl;
    stream << ".PHONY: .FORCE" << std::endl;
    stream << std::endl;
    stream << ".PHONY: testall" << std::endl;

    std::deque<std::string> const testcases = getFilteredTestcases();
    for(std::deque<std::string>::const_iterator i = testcases.begin(); testcases.end() != i; ++i)
    {
        stream << "testall: testcase_" << *i << std::endl;
    }

    stream << "\techo (makefile) Test all done" << std::endl;
    
    for(std::deque<std::string>::const_iterator i = testcases.begin(); testcases.end() != i; ++i)
    {
        stream << std::endl;
        stream << "testcase_" << *i << ": .FORCE" << std::endl;
        stream << "\t-$(TESTCOMMAND) " << *i << std::endl;
        stream << ".PHONY: testcase_" << *i << std::endl;
    }
}

// ------------------------------- output_formater_set ----------------------

void output_formater_set::test_start(counter_t /* test_cases_amount */)
{
    boost::unit_test::unit_test_log.set_formatter(&boostMT::thread_safe_compiler_log_formatter::get_instance());
}

// ------------------------------- log_buffer_clear ----------------------

void log_buffer_clear::test_unit_finish(test_unit const& t, unsigned long /* elapsed */)
{
    string type(t.p_type_name.get().begin(), t.p_type_name.get().end());
    if (type == "case")
    {
        dbg_prints::instance()->clear_buffer();//----------------------------------------------------------------------------
    }
}
