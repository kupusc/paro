#include <boost/program_options.hpp>
#include <boost/scoped_array.hpp>
#include <iostream>
#include <string>
#include <deque>
#include <boost/lexical_cast.hpp>

#ifdef LINUX
#include <sys/stat.h>
#include <sys/types.h>
#else
#include <windows.h>
#endif

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

typedef std::deque<std::string> Output;

Output run(const std::string &command)
{
    std::deque<std::string> result;
    // Starts process and redirect (through pipe) output to vector<string>

    size_t const MAX_BUFFER = 1 * 1000 * 1000;
    boost::scoped_array<char> psBuffer(new char[MAX_BUFFER]);
    FILE   *pPipe;

    if ((pPipe = popen((command + " 2>&1").c_str(), POPEN_FLAGS)) == NULL)
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
        result.push_back(line);
    }

    if (feof(pPipe))
    {
        pclose(pPipe);
    }
    else
    {
        throw std::runtime_error("error closing pipe while running command: \"" + command + "\"");
    }

    return result;
}

bool analyze(const Output &output, int &bugsCount, bool verbose = false)
{
    bool hadNoErrors = false;
    for(Output::const_iterator i = output.begin(); output.end() != i; ++i)
    {
        if(verbose)
            std::cout << "    ::out:: " << *i << std::endl;

        static const std::string BugsCountStr("bug_introducer::Bugs ");
        if(i->find(BugsCountStr) != std::string::npos)
        {
            bugsCount = boost::lexical_cast<int>(i->substr(BugsCountStr.size(), 1000));                
            if(verbose)
                std::cout << "Found bugs count " << bugsCount << std::endl;
        }

        static const std::string NoErrorsDetected("*** No errors detected");
        if(i->find(NoErrorsDetected) != std::string::npos)
        {
            hadNoErrors = true;
            if(verbose)
                std::cout << "Tests passed" << std::endl;
        }
    }

    if(verbose && !hadNoErrors)
        std::cout << "Tests failed" << std::endl;

    return hadNoErrors;
}

int main(int argc, char **argv) try
{
    namespace po = boost::program_options;

    po::options_description desc("Allowed options");
    desc.add_options()
        ("pass_nr", po::value<int>()->default_value(-1), "Which bug number means PASS.")
        ("bugs_count", po::value<int>()->default_value(-1), "Number of bugs to check")
        ("input", po::value<std::string>(), "Input program name")
        ("help", "Prints help")
        ("verbose", "Verbose output")
        ;     

    po::variables_map vm;

    po::parsed_options parsed = po::command_line_parser(argc, argv).options(desc).run(); 

    po::store(parsed, vm);  
    po::notify(vm);

    if(vm.count("help"))
    {
        std::cout << desc;
        return 0;
    }

    int bugsCount = vm["bugs_count"].as<int>();
    {
        Output output = run(vm["input"].as<std::string>() + " --print_bugs");

        int count = -1;
        if(!analyze(output, count, vm.count("verbose") > 0))
        {
            std::cout << "FAILED" << std::endl;
            return 0;
        }

        if(bugsCount <= 0)
        {
            if(count <= 0)
            {
                std::cout << "FAILED" << std::endl;
                return 0;
            }
            bugsCount = count;
        }
    }

    int fails = 0;
    for(int i = 1; i <= bugsCount; ++i)
    {
        if(vm.count("verbose"))
            std::cout << "Testing bug: " << i << std::endl;
            
        Output output = run(vm["input"].as<std::string>() + " --bug=" + boost::lexical_cast<std::string>(i));

        int count = -1;
        if(analyze(output, count, vm.count("verbose") > 0))
        {
            fails++;
        }            
    }

    if(vm.count("verbose"))
        std::cout << "\n\n\n";

    if(fails)
        std::cout << "FAILED (missed " << fails << " of " << bugsCount << " bugs)" << std::endl;
    else            
        std::cout << "PASSED" << std::endl;
    return 0;
} catch(std::exception &e)
{
    std::cout << "Exception " << typeid(e).name() << " \"" << e.what() << "\"";
}
