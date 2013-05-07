cmake_minimum_required (VERSION 2.8)
project (ORIGINAL_BOOST_MT_CORE)

# set cmake options

set(TARGET_FSMr3 ON CACHE BOOL "Is this for FSMr3 of system module (FSMr2 otherwise)?")
set(TARGET_FSP OFF CACHE BOOL "Is this for FSP? (MCU otherwise)")

if(TARGET_FSMr3)
    set(STATIC_FSMrX_DIR FSMr3)
    set(MT_EXE_NAME "mt_fct")
else(TARGET_FSMr3)
    set(STATIC_FSMrX_DIR FSMr2)
    set(MT_EXE_NAME "mt")
endif(TARGET_FSMr3)

if(WIN32)
    if(TARGET_FSMr3)
        set(RHAPSODY_GENERATED_DIR WinX86_WN_FCT)
        set(RHAPSODY_GENERATE_COMPONENT WN_FCT_BOSSE)
        set(RHAPSODY_GENERATE_CONFIGURATION WinPcVisualBE)
    else(TARGET_FSMr3)
        set(RHAPSODY_GENERATED_DIR WinX86_WN_FCMD)
        set(RHAPSODY_GENERATE_COMPONENT WN_FCMD_BOSSE)
        set(RHAPSODY_GENERATE_CONFIGURATION WinPcVisualBE)
    endif(TARGET_FSMr3)
else()
    #linux
    if(TARGET_FSMr3)
        set(RHAPSODY_GENERATED_DIR LinuxX86_WN_FCT)
        set(RHAPSODY_GENERATE_COMPONENT WN_FCT)
        set(RHAPSODY_GENERATE_CONFIGURATION CCSLinuxGCC_X86)
    else(TARGET_FSMr3)
        set(RHAPSODY_GENERATED_DIR LinuxX86_WN_FCMD)
        set(RHAPSODY_GENERATE_COMPONENT WN_FCMD)
        set(RHAPSODY_GENERATE_CONFIGURATION CCSLinuxGCC_X86)
    endif(TARGET_FSMr3)
endif()

macro(replaceflag list from to)
  set(tmp ${${list}})
  if(${tmp} MATCHES ${from})
    string(REGEX REPLACE ${from} ${to} tmp "${tmp}")
  #else()
  #  set(tmp "${tmp} ${to}")
  endif()
  set(${list} ${tmp})
endmacro()

if(MSVC AND NOT MSVC_IDE)
  #helps parallelisation on emake
  replaceflag(CMAKE_CXX_FLAGS "/Zi" "/Z7")
  replaceflag(CMAKE_CXX_FLAGS_DEBUG "/Zi" "/Z7")
endif()

if(NOT DEFINED MT_SUBDIR)
    #some domains have this test framework somewhere else than SC_OAM/Domain/MT/
    set(MT_SUBDIR "MT")
endif()

# setup paths

get_filename_component(DEFAULT_WCDMA_ROOT ../../../../ ABSOLUTE)

set(WCDMA_ROOT ${DEFAULT_WCDMA_ROOT} CACHE PATH "WCDMA root directory (i.e. trunk checked out dir)")
set(OAM_ROOT_MT ${WCDMA_ROOT}/C_Test/SC_OAM)
set(OAM_ROOT ${WCDMA_ROOT}/C_Application/SC_OAM)
set(DomainTestFramework_dir ${OAM_ROOT_MT}/${DOMAIN_NAME}/${MT_SUBDIR} CACHE PATH "MT home dir")
set(CoreTestFramework_dir ${OAM_ROOT_MT}/MT_COMMONS/original_boost_mt_core CACHE PATH "Original boost MT core home dir")
set(Domain_dir ${OAM_ROOT}/${DOMAIN_NAME})
set(FML_dir ${OAM_ROOT}/FoundationModel)
set(II_dir ${OAM_ROOT}/InternalInterfaces)
set(MT_COMMONS_dir ${OAM_ROOT_MT}/MT_COMMONS)

# just to hide it from GUI
set(CMAKE_INSTALL_PREFIX "${DomainTestFramework_dir}" CACHE INTERNAL "")

