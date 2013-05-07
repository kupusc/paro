#define BOOST_TEST_ALTERNATIVE_INIT_API
#include <boost/test/unit_test.hpp>
#include <boost/test/framework.hpp>
#include <boost/filesystem.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/functional/hash.hpp>

#include <iostream>
#ifndef DISABLE_STACKWALKER
#include "CrashHandler.h"
#endif
#ifdef _WIN2
#include <windows.h>
#endif


#include "LeakReporter.h"
#include "testcase_filter.h"
#include "TestRunner.h"
#include "console_output.h"                                                                                                            
#include "log_barrier.h"
#include "env_time.h"
#include "logcheck_timeout.h"
#include "dbg_prints.h"
#include "print_writer.h"

#include "MessageQueue.h" //GlobalMessage
#include <boost/program_options.hpp>
#include "xml_output_integrator.h"
#include <fstream>
#include "mt_paths.h"

using namespace std;
using namespace original_boost_mt_core::test_framework;

namespace
{
    /**
     * @brief Creates proper directory structure for MT tests. 
     *
     * Directories will be created by first MT process started (on single thread).
     * Other processes/threads will just check existance of directories so it can be safely used.
     */
    void ensureDirectoryStructure()
    {
        using boost::filesystem::create_directory;

        create_directory(MT_ROOT_PATH / "logs");
        create_directory(MT_ROOT_PATH / RELATIVE_LOG_PATH);        
#ifdef EACH_PROCESS_USES_ITS_OWN_DIRECTORY
        create_directory(MT_ROOT_PATH / RELATIVE_TMP_PATH);
#endif
    }

    /**
     * @brief Initialize temporary directory for each started process.
     *
     * It generates unique directry based on test case name and creates directory structure:
     * ./ram
     * ./rom
     *  \- config
     *   \- PersDataFiles
     *
     * This method also copy swconfig.txt file from app/exe/rom/ if it exists.
     *
     * This method is not thread safe, however it should be started for a specific directory name
       only once on single thread.
     *
     * @param testName Name of currently started test
     */
    void initializeTempDirectory(const std::string& testName)
    {
        {
            size_t pos = testName.find_last_of("/");
            if (std::string::npos == pos)
            {
                pos = -1;
            }
            size_t length = testName.length() + 1 - pos;
            if (length > 16)
            {
                length = 16;
            }
            std::string testCaseName = testName.substr(pos + 1, pos + 1 + length);
            std::replace(testCaseName.begin(), testCaseName.end(), '*', '_');
            std::replace(testCaseName.begin(), testCaseName.end(), '?', '_');

            boost::hash<std::string> hashedValue;
            PER_TESTCASE_TMP_PATH = MT_ROOT_PATH / RELATIVE_TMP_PATH / (testCaseName + "_" + boost::lexical_cast<std::string>(hashedValue(testName)));
        }

        if (boost::filesystem::exists(PER_TESTCASE_TMP_PATH))
        {
            boost::filesystem::remove_all(PER_TESTCASE_TMP_PATH);
        }
        boost::filesystem::create_directory(PER_TESTCASE_TMP_PATH);

        boost::filesystem::current_path(PER_TESTCASE_TMP_PATH);

        boost::filesystem::path romPath = PER_TESTCASE_TMP_PATH / "rom";
        if (!boost::filesystem::exists(romPath))
        {
            boost::filesystem::create_directory(romPath);
        }

        boost::filesystem::path configPath = romPath / "config";
        if (!boost::filesystem::exists(configPath))
        {
            boost::filesystem::create_directory(configPath);
        }

        boost::filesystem::path persPath = configPath / "PersDataFiles";
        if (!boost::filesystem::exists(persPath))
        {
            boost::filesystem::create_directory(persPath);
        }

        boost::filesystem::path ramPath = PER_TESTCASE_TMP_PATH / "ram";
        if (!boost::filesystem::exists(ramPath))
        {
            boost::filesystem::create_directory(ramPath);
        }

        // Copy swconfig.txt if exists
        boost::filesystem::path swconfigOldPath = MT_ROOT_PATH / "app" / "exe" / "rom" / "swconfig.txt";
        if (boost::filesystem::exists(swconfigOldPath))
        {
            boost::filesystem::path swconfigNewPath = romPath / "swconfig.txt";
            boost::filesystem::copy_file(swconfigOldPath, swconfigNewPath);
        }

    }
}

