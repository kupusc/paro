
#ifndef _BUG_INTRODUCER_CAN_BE_USED_ONCE_47129283
#define _BUG_INTRODUCER_CAN_BE_USED_ONCE_47129283
#else
#error "Bug introducer can be used only once..."
#endif

#ifndef _BUG_INTRODUCER_47129283
#define _BUG_INTRODUCER_47129283

#include <boost/thread/mutex.hpp>
#include <boost/test/unit_test.hpp>
#include <boost/program_options.hpp>
#include <set>
#include <iostream>
#include <sstream>
#include <stdexcept>

namespace bug_introducer
{
    namespace detail
    {
        template<typename T>
        struct PtrDestroyer
        {
            T *ptr;

            ~PtrDestroyer()
            {
                delete ptr;
            }
        };

        struct Registry
        {
            static const int PassNr = -1;

            Registry():mBugNr(PassNr),mInitialized(false)
            {
            }

            void init()
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

            static Registry &getInstance()
            {
                if(!instance.ptr)
                {
                    instance.ptr = new Registry();
                }
                return *instance.ptr;
            }

            bool query(int line)
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

            void registerBug(int line)
            {
                boost::mutex::scoped_lock guard(mMutexBugs);

                int nr = 0;
                std::string const key = makeKey(line);
                mBugs.insert(key);
            }

        private:
            static std::string makeKey(int line)
            {
                std::stringstream ss;
                ss << line;
                return ss.str();
            }

            static PtrDestroyer<Registry> instance;

            mutable boost::mutex mMutexBugs;
            std::set<std::string> mBugs;
            int mBugNr;
            bool mInitialized;
        };

        PtrDestroyer<Registry> Registry::instance; //< can be used only once anyway 
    }

    template<int line, bool IsBug = true>
    struct Bugify
    {
        static Bugify instance;

        Bugify():callCount(0)
        {
            if(IsBug)
                (void)detail::Registry::getInstance().registerBug(line);
        }

        void protectMaxCallCount()
        {
            if(++callCount > 2)
                throw std::runtime_error("No no no!");
        }

        int makeBug(int t)
        {
            return detail::Registry::getInstance().query(line) ? t + 1 : t;
        }

        float makeBug(float t)
        {
            return detail::Registry::getInstance().query(line) ? t + 0.1f : t;
        }

        template<typename K, typename V>
        std::map<K, V> makeBug(const std::map<K, V> &t)
        {
            if(detail::Registry::getInstance().query(line))
            {
                std::map<K, V> tmp = t;
                if(tmp.empty())
                {
                    tmp[K()] = V();
                } else
                {
                    tmp.erase(tmp.begin());
                }
                return tmp;
            } else
                return t;
        }

        unsigned int makeBug(unsigned int t)
        {
            return detail::Registry::getInstance().query(line) ? t + 1 : t;
        }

        bool makeBug(bool t)
        {
            return detail::Registry::getInstance().query(line) ? !t : t;
        }

        std::string makeBug(const std::string &t)
        {
            if(detail::Registry::getInstance().query(line))
            {
                return t.size() ? t.substr(1, 100) : "X";       
            } else
            {
                return t;
            }
        }

    private:
        int callCount;
    };

    template<int line, bool IsBug>
    Bugify<line, IsBug> Bugify<line, IsBug>::instance;

}

#define INTRODUCE_BUG(value) ::bug_introducer::Bugify<__LINE__>::instance.makeBug((value))
#define PROTECT_MAX_CALL_COUNT() ::bug_introducer::Bugify<__LINE__, false>::instance.protectMaxCallCount()

#endif // _BUG_INTRODUCER_47129283