MESSAGE("TARGET_FSMr3: ${TARGET_FSMr3}")
MESSAGE("TARGET_FSP: ${TARGET_FSP}")
MESSAGE("CMAKE_BINARY_DIR: ${CMAKE_BINARY_DIR}")
MESSAGE("BOOST_ROOT = $ENV{BOOST_ROOT}")
MESSAGE("WCDMA_ROOT = ${WCDMA_ROOT}")
MESSAGE("OAM_ROOT_MT = ${OAM_ROOT_MT}")
MESSAGE("OAM_ROOT = ${OAM_ROOT}")
MESSAGE("DomainTestFramework_dir = ${DomainTestFramework_dir}")
MESSAGE("CoreTestFramework_dir = ${CoreTestFramework_dir}")
MESSAGE("Domain_dir = ${Domain_dir}")

# code generation

        
add_custom_target(GenerateII
    COMMAND ${CMAKE_COMMAND} 
        -D PRP_path=${OAM_ROOT}/OamSw.prp 
        -D RPY_path=${II_dir}/InternalInterfaces.rpy
        -D COMPONENT=${RHAPSODY_GENERATE_COMPONENT}
        -D CONFIGURATION=${RHAPSODY_GENERATE_CONFIGURATION}
        -P ${CoreTestFramework_dir}/CMake/rhapsodygenerator.cmake)

add_custom_target(GenerateFML
    COMMAND ${CMAKE_COMMAND} 
        -D PRP_path=${OAM_ROOT}/OamSw.prp 
        -D RPY_path=${FML_dir}/FoundationModel.rpy
        -D COMPONENT=${RHAPSODY_GENERATE_COMPONENT}
        -D CONFIGURATION=${RHAPSODY_GENERATE_CONFIGURATION}
        -P ${CoreTestFramework_dir}/CMake/rhapsodygenerator.cmake)
        
add_custom_target(Generate${DOMAIN_NAME}
    COMMAND ${CMAKE_COMMAND} 
        -D PRP_path=${OAM_ROOT}/OamSw.prp 
        -D RPY_path=${Domain_dir}/${DOMAIN_NAME}.rpy
        -D COMPONENT=${RHAPSODY_GENERATE_COMPONENT}
        -D CONFIGURATION=${RHAPSODY_GENERATE_CONFIGURATION}
        -P ${CoreTestFramework_dir}/CMake/rhapsodygenerator.cmake)

add_custom_target(GenerateAll DEPENDS GenerateII GenerateFML Generate${DOMAIN_NAME})

# todo: use this - subproject probably need to output there
link_directories(${DomainTestFramework_dir}/lib)

# todo: output to bin/
#set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${DomainTestFramework_dir}/bin)

# boost

set(Boost_USE_MULTITHREAD ON) #set a flag
set(Boost_USE_STATIC_LIBS OFF)
find_package(Boost 1.46.1 COMPONENTS unit_test_framework thread date_time regex filesystem serialization system program_options REQUIRED)
include_directories(${INCLUDE_DIRECTORIES} ${Boost_INCLUDE_DIRS})
link_directories(${LINK_DIRECTORIES} ${Boost_LIBRARY_DIRS})
set(liblist boost_program_options)

# WCDMA Includes and defines (Used by FML, Domain and MT)

