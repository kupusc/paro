#include "bug-introducer.hpp"

namespace problem
{
    void initBugs()
    {
        bug_introducer::detail::Registry::getInstance().init();
    }
}

namespace bug_introducer
{
    namespace detail
    {

        PtrDestroyer<Registry> Registry::instance;

        template<typename T>
        PtrDestroyer<T>::~PtrDestroyer()
        {
            delete ptr;
        }


        Registry::Registry():mBugNr(PassNr),mInitialized(false)
        {
        }

        void Registry::init()
        {
            if(mInitialized)
                return;
            mInitialized = true;

            int argc = boost::unit_test::framework::master_test_suite().argc;
            char **argv = boost::unit_test::framework::master_test_suite().argv;

            namespace po = boost::program_options;

            po::options_description desc("Allowed options");
            desc.add_options()
                    ("bug", po::value< unsigned int >()->implicit_value(0), "Defines bug number.")
                    ("print_bugs", "Prints bugs when registered")
                    ;

            po::variables_map vm;

            po::parsed_options parsed = po::command_line_parser(argc, argv).options(desc).allow_unregistered().run();

            po::store(parsed, vm);
            po::notify(vm);

            if(vm.count("print_bugs"))
            {
                std::cout << "bug_introducer::Bugs " << mBugs.size() << std::endl;
                int nr = 0;
                for(std::set<std::string>::const_iterator i = mBugs.begin(); mBugs.end() != i; ++i)
                {
                    std::cout << ++nr << " " << *i << std::endl;
                }
            }

            if(vm.count("bug"))
            {
                mBugNr = vm["bug"].as<unsigned int>();
                std::cout << "bug_introducer::Bug " <<mBugNr << std::endl;
            }
        }

        Registry &Registry::getInstance()
        {
            if(!instance.ptr)
            {
                instance.ptr = new Registry();
            }
            return *instance.ptr;
        }

        bool Registry::query(int line)
        {
            boost::mutex::scoped_lock guard(mMutexBugs);

            int nr = 0;
            std::string const key = makeKey(line);
            for(std::set<std::string>::const_iterator i = mBugs.begin(); mBugs.end() != i; ++i)
            {
                ++nr;
                if(*i == key)
                    break;
            }
            return (mBugNr != PassNr) && (mBugNr == nr || mBugNr > (int)mBugs.size());
        }

        void Registry::registerBug(int line)
        {
            boost::mutex::scoped_lock guard(mMutexBugs);

            int nr = 0;
            std::string const key = makeKey(line);
            mBugs.insert(key);
        }

        std::string Registry::makeKey(int line)
        {
            std::stringstream ss;
            ss << line;
            return ss.str();
        }
    }
}

