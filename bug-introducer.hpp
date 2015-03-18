
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

            ~PtrDestroyer();
        };

        struct Registry
        {
            static const int PassNr = -1;

            Registry();
            void init();
            static Registry &getInstance();
            bool query(int line);
            void registerBug(int line);

        private:

            static std::string makeKey(int line);
            static PtrDestroyer<Registry> instance;

            mutable boost::mutex mMutexBugs;
            std::set<std::string> mBugs;
            int mBugNr;
            bool mInitialized;
        };
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