include_directories(
    ${OAM_ROOT}/SSW_SupportSoftware/src/targetagnostic
    ${OAM_ROOT}/SSW_SupportSoftware/src/OXFramework/src
    ${OAM_ROOT}/SSW_SupportSoftware/src/OXFramework/src/oxf
    ${OAM_ROOT}/SSW_SupportSoftware/src/RAML/src
    ${OAM_ROOT}/SSW_SupportSoftware/src/XML/src/libXML
    ${OAM_ROOT}/SSW_SupportSoftware/src/XML/src
    ${OAM_ROOT}/SSW_SupportSoftware/src/SWBus/src
    ${OAM_ROOT}/SSW_SupportSoftware/src/
    ${OAM_ROOT}/SSW_SupportSoftware/src/Logger
    ${OAM_ROOT}/SSW_SupportSoftware/src/AppContext
    ${OAM_ROOT}/SSW_SupportSoftware/src/Localization
    ${OAM_ROOT}/SSW_SupportSoftware/src/Localization/inc    
    ${OAM_ROOT}/Include_Path/Oam
    ${OAM_ROOT}/Include_Path/swbus_src
    ${OAM_ROOT}/Include_Path/Messages
# todo: MessageId_Oam.h is defined multiple times... worst definition is in this directory
    ${OAM_ROOT}/include/definitions    
    ${OAM_ROOT}/InternalInterfaces/include
    ${OAM_ROOT}/InternalInterfaces/src/${RHAPSODY_GENERATED_DIR}
    ${WCDMA_ROOT}/I_Interface/Global_Env/Messages
    ${WCDMA_ROOT}/I_Interface/Global_Env/Definitions
    ${WCDMA_ROOT}/I_Interface/Application_Env/Definitions
    ${WCDMA_ROOT}/I_Interface/Application_Env/Messages
    ${WCDMA_ROOT}/I_Interface/Application_Env/Interfaces
    ${WCDMA_ROOT}/I_Interface/Application_Env/Wn_Env/Bs_Env/Definitions
    ${WCDMA_ROOT}/I_Interface/Application_Env/Wn_Env/Bs_Env/Messages
    ${WCDMA_ROOT}/I_Interface/Platform_Env/MCUHWAPI_ENV/Definitions
    ${WCDMA_ROOT}/I_Interface/Platform_Env/MCUHWAPI_ENV/Messages
    ${WCDMA_ROOT}/I_Interface/Platform_Env/CCS_ENV/ServiceInterface
    ${WCDMA_ROOT}/I_Interface/Platform_Env/DSPHWAPI_ENV/Definitions
    ${WCDMA_ROOT}/I_Interface/Platform_Env/DSPHWAPI_ENV/Messages
    ${WCDMA_ROOT}/I_Interface/Platform_Env/Definitions
    ${WCDMA_ROOT}/I_Interface/Platform_Env/Messages
)

if(WIN32)
include_directories(
    ${OAM_ROOT}/SSW_SupportSoftware/src/OXFramework/src/osconfig/WIN32
    ${OAM_ROOT}/Include_Path/bosse/Win32Includes
)
else()
include_directories(
    ${OAM_ROOT}/SSW_SupportSoftware/src/OXFramework/src/osconfig/Linux
)
endif()

#todo: half of those probably not needed...
add_definitions(
    -D_USE_32BIT_TIME_T
    -DDO_NOT_USE_BSHEAP
    -DHWW_USE_DIRECT_OSE_SEND
    -DOM_NO_RCS_ID
    -DMEDIATOR
    -DRTM_SUPPORTED
    -D_DEBUG
    #oam defines
    -DFLEXI
    #ccs
    -D__CCS_INLINE__=inline
    -DCCS_LITTLE_ENDIAN
    -DCCS_LINUX
    #oxf
    -DRESERVE_MESSAGE_LIST
    -DCANCEL_TIMEOUT_EVENTS    
    -DOMOXF
    -DOM_USE_STL
    -DOM_REUSABLE_STATECHART_IMPLEMENTATION
    -DOM_NO_FRAMEWORK_MEMORY_MANAGER
    #todo: cmake includes boost, do we need this?
    -DBOOST_ALL_NO_LIB
    -DBOOST_TEST_NO_MAIN
    -DBOOST_PROGRAM_OPTIONS_DYN_LINK    
    #for tiny xml
    -DTIXML_USE_STL
)

if(TARGET_FSMr3)
add_definitions(
    -DREL3
    -DFLEXI_REL3
    -DRP3DYN_CFG_USE_HW_DBG_PRNT 
    -DRP3DYN_CFG_SHOW_ALL_LOGS
)
else()
add_definitions(
    -DREL2
    -DFLEXI_REL2
)
endif()

if(WIN32)
add_definitions(
    -DBOOST_ALL_DYN_LINK
    #bosseish?
    -DOM_SCT
    -D__SCT__
    -DHOST_COMPILATION
    #TODO: half of those not needed?
    -D__MSC__
    -D_AFXDLL
    -D_CONSOLE
    -D_MBCS
    -D_WINDOWS    
    -DWINDOWS
    -D_SCL_SECURE_NO_WARNINGS
    -D_CRT_SECURE_NO_DEPRECATE
    -D_WIN32_WINNT=0x0501 #for files included by stackwalker
)
else()
add_definitions(
    -DTARGET_COMPILATION
    -DLINUX
    -D_itoa=OMitoa
    -DNO_STD_NAMESPACE
    -DWAM
    -DDISABLE_STACKWALKER
    -DUSE_IOSTREAM
    -D__GCC
    -DUSE_CCS
    -DCCS_LINUX
    -DLITTLE_ENDIAN
)
endif()

if(CMAKE_COMPILER_IS_GNUCXX)
    set(CMAKE_CXX_FLAGS "-Wno-deprecated -fpermissive")
endif()

# Subprojects

add_subdirectory(CMake/SSW)

# FML includes (used by FML, Domain and MT)

include_directories(
    ${FML_dir}/src/targetagnostic/
    ${FML_dir}/src/include
    ${FML_dir}/src/${RHAPSODY_GENERATED_DIR}
)

add_subdirectory(CMake/FoundationModel)

add_subdirectory(CMake/InternalInterfaces)

# Common MT itself

add_subdirectory(CMake/CoreMT)

# Domain includes (used by Domain and parts of MT)

include_directories(
    ${Domain_dir}/src/targetagnostic/
    ${Domain_dir}/src/include
    ${Domain_dir}/src/ServiceImpl
    ${Domain_dir}/src/${RHAPSODY_GENERATED_DIR}
)

add_subdirectory(CMake/Domain)

# Domain MT itself

include(${DomainTestFramework_dir}/CMake/domainsources.cmake)

if(MSVC)
    # if we used the version from linux, MS Visual would append /$(TargetName)/ path
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${DomainTestFramework_dir}/app/exe)
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${DomainTestFramework_dir}/app/exe)
else()
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${DomainTestFramework_dir}/app/exe)
endif()

if(WIN32)
    set(OXF_OS_SOURCE ${DomainTestFramework_dir}/sut/SSW_SupportSoftware/OXFramework/ntos_mt.cpp)
else()
    set(OXF_OS_SOURCE ${DomainTestFramework_dir}/sut/SSW_SupportSoftware/OXFramework/LinuxOS_mt.cpp)
endif()

add_executable (
    ${MT_EXE_NAME}
    
    ${DomainSources}
    
    # todo: move it somewhere
    ${DomainTestFramework_dir}/replacement/FORE_Global_Pkg.cpp
    ${DomainTestFramework_dir}/replacement/DBLogger.cpp
    ${DomainTestFramework_dir}/replacement/Registry.cpp
    
    # used by time forwarder
    ${OXF_OS_SOURCE}
)

if(WIN32)
    #TODO: blocked by CUdpPrintSocket::opOpenSocket
    set(OS_LIBRARIES wsock32)
else()
    # boost::interprocess needs this
    set(OS_LIBRARIES rt)
endif()

add_subdirectory(CMake/SSW_FML_Workaround)

target_link_libraries(${MT_EXE_NAME}
    SSW_FML_Workaround
    CORE_MT
    SUT_${DOMAIN_NAME}
    SUT_FoundationModel
    SUT_InternalInterfaces
    SUT_SSW
    ${Boost_LIBRARIES}
    
    ${OS_LIBRARIES}
)

# todo: need to learn what is this

# add profiling/coverage support
#set_target_properties(
#	TestCases
#	PROPERTIES  COMPILE_FLAGS "${COMPILE_FLAGS} ${coverage_flags} ${profiling_flags} ${mleak_flags}"
#	LINK_FLAGS "${LINK_FLAGS} ${coverage_flags} ${profiling_flags}"
#)

# add coverage/profiling support during linking of the whole
#set_target_properties(${CMAKE_PROJECT_NAME} 
#	PROPERTIES LINK_FLAGS "${LINK_FLAGS} ${coverage_flags} ${profiling_flags}"
#)
