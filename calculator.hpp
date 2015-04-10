#pragma once

#include "interfaces.h"
#include <vector>

namespace problem
{
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

