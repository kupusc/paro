cmake_minimum_required (VERSION 2.8)
project (SUT_SSW)

set(SSW_dir ${OAM_ROOT}/SSW_SupportSoftware)

set(OXFSources
    #${SSW_dir}/src/OXFramework/src/oxf/ccsOS.cpp
    ${SSW_dir}/src/OXFramework/src/oxf/IOxfEventSender.cpp
    #${SSW_dir}/src/OXFramework/src/oxf/ntos.cpp - replaced by version prepared for time forwarer in tests
    ${SSW_dir}/src/OXFramework/src/oxf/OMAnimHelper.cpp
    ${SSW_dir}/src/OXFramework/src/oxf/OMAnimReactive.cpp
    ${SSW_dir}/src/OXFramework/src/oxf/OMDefaultInBound.cpp
    ${SSW_dir}/src/OXFramework/src/oxf/OMDefaultOutBound.cpp
    ${SSW_dir}/src/OXFramework/src/oxf/OMDefaultReactivePort.cpp
    ${SSW_dir}/src/OXFramework/src/oxf/OMDelay.cpp
    ${SSW_dir}/src/OXFramework/src/oxf/OMEvent.cpp
    ${SSW_dir}/src/OXFramework/src/oxf/OMMainThread.cpp
    ${SSW_dir}/src/OXFramework/src/oxf/ommemorymanager.cpp
    ${SSW_dir}/src/OXFramework/src/oxf/OMMemoryManagerSwitchHelper.cpp
    ${SSW_dir}/src/OXFramework/src/oxf/OMMemoryManagerSwitchHelperImpl.cpp
    ${SSW_dir}/src/OXFramework/src/oxf/OMMemoryManagerWrapper.cpp
    ${SSW_dir}/src/OXFramework/src/oxf/OMNotifier.cpp
    ${SSW_dir}/src/OXFramework/src/oxf/OMOSEventGenerationParams.cpp
    ${SSW_dir}/src/OXFramework/src/oxf/omprotected.cpp
    ${SSW_dir}/src/OXFramework/src/oxf/omreactive.cpp
    ${SSW_dir}/src/OXFramework/src/oxf/omstring.cpp
    ${SSW_dir}/src/OXFramework/src/oxf/omthread.cpp
    ${SSW_dir}/src/OXFramework/src/oxf/OMThreadManager.cpp
    ${SSW_dir}/src/OXFramework/src/oxf/OMTimeout.cpp
    ${SSW_dir}/src/OXFramework/src/oxf/OMTimerManager.cpp
    ${SSW_dir}/src/OXFramework/src/oxf/OMTimerManagerDefaults.cpp
    ${SSW_dir}/src/OXFramework/src/oxf/os.cpp
    #${SSW_dir}/src/OXFramework/src/oxf/oseOS.cpp
    #${SSW_dir}/src/OXFramework/src/oxf/osesocket.cpp
    ${SSW_dir}/src/OXFramework/src/oxf/oxf.cpp
    ${SSW_dir}/src/OXFramework/src/oxf/OXFDllGuards.cpp
    ${SSW_dir}/src/OXFramework/src/oxf/OXFEvents.cpp
    ${SSW_dir}/src/OXFramework/src/oxf/OXFRefManager.cpp
    ${SSW_dir}/src/OXFramework/src/oxf/OXFTimeManagement.cpp
    ${SSW_dir}/src/OXFramework/src/oxf/OXFTypeSafeContainers.cpp
    ${SSW_dir}/src/OXFramework/src/oxf/rhapsody_start.cpp
    ${SSW_dir}/src/OXFramework/src/oxf/state.cpp
)

if(WORKAROUND_EXCLUDE_OMTHREAD)
    # at least ALMAG's time forwarder needs fixed implementation and this is too buggy
    list(REMOVE_ITEM OXFSources ${SSW_dir}/src/OXFramework/src/oxf/omthread.cpp)
endif()

if(NOT WIN32)
    # on linux we use target compilation and this is used
    #TODO: will this handle C files?
    aux_source_directory(${SSW_dir}/src/SWBus/src SWBSources)
    #TODO: LoggerPc might be needed on Windows
    set(OSSpecificSources ${SSW_dir}/src/Logger/src/LoggerTarget.cpp)
endif()

add_library (${PROJECT_NAME}
    ${OXFSources}
    ${SWBSources}
    ${OSSpecificSources}
    
    ${SSW_dir}/src/OamAssert/src/oam_assert.cpp
    
    ${SSW_dir}/src/DomainsService/src/Identifier.cpp
    ${SSW_dir}/src/DomainsService/src/Service.cpp
    ${SSW_dir}/src/DomainsService/src/OXFService.cpp
    
    ${SSW_dir}/src/MemoryProtection/src/RwLockRead.cpp
    ${SSW_dir}/src/MemoryProtection/src/RwLockWrite.cpp
    
    ${SSW_dir}/src/XML/src/libXML/libCParser.cpp
    ${SSW_dir}/src/XML/src/libXML/libXmlNode.cpp
    ${SSW_dir}/src/XML/src/libXML/XmlNodeAttribute.cpp
    ${SSW_dir}/src/XML/src/libXML/XmlNodeElement.cpp
    
    ${SSW_dir}/src/AppContext/src/ALMAGContext.cpp
    ${SSW_dir}/src/AppContext/src/DMFSMContext.cpp
    ${SSW_dir}/src/AppContext/src/LMContext.cpp
    ${SSW_dir}/src/AppContext/src/SSWContext.cpp
    ${SSW_dir}/src/AppContext/src/BBCContext.cpp
    ${SSW_dir}/src/AppContext/src/FCMContext.cpp
    ${SSW_dir}/src/AppContext/src/PMContext.cpp
    ${SSW_dir}/src/AppContext/src/SYSMContext.cpp
    ${SSW_dir}/src/AppContext/src/CMContext.cpp
    ${SSW_dir}/src/AppContext/src/FMContext.cpp
    ${SSW_dir}/src/AppContext/src/RPMAGContext.cpp
    ${SSW_dir}/src/AppContext/src/TMContext.cpp
    ${SSW_dir}/src/AppContext/src/CommonContext.cpp
    ${SSW_dir}/src/AppContext/src/FSPContext.cpp
    ${SSW_dir}/src/AppContext/src/SIMContext.cpp
    ${SSW_dir}/src/AppContext/src/DMCommonContext.cpp
    ${SSW_dir}/src/AppContext/src/HWMContext.cpp
    ${SSW_dir}/src/AppContext/src/SPMContext.cpp
    
    ${SSW_dir}/src/Logger/src/LoggerFactory.cpp
    ${SSW_dir}/src/Logger/src/ILoggerFactory.cpp
    ${SSW_dir}/src/Logger/src/UltimateLogger.cpp
    
    ${SSW_dir}/src/Localization/src/HWInfoImpl.cpp
)

add_subdirectory(SSW_WORKAROUND)

target_link_libraries(
    ${PROJECT_NAME}
    ${PROJECT_NAME}_WORKAROUND
)