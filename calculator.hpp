#pragma once

#include <boost/function.hpp>
#include <vector>
#include <boost/date_time.hpp>

namespace problem
{
    void initBugs();

    /** @brief Interface for Randomization*/
    struct IRandomize
    {
	virtual ~IRandomize();
	virtual int get42();
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

    struct Calculator
    {
        Calculator();

	/** @brief returns The Answer To The Ultimate Question*/	
	int return42();

	/** @brief returns the sum of integers */
	int returnSum(int a, int b);

	/** @brief The same but using delegation*/
	int return42UsingRandomNumbers(IRandomize &engine);

	/** @brief Time inefficient  version, without a possibility to mock with dynamic polymorphism (WHAT TO DO :O)*/
	int return42UsingLegacyRandom();

        /** @brief Finds first i >= 0, that predicate(start + i * step) is true
        *
        * Pseudocode:
        * var
        *   f: Float;
        *   i: Integer;
        * begin
        *   f := start;
        *   i := 0;
        *   while not predicate(f) do
        *   begin
        *     f := f + step;
        *     i := i + 1;
        *   end;
        *   Result := i;
        * end;
        *
        */
        unsigned int findFirst(IPredicate &predicate, float start, float step);

        /** @brief Modifies "data" with "convert" function object
        *
        * For each i in [0, data.size()-1]
        *   data[i] = convert(data[i])
        *
        * "convert" will be called once per each "data" item.
        */
        void calcForEach(boost::function<int(int)> convert, std::vector<int> &data);

        /** @brief Makes image transparent using command-line tools
        *
        * Throws std::runtime_error when command fails.
        * @param imageIn Input image
        * @param imageOut Output image
        */
        void makeTransparent(ISystem &system, const std::string &imageIn, const std::string &imageOut);

        /** @brief Does "some" processing in parallel
        *
        * Given "some" function "f" this method calculates:
        * f(input) + e
        * where "e" is a small error
        *
        * Function value depends only on input (not on the number of tasks, or some other outside parameters)
        *
        * @param numberOfTasks Number of tasks on which processing should run. Should be more than 0.
        * @param input Input on which result depends
        * @return Resuls of a function "f"
        */
        float runParallel(IThreadPool &threadPool, int numberOfTasks, float input);

        /** @brief Just calls "take" on receiver
        */
        void sendCustomStruct(ICustomStructReceiver &receiver, const std::string &aString, float aFloat, const std::map<int, bool> &aMap);
    };

}

