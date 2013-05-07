Introduction
============

For reference on how to generate HTML from this file or how to edit see [markdown](http://en.wikipedia.org/wiki/Markdown)
This document refers to all test frameworks based on Orginal Boost MT Core later refered to as OBMC.


Bjam compilation
================


How to compile tests intended for FSMr2?
----------------------------------------


Go to:

    C_Test/SC_OAM/<domain name>/MT/

To generate all sources from rhapsody (so domain, foundation model, internal interfaces):

    bjam sut_gen

To compile everything (including SUT):

    bjam [--fastbuild] --scan -j3 [toolset=msvc-10.0]

where:

* `--fastbuild` (optional)

    Improves build performance a bit.
    
* `--scan`
    
    With this SUT will be compiled also. Otherwise only tests are compiled which is quicker.
    
* `-j3`
    
    Compiles on 3 threads concurrently.
    
* `toolset=msvc-10.0` (optional)

    Only if you want to use visual studio 2010 (instead of default 2005). For Visual Studio 2012 use `msvc-11.0`
    


If you have changed only test, to compile faster issue:

    bjam -j3

So without `--scan`. If you get linking errors, try with `--scan` again as above.


How to compile tests intended for FSMr3?
----------------------------------------

As above, but after `bjam` add FCT, so for example:

    bjam FCT -j3


CMake compilation
=================


Though most of the CMake and compiler generated files are out-of-the-source in the build tree, 
resulting executable is copied to `app/exe` for historical reasons.

Linux
-----

Go to:

    C_Test/SC_OAM/<domain name>/MT/

Now issue commands:

    mkdir <output>
    cd <output>
    cmake ../
    
Where:

* <domain name>

    For instance DM_RPMAG

* <output>

    Directory of your choice where to put build files.

    
Windows - MSVC 2005, MSVC 2012
-------

The easiest way is to use CMake-GUI.

1. Put `C_Test/SC_OAM/<domain name>/MT/` into "Where is the source code"

2. Select where to put resulting solution and object files with "Where to build the binaries"

3. Press *Configure*

4. Select MSVC version

5. Press *Configure* again

6. Press *Generate*

Now you can open Visual Solution file from output in 2., or compile it from command line.


Windows - NMake, JOM, Electric Cloud
------------------------------------

Compilation is with MSVC 2005 from OSESEE.

Go to:

    C_Test/SC_OAM/<domain name>/MT/
    
To generate makefiles issue following commands:
    
    md <output>
    set CMAKE_PATH="<your path to cmake>"
    "%CMAKE_PATH%\bin\cmake" DCMAKE_CXX_COMIPILER=C:\APPS\msvs\VC\bin\cl.exe DCMAKE_C_COMIPILER=C:\APPS\msvs\VC\bin\cl.exe --build ..\ -G "NMake Makefiles"

For nmake:

    cd <output>
    nmake
    
For [JOM](http://qt-project.org/wiki/jom) (it allows parallel building):

    cd <output>
    jom -j4
    
For Electric Cloud (it allows distributed building):

    C_Application\SC_OAM\setenv.bat WRU EC
    cd <output>
    emake --emake-root=C:\APPS\;"%CMAKE_PATH%";..\..\..\..\..\;"%BOOST_ROOT%" --emake-emulation=nmake --emake-autodepend=0
    
Of course for other sites replace `WRU` accordingly.


FSMr3
-----

For command line add `-DTARGET_FSMr3` to CMake's command line or select it from GUI.


Tests execution
===============


Help
----

To see what parameters are acceptable when running tests in boost's framework refer
to [boost pages](http://www.boost.org/doc/libs/1_46_1/libs/test/doc/html/utf/user-guide/runtime-config/reference.html)

To see additional parameters implemented for OAM purposes call:

    mt --help


How to run tests tests intended FSMr2?
--------------------------------------

To run, either go to `./app/exe` where `mt.exe` resides, and call:

    test_all.bat

or from `./`:
    
    run_test.bat [testcase name]

where:

* [testcase name] (optional)

    If provided will run only one testcase

Alternatively, you can issue full command by yourself from `./app/exe`:

    mt --detect_memory_leaks=0 --spawn [-t testcase/name]
    
Note that you can use wildcards for `testcase/name`. For instance:

    mt -t ut/rpm*
    
Will run all testcases that have full name starting with "ut/rpma", for instance (if such tests existed):

- ut/rpmag/adser/startup_ok
- ut/rpmag/multiradio/failure
- ut/rpmagisbetterthanalmag/yes


How to run tests tests intended FSMr3?
--------------------------------------

As above, but with `_fct` suffix in batch/exe files.