static bool empty_init()
{
    return true;
}

static void filterTestTree(int argc, char* const argv[])
{
    using namespace boost::unit_test::framework;

    //make a copy of args as boost::unit_test::framework::init is eating them.
    assert(argc < 100);
    char* argv_bak[100] = {0};
    std::copy(argv,argv + argc , argv_bak);

    boost::unit_test::framework::init(empty_init, argc, argv_bak);

    test_case_filter filter(runtime_config::test_to_run());
    traverse_test_tree(framework::master_test_suite().p_id, filter);
}

int boostMT_init( int argc, char* argv[] ,bool (*user_init)() ) try
{
#ifndef DISABLE_STACKWALKER
    struct StopUsingStackWalkerAfterExit
    {
        ~StopUsingStackWalkerAfterExit()
        {
            // Using stack walker when program is closing is not a good idea anyway
            CrashHandler::getInstance()->setCatchesExceptions(false); 
        }
    };

    StopUsingStackWalkerAfterExit stopUsingStackWalkerAfterExit;  
#endif

    MT_ROOT_PATH = boost::filesystem::current_path() / ".." / "..";
    PER_TESTCASE_TMP_PATH = MT_ROOT_PATH / "app" / "exe";
    std::cout << MT_ROOT_PATH;

    namespace po = boost::program_options;

    po::options_description desc("Allowed options");
    desc.add_options()
        ("messagequeue", po::value< string >(), "name of the message queue for child processes. if supplied, then spawn command is ignored")
        ("spawn", po::value< unsigned int >()->implicit_value(1), "specifies if test shall run in own processes, number specifies concurent executions")
        ("list", "lists all testcase names")
        ("repeat", po::value< unsigned int >(), "repeats tests \"arg\" times")  
        ("default_timeout", po::value< unsigned int >(), "default duration of timeout (in seconds)")
        ("output_format", po::value< string >(), "XML")
        ("testcase,t", po::value< string >()->default_value("AllTestCases"), "name of testcase to run")
        ("help", "prints available commands")
        ("nouserattention", "for CI. ensures that for instance no assert message boxes are shown - instead prints to stdout")
        ("try_test", po::value< unsigned int >()->default_value(1), "defines how many times each test should be run before reporting failure. Don't use it!")
        ("generate_makefile", po::value<std::string>()->implicit_value("TestcasesMakefile"), "Generates makefile for running testcases on cloud")
        ;     

    po::variables_map vm;

    po::parsed_options parsed = po::command_line_parser(argc, argv).options(desc).allow_unregistered().run(); 

    po::store(parsed, vm);  
    po::notify(vm); 

    if(vm.count("messagequeue"))
    {
        GlobalMessage::getSingleton().setQueueName(vm["messagequeue"].as<string>());
    }

    if(vm.count("nouserattention"))
    {
#ifdef _MSC_VER
        _CrtSetReportMode(_CRT_WARN, _CRTDBG_MODE_FILE);
        _CrtSetReportFile(_CRT_WARN, _CRTDBG_FILE_STDOUT);

        _CrtSetReportMode(_CRT_ERROR, _CRTDBG_MODE_FILE);
        _CrtSetReportFile(_CRT_ERROR, _CRTDBG_FILE_STDOUT);

        _CrtSetReportMode(_CRT_ASSERT, _CRTDBG_MODE_FILE);
        _CrtSetReportFile(_CRT_ASSERT, _CRTDBG_FILE_STDOUT);

        SetErrorMode(SEM_FAILCRITICALERRORS | SEM_NOGPFAULTERRORBOX | SEM_NOALIGNMENTFAULTEXCEPT | SEM_NOOPENFILEERRORBOX);

#ifndef DISABLE_STACKWALKER
        CrashHandler::getInstance(); 
#endif 

#endif

    } else
    {
#ifdef _MSC_VER
        CrashHandler::getInstance()->setCatchesExceptions(false); //can cause trouble, and locally we have debugger anyway
        SetErrorMode(0);
#endif
    }

    //initialize log barrier manager now . so there wont be race conditions later
    LogBarrierManager::get_instance() ; 
    boostMT::ConsoleOutput::get_instance(); 
    boostMT::EnvTime::get_instance();


    bool spawn_command = (vm.count("spawn") > 0) && (vm.count("messagequeue") == 0);
    bool list_testcases = vm.count("list") > 0;
    bool XML_output = vm.count("output_format") && (vm["output_format"].as<string>() == "XML");

    if(vm.count("default_timeout"))
    {
        boostMT::LogCheckTimeout::get_instance().set_default_timeout(  boost::posix_time::seconds (vm["default_timeout"].as<unsigned int>()) );
    }

    unsigned int repeat_count = 1;
    if(vm.count("repeat"))
    {
        repeat_count = vm["repeat"].as<unsigned int>();
    }             

    std::string test_unit_name = vm["testcase"].as<string>();//"AllTestCases";

    //init dbg prints after default timeout has been set
    dbg_prints::instance();

    // Initialize directory structure 
    // Methods inside are not thread safe, however when first process is started it will
    // create proper structure (on single thread), then all other processes will just check 
    // if directiries exists and will do nothing, so it can be safely done like this. 
    ensureDirectoryStructure();

    if(vm.count("help"))
    {
        cout << desc;
        return 0;
    } else if (list_testcases)
    {
        cout << "Listing all matching testcases:" << endl << endl;

        filterTestTree(argc, argv);

        TestRunner::listSelectedTestCases(argc, argv);
        return 0;
    } else if (vm.count("generate_makefile"))
    {
        filterTestTree(argc, argv);

        TestRunner tr(argc, argv);

        std::ofstream makefile(vm["generate_makefile"].as<std::string>().c_str(), std::ios_base::out);        tr.generateMakefile(makefile);
        
        return 0;
    } else if (spawn_command)
    {
        cout << "Running every test case in separate process." << endl;
        cout << "Running selected test cases " << boost::lexical_cast<string>(repeat_count) << " times."  << endl;

        filterTestTree(argc, argv);

        return TestRunner::runSelectedTestCases(argc, argv, repeat_count, vm["spawn"].as<unsigned int>(), vm["try_test"].as<unsigned int>()) ? 0 : 1;
    }
    else
    {
        XmlOutputIntegrator xmlOutputIntegrator(test_unit_name, XML_output);
        log_files_maker lfm;
        framework::register_observer(lfm);

#ifdef EACH_PROCESS_USES_ITS_OWN_DIRECTORY
        initializeTempDirectory(test_unit_name);
#endif

        int res = unit_test_main(user_init, argc, argv);
        
        if(0 == res) //PASSED
        {
            if(LeakReporter::LastLeaked)
            {
                res = 3;                
            }
        }

        LeakReporter::LastLeaked = false;

        // save return code and send result to TestRunner message queue
        GlobalMessage::getSingleton().returnCode = res;
        GlobalMessage::getSingleton().sendMessageIfQueueAssigned();

        cout << "Return code is: " << res << endl;
        return res;
    }

}
catch (std::invalid_argument & ex)
{
    std::cout << "std::invalid_argument: " << ex.what() << std::endl;
    return 2;
}
catch (boost::interprocess::interprocess_exception &ex)
{
    std::cout << "boost::interprocess::interprocess_exception: " << ex.what() << std::endl;
    return 2;
}
catch (boost::program_options::error &ex)
{
    std::cout << "boost::program_options::error: " << ex.what() << std::endl;
    return 2;
}
catch (std::exception &ex)
{
    std::cout << "std::exception: " << ex.what() << std::endl;
    return 2;
}
catch (...)
{
    cout << "ERROR: got unknown exception" << std::endl ;
    return 2;
}

