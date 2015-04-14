#pragma once

#include <boost/function.hpp>
#include <boost/date_time.hpp>

namespace problem
{
    void initBugs();

    /** @brief Interface for Randomization*/
    struct IRandomize
    {
        virtual ~IRandomize(){};
        virtual int get42() = 0;
    };

    /** @brief A predicate
    *
    * See http://en.wikipedia.org/wiki/Predicate_%28mathematical_logic%29
    */
    struct IPredicate
    {
        virtual ~IPredicate() {}

        virtual bool operator()(float value)=0;
    };

    struct IThreadPool
    {
        virtual ~IThreadPool() {}

        /** @brief Adds task to be processed by threads
        */
        virtual void addTask(boost::function<void()> task)=0;

        /** @brief Waits till all curent tasks are finished
        */
        virtual void join()=0;
    };

    struct ISystem
    {
        virtual ~ISystem() {}

        /** @brief Runs system command
        *
        * @param command Command do run
        * @param timeout Maximum time command may run, after which it should return with failure
        * @returns False on failure
        */
        virtual bool run(const char *command, boost::posix_time::time_duration timeout)=0;
    };

    struct CustomStruct
    {
        CustomStruct(const std::string &aString, float aFloat, const std::map<int, bool> &aMap)
            :mString(aString),mFloat(aFloat),mMap(aMap)
        {
        }
        std::string mString;
        float mFloat;
        std::map<int, bool> mMap;

    private:
        bool operator==(const CustomStruct &);
    };

    /** @brief This struct is a proof that I'm running out of real-life ideas
    */
    struct ICustomStructReceiver
    {
        virtual ~ICustomStructReceiver() {}
        virtual void take(const CustomStruct &custom)=0;
    };

    struct LegacyRandom
    {
    int get42();
    };
}
