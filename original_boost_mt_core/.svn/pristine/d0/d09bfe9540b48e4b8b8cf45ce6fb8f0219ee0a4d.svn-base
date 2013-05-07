#ifndef LEAK_REPORTER_H
#define LEAK_REPORTER_H

#ifdef _MSC_VER
#include <crtdbg.h>
#endif
//! Per-testcase memory leak reporter.
/*! It is best to add it as and attribute of a fixture. This way all tests using it will report leaks (if any) and fail
if leak was detected. Alternatively it can be instantiated in one testcase.
*
* To debug on allocation number run one testcase in debugger with following parameters:
* --detect_memory_leaks=123456789 -t <testcase name without *>
* And get console output (you may need adding breakpoint at the end of init.cpp).
* If memory leaked output will be like this:
* {177319} normal block at 0x039504A0, 4 bytes long.
* Data: <    > CD CD CD CD
* ...
* Where {177319} is the allocation number. It is cruicial to run in debugger with such above parameters to get this number,
 otherwise it will be different (for instance, if you run from console).
*
* With this number, we can run debugger again:
* --detect_memory_leaks=177319 -t <testcase name without *>
* This time it will break when leaking memory is allocated.
* \warning If allocation order differs from run to run (for instance when threads doing things in different order) this
method will not work
*/
class LeakReporter 
{ 
public:
    LeakReporter();

    ~LeakReporter();

    //! If called, leaks won't be reported.
    void setLeaksAreExpected();

    //! True if last use of LeakReporter reported memory leaks.
    static bool LastLeaked;

private:
#ifdef _MSC_VER
    _CrtMemState memStateBeforeTest;
#endif
    bool mLeaksAreExpected;

};


#endif //LEAK_REPORTER_H
