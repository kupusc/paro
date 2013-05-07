#ifndef MT_PATHS_H_4HBH8I3M
#define MT_PATHS_H_4HBH8I3M

#include <string>
#include <boost/filesystem.hpp>

namespace original_boost_mt_core
{
    namespace test_framework
    {
        /** @brief Relative path for logs
        * 
        * To get absolute one use: MT_ROOT_PATH / RELATIVE_LOG_PATH
        * Example value: 
        *   /logs/FSMr2/
        */
        extern const std::string RELATIVE_LOG_PATH;
        
        /** @brief Relative path to temp folder
        * 
        * To get absolute one use: MT_ROOT_PATH / RELATIVE_TMP_PATH
        * Example value: 
        *   /tmp/
        */
        extern const std::string RELATIVE_TMP_PATH;
        
        /** @brief Absolute domain's framework root
        *
        * Example value: 
        *   C:/ ... /C_Test/SC_OAM/SWM_SoftwareManagement/MT/
        * Set up in init.cpp
        */
        extern boost::filesystem::path MT_ROOT_PATH;
        
        /** @brief Absolute per-testcase tmp path
        *
        * As name indicates, value may vary from test to test.
        * Example value: 
        *   C:/ ... /C_Test/SC_OAM/SWM_SoftwareManagement/MT/tmp/ActivateSDSF_Timeout_105854855/
        * Set up in init.cpp
        */
        extern boost::filesystem::path PER_TESTCASE_TMP_PATH;
    }
}

#endif // MT_PATHS_H_4HBH8I3M
