cmake_minimum_required (VERSION 2.8)
project (CORE_MT)

include(${CoreTestFramework_dir}/CMake/coremt.cmake)

aux_source_directory(${CoreTestFramework_dir}/common_stubs CommonStubsSources) 
aux_source_directory(${CoreTestFramework_dir}/helpers CommonHelpersSources)
aux_source_directory(${CoreTestFramework_dir}/test_framework TestFrameworkSources) 

#todo: fix it
if(WIN32)
aux_source_directory(${CoreTestFramework_dir}/test_framework/crashhandler CrashHandlerSources)
list(REMOVE_ITEM TestFrameworkSources ${CoreTestFramework_dir}/test_framework/ConsoleOutputHandlerLINUX.cpp)
else(WIN32)
#todo better check for linux
list(REMOVE_ITEM TestFrameworkSources ${CoreTestFramework_dir}/test_framework/ConsoleOutputHandlerWIN32.cpp)
list(REMOVE_ITEM CommonStubsSources ${CoreTestFramework_dir}/common_stubs/bosse_sct_stub.cpp)
endif(WIN32)


add_library(
    ${PROJECT_NAME}
    ${CommonStubsSources}
    ${CommonHelpersSources}
    ${TestFrameworkSources}
    ${CrashHandlerSources}
    
    ${CoreTestFramework_dir}/test_framework/tinyxml/tinyxml.cpp
    ${CoreTestFramework_dir}/test_framework/tinyxml/tinyxmlparser.cpp
    ${CoreTestFramework_dir}/test_framework/tinyxml/tinyxmlerror.cpp
)