cmake_minimum_required (VERSION 2.8)
project (SUT_SSW_WORKAROUND)

#for OMHandleCloser.cpp
remove_definitions(-DOM_REUSABLE_STATECHART_IMPLEMENTATION) 

#for Init.cpp, LoggerPc.cpp
include_directories(
    ${FML_dir}/src/${RHAPSODY_GENERATED_DIR}
)

add_library(
    ${PROJECT_NAME}
    ${SSW_dir}/src/OXFramework/src/oxf/OMHandleCloser.cpp
    ${SSW_dir}/src/SSWinit/src/Init.cpp
    ${SSW_dir}/src/Logger/src/LoggerPc.cpp
)