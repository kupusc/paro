

#include "ccs_default_impl.h"
#include "sw_conf_table.h"
#include "dbg_prints.h"
#include <boost/filesystem.hpp>

// dbg_print implementation uses CCS . dont use dbg print in CCS stubs ! (unterminated recursive call will occur)


void CcsStubImplDefault::AaSysComMsgSend(void **message)
{
    dbg_prints::instance()->addPrint("CcsStubImplDefault::AaSysComMsgSend");
}
void * CcsStubImplDefault::AaSysComMsgCreate(const TAaSysComMsgId messageId,
        const TAaSysComMsgSize messagePayloadSize,
        const TAaSysComSicad messageTarget)
{
    dbg_prints::instance()->addPrint("CcsStubImplDefault::AaSysComMsgCreate");
    return 0;
}
EAaProEuRetVal
CcsStubImplDefault::AaProEuCreateAndStart( u32*                 euIdPtr,
        const char          *euNamePtr,
        TAaProEuEntryPoint  *euEntryPoint,
        u32                  euStackSize,
        u32                  euPriority,
        void*                euArgPtr,
        u32                  sizeOfeuArg )
{
    dbg_prints::instance()->addPrint("CcsStubImplDefault::AaProEuCreateAndStart");
    return EAaProEuRetVal_NoError;
}

TAaSysComCpid CcsStubImplDefault::AaSysComUserRegister(const TAaSysComCpid userCpid, const u32 euId)
{
    dbg_prints::instance()->addPrint("CcsStubImplDefault::AaSysComUserRegister");
    return 666;
}
TAaSysComSicad CcsStubImplDefault::AaSysComNmapGetSicad(const TBoard board, const TCpu cpu, const TTask task)
{
    dbg_prints::instance()->addPrint("CcsStubImplDefault::AaSysComNmapGetSicad");
    return 0;
}

void CcsStubImplDefault::AaGpuDurFree(TAaGpuDurHandle *handle)
{
    dbg_prints::instance()->addPrint("CcsStubImplDefault::AaGpuDurFree");
}
void * CcsStubImplDefault::AaSysMbPrepare(const TAaSysComMsgSize messagePayloadSize,
        const TAaSysComMsgId messageId,
        const TAaSysComSicad publisher,
        const EAaSysMbPublMode mode,
        const TAaSysMbZoneId zone)
{
    dbg_prints::instance()->addPrint("CcsStubImplDefault::AaSysMbPrepare");
    return 0;
}
EAaSysMbRetVal CcsStubImplDefault::AaSysMbSubscribe(const TAaSysComMsgId messageId,
        const TAaSysComSicad subscriber,
        const EAaSysMbSubsMode mode,
        const TAaSysMbZoneId zone)
{
    dbg_prints::instance()->addPrint("CcsStubImplDefault::AaSysMbSubscribe");
    return EAaSysMbRetVal_Ok;
}

void CcsStubImplDefault::AaSysComMsgDestroy(void **message)
{
    dbg_prints::instance()->addPrint("CcsStubImplDefault::AaSysComMsgDestroy");
}

EAaSysMbRetVal CcsStubImplDefault::AaSysMbPublish(void **payload)
{
    dbg_prints::instance()->addPrint("CcsStubImplDefault::AaSysMbPublish");
    return EAaSysMbRetVal_Ok;
}

u32 CcsStubImplDefault::AaProEuCurrent(void)
{
    dbg_prints::instance()->addPrint("CcsStubImplDefault::AaProEuCurrent");
    return 0;
}
TAaSysComNid CcsStubImplDefault::AaSysComGetOwnNid(void)
{
    dbg_prints::instance()->addPrint("CcsStubImplDefault::AaSysComGetOwnNid");
    return 0;
}
TAaSysComSicad CcsStubImplDefault::AaSysComSicadGet(const TAaSysComCpid userCpid,const TAaSysComNid userNid)
{
    dbg_prints::instance()->addPrint("CcsStubImplDefault::AaSysComSicadGet");
    return 123;
}
void * CcsStubImplDefault::AaSysComMsgGetPayload(const void *message)
{
    dbg_prints::instance()->addPrint("CcsStubImplDefault::AaSysComMsgGetPayload");
    return 0;
}
TAaSysComMsgSize CcsStubImplDefault::AaSysComMsgGetPayloadSize(const void *message)
{
    dbg_prints::instance()->addPrint("CcsStubImplDefault::AaSysComMsgGetPayloadSize");
    return 0;
}
TAaSysComMsgId CcsStubImplDefault::AaSysComMsgGetId(const void *message)
{
    dbg_prints::instance()->addPrint("CcsStubImplDefault::AaSysComMsgGetId");
    return 0;
}
TAaSysComSicad CcsStubImplDefault::AaSysComMsgGetSender(const void *message)
{
    dbg_prints::instance()->addPrint("CcsStubImplDefault::AaSysComMsgGetSender");
    return 0;
}
TBoard CcsStubImplDefault::AaSysComNmapGetBoard(const TAaSysComSicad sicAddress)
{
    dbg_prints::instance()->addPrint("CcsStubImplDefault::AaSysComNmapGetBoard");
    return 0;
}
TCpu CcsStubImplDefault::AaSysComNmapGetCpu(const TAaSysComSicad sicAddress)
{
    dbg_prints::instance()->addPrint("CcsStubImplDefault::AaSysComNmapGetCpu");
    return 0;
}
TAaSysComSicad CcsStubImplDefault::AaSysComMsgGetReceiver(const void *message)
{
    dbg_prints::instance()->addPrint("CcsStubImplDefault::AaSysComMsgGetReceiver");
    return 0;
}
TTask CcsStubImplDefault::AaSysComNmapGetTask(const TAaSysComSicad sicAddress)
{
    dbg_prints::instance()->addPrint("CcsStubImplDefault::AaSysComNmapGetTask");
    return 0;
}
void CcsStubImplDefault::AaSysComMsgSetSender(const void *message,const TAaSysComSicad messageSource)
{
    dbg_prints::instance()->addPrint("CcsStubImplDefault::AaSysComMsgSetSender");
}
TAaSysComCpid CcsStubImplDefault::AaSysComUserDeregister(const TAaSysComCpid userCpid)
{
    dbg_prints::instance()->addPrint("CcsStubImplDefault::AaSysComUserDeregister");
    return 0;
}
u32 CcsStubImplDefault::AaConfigRadGetValue(u32 tag)
{
    dbg_prints::instance()->addPrint("CcsStubImplDefault::AaConfigRadGetValue");
    return 0;
}
const char* CcsStubImplDefault::AaConfigRadGetTagString(u32 tag)
{
    dbg_prints::instance()->addPrint("CcsStubImplDefault::AaConfigRadGetTagString");
    return 0;
}
EAaConfigRet CcsStubImplDefault::AaConfigRadRegisterDomain(u32 domain,
        const char* nameStringPtr,
        void (*initializeParameters)(void))
{
    dbg_prints::instance()->addPrint("CcsStubImplDefault::AaConfigRadRegisterDomain");
    return EAaConfigRet_Error;

}
EAaConfigRet CcsStubImplDefault::AaConfigRadSetValue(u32 tag, u32 value)
{
    dbg_prints::instance()->addPrint("CcsStubImplDefault::AaConfigRadSetValue");
    return EAaConfigRet_Error;
}
EAaConfigRet CcsStubImplDefault::AaConfigRadSetDefault(u32         tag,
        const char* stringPtr,
        u32         initialValue)
{
    dbg_prints::instance()->addPrint("CcsStubImplDefault::AaConfigRadSetDefault");
    return EAaConfigRet_Error;
}
EAaConfigRet CcsStubImplDefault::AaConfigRadSetMaxTagCount(u32 domain, u32 count)
{
    dbg_prints::instance()->addPrint("CcsStubImplDefault::AaConfigRadSetMaxTagCount");
    return EAaConfigRet_Error;
}
EAaSysTimeRetVal CcsStubImplDefault::AaUnixTimeGet(SAaBtsTimeval * const timePtr)
{
    dbg_prints::instance()->addPrint("CcsStubImplDefault::AaUnixTimeGet");
    return EAaSysTimeRetVal_Error;
}
EAaFileRet CcsStubImplDefault::AaFileClose(TAaFile *stream)
{
    dbg_prints::instance()->addPrint("CcsStubImplDefault::AaFileClose");
    return EAaFileRet_Error;    
}
EAaFileRet CcsStubImplDefault::AaFileRemove(const char *fileName)
{
    dbg_prints::instance()->addPrint("CcsStubImplDefault::AaFileRemove");
    return EAaFileRet_Error;
}
void CcsStubImplDefault::va_AaSysLogPrint(const EAaSysLogSeverityLevel severityLevel,
        const char* unformattedStringPtr, va_list argptr )
{
    dbg_prints::instance()->addPrint("CcsStubImplDefault::AaSysLogPrint");
}
void CcsStubImplDefault::AaSysLogVPrintE(const EAaSysLogSeverityLevel severityLevel,
        const u32                    featureId,
        const char*                  unformattedStringPtr,
        va_list                      args)
{

    char buffer[1024*16] = {0};
    vsprintf(buffer, unformattedStringPtr, args);

    //string line(buffer);
    dbg_prints::instance()->addPrint(buffer);

}
TAaFile *CcsStubImplDefault::AaFileOpen(const char *fileName, const char *mode)
{
    dbg_prints::instance()->addPrint("CcsStubImplDefault::AaFileOpen");
    return 0;
}
size_t CcsStubImplDefault::AaFileRead(void *ptr, size_t size, size_t nitems, TAaFile *stream)
{
    dbg_prints::instance()->addPrint("CcsStubImplDefault::AaFileRead");
    return 0;   
}
size_t CcsStubImplDefault::AaFileWrite(void *ptr, size_t size, size_t nitems, TAaFile* stream)
{
    dbg_prints::instance()->addPrint("CcsStubImplDefault::AaFileWrite");
    return 0;
}
long CcsStubImplDefault::AaFileGetSize(TAaFile *stream)
{
    dbg_prints::instance()->addPrint("CcsStubImplDefault::AaFileGetSize");
    return 0;
}
TAaSysComSicad CcsStubImplDefault::AaSysComNmapGetSicAddress(const TBoard board,
        const TCpu cpu,
        const TTask task)
{
    dbg_prints::instance()->addPrint("CcsStubImplDefault::AaSysComNmapGetSicAddress");
    return 0;
}
TAaSysTime64 CcsStubImplDefault::AaSysTimeBcnGet(void)
{
    dbg_prints::instance()->addPrint("CcsStubImplDefault::AaSysTimeBcnGet");
    return 0;
}
EAaFileTftpErrorCode CcsStubImplDefault::AaFileTftpGet(const char *ipAddress,
        const char *srcFilename,
        const char *dstFilename)
{
    dbg_prints::instance()->addPrint("CcsStubImplDefault::AaFileTftpGet");
    return EAaFileTftpErrorCode_UndefinedError;
}
EAaConfigRet CcsStubImplDefault::AaConfigTagSetString(const char* const name,
        const char* const value)
{
    dbg_prints::instance()->addPrint("CcsStubImplDefault::AaConfigTagSetString");
    return EAaConfigRet_Error;
}
EAaProEuRetVal CcsStubImplDefault::AaProEuSetPri( u32 euId, u32 euPriority )
{
    dbg_prints::instance()->addPrint("CcsStubImplDefault::AaProEuSetPri");
    return EAaProEuRetVal_Error;
}
u32 CcsStubImplDefault::AaProEuGetPri(u32 euId)
{
    dbg_prints::instance()->addPrint("CcsStubImplDefault::AaProEuGetPri");
    return 0;
}
void CcsStubImplDefault::AaSemPost(TAaSem* semPtr)
{
    dbg_prints::instance()->addPrint("CcsStubImplDefault::AaSemPost");
}
void CcsStubImplDefault::AaSemWait(TAaSem* semPtr)
{
    dbg_prints::instance()->addPrint("CcsStubImplDefault::AaSemWait");
}
u32 CcsStubImplDefault::GetLteDownlinkFrequency(const u32 earfcn)
{
    dbg_prints::instance()->addPrint("CcsStubImplDefault::GetLteDownlinkFrequency");
    return 0;
}
u32 CcsStubImplDefault::GetLteUplinkFrequency(const u32 earfcn)
{
    dbg_prints::instance()->addPrint("CcsStubImplDefault::GetLteUplinkFrequency");
    return 0;
}
u32 CcsStubImplDefault::GetWcdmaDownlinkFrequency(const u32 earfcn)
{
    dbg_prints::instance()->addPrint("CcsStubImplDefault::GetWcdmaDownlinkFrequency");
    return 0;
}
u32 CcsStubImplDefault::GetWcdmaUplinkFrequency(const u32 earfcn)
{
    dbg_prints::instance()->addPrint("CcsStubImplDefault::GetWcdmaUplinkFrequency");
    return 0;
}
void CcsStubImplDefault::AaSysComMsgSetMtm(const void *message,const EAaSysComMtm requestedTransferMode)
{
    dbg_prints::instance()->addPrint("CcsStubImplDefault::AaSysComMsgSetMtm");
}
TAaGpuDurHandle* CcsStubImplDefault::AaGpuDurAlloc(char const * const name)
{
    dbg_prints::instance()->addPrint("CcsStubImplDefault::AaGpuDurAlloc");
    return 0;
}
void CcsStubImplDefault::AaGpuDurStart(TAaGpuDurHandle *handle)
{
    dbg_prints::instance()->addPrint("CcsStubImplDefault::AaGpuDurStart");
}
void CcsStubImplDefault::AaGpuDurStop(TAaGpuDurHandle *handle)
{
    dbg_prints::instance()->addPrint("CcsStubImplDefault::AaGpuDurStop");
}
void CcsStubImplDefault::AaFileFreeListDirArray(SAaFileDnode*** dirArray, u32 nfiles)
{
    dbg_prints::instance()->addPrint("CcsStubImplDefault::AaFileFreeListDirArray");
}
EAaFileRet CcsStubImplDefault::AaFileListDir(SAaFileDnode*** dirArray, u32* nfilesp, const char* path, TBoolean recursive)
{
    dbg_prints::instance()->addPrint("CcsStubImplDefault::AaFileListDir");
    return EAaFileRet_Error; 
}
char* CcsStubImplDefault::AaProEuGetName(u32 euId, char* buffer, u32 length)
{
    dbg_prints::instance()->addPrint("CcsStubImplDefault::AaProEuGetName");
    return 0;
}
TAaSysComCpid CcsStubImplDefault::AaSysComSicadGetCpid(const TAaSysComSicad sicAddress)
{
    dbg_prints::instance()->addPrint("CcsStubImplDefault::AaSysComSicadGetCpid");
    return 0;
}
void CcsStubImplDefault::AaSemCreateC( TAaSem** semPtr, u32      initialValue )
{
    dbg_prints::instance()->addPrint("CcsStubImplDefault::AaSemCreateC");
}
void CcsStubImplDefault::AaSemDestroy(TAaSem* semPtr)
{
    dbg_prints::instance()->addPrint("CcsStubImplDefault::AaSemDestroy");
}
void CcsStubImplDefault::AaSemGetValue(TAaSem*  semPtr, i32*     semValuePtr)
{
    dbg_prints::instance()->addPrint("CcsStubImplDefault::AaSemGetValue");
}
void* CcsStubImplDefault::AaSysComMsgReceiveFromEu(const u32 euId)
{
    dbg_prints::instance()->addPrint("CcsStubImplDefault::AaSysComMsgReceiveFromEu");
    return 0;
}
EAaSysTimeRetVal CcsStubImplDefault::AaSysTimeSleep(const TAaSysTime sleepTime, const EAaSysTimeScale scale)
{
    dbg_prints::instance()->addPrint("CcsStubImplDefault::AaSysTimeSleep");
    return EAaSysTimeRetVal_Error;
}

EAaFileRet CcsStubImplDefault::AaFileCopy(const char* srcPath, const char* destPath)
{
    dbg_prints::instance()->addPrint("CcsStubImplDefault::AaFileCopy");
    return EAaFileRet_Error;
}

void *CcsStubImplDefault::AaSysComMsgReceive(const u32 maxTimeToWait)
{
    dbg_prints::instance()->addPrint("CcsStubImplDefault::AaSysComMsgReceive");
    return 0;
}
EAaProEuRetVal CcsStubImplDefault::AaProCmdExec(const char * command, const char * args, u32 flags, int * retVal)
{
    dbg_prints::instance()->addPrint("CcsStubImplDefault::AaProCmdExec");
    return EAaProEuRetVal_Error;
}
TAaSysComHopId CcsStubImplDefault::AaSysComHopRegister(const TAaSysComSicad destinationAddress, const u32 metric, const TAaSysComLinkId linkId)
{
    dbg_prints::instance()->addPrint("CcsStubImplDefault::AaSysComHopRegister");
    return 0;
}
void CcsStubImplDefault::AaSemRwLockCreate(TAaSemRwLock** const lock)
{
    *lock = reinterpret_cast<TAaSemRwLock*>(new boost::mutex);
}
void CcsStubImplDefault::AaSemRwLockDestroy(TAaSemRwLock** const lock)
{
    delete reinterpret_cast<boost::mutex*>(*lock);
}
void CcsStubImplDefault::AaSemRwLockReadLock(TAaSemRwLock* const lock)
{
    boost::mutex* tmp = reinterpret_cast<boost::mutex*>(lock);
    tmp->lock();
}
void CcsStubImplDefault::AaSemRwLockReadUnlock(TAaSemRwLock* const lock)
{
    boost::mutex* tmp = reinterpret_cast<boost::mutex*>(lock);
    tmp->unlock();
}
void CcsStubImplDefault::AaSemRwLockWriteLock(TAaSemRwLock* const lock)
{
    boost::mutex* tmp = reinterpret_cast<boost::mutex*>(lock);
    tmp->lock();
}
void CcsStubImplDefault::AaSemRwLockWriteUnlock(TAaSemRwLock* const lock)
{
    boost::mutex* tmp = reinterpret_cast<boost::mutex*>(lock);
    tmp->unlock();
}
EAaConfigRet CcsStubImplDefault::AaConfigTagRegister(const char* const name, TAaConfigTagObserver* const callback)
{
    dbg_prints::instance()->addPrint("CcsStubImplDefault::AaConfigTagRegister");
    return EAaConfigRet_Ok;
}
EAaConfigRet CcsStubImplDefault::AaConfigTagUnregister(const char* const name, TAaConfigTagObserver* const callback)
{
    dbg_prints::instance()->addPrint("CcsStubImplDefault::AaConfigTagUnregister");
    return EAaConfigRet_Ok;
}
EAaGpuChecksumsRet CcsStubImplDefault::AaGpuChecksumsUninit(SAaGpuChecksumHandler* const handler)
{
    dbg_prints::instance()->addPrint("CcsStubImplDefault::AaGpuChecksumsUninit");
    return EAaGpuChecksumsRet_Ok; 
}
EAaGpuChecksumsRet CcsStubImplDefault::AaGpuChecksumsUpdate(SAaGpuChecksumHandler* const handler, const void* const data, const u32 length)
{
    dbg_prints::instance()->addPrint("CcsStubImplDefault::AaGpuChecksumsUpdate");
    return EAaGpuChecksumsRet_Ok; 
}
u32 CcsStubImplDefault::AaGpuChecksumsValueGet(SAaGpuChecksumHandler* const handler)
{
    dbg_prints::instance()->addPrint("CcsStubImplDefault::AaGpuChecksumsValueGet");
    return 0; 
} 
EAaGpuChecksumsRet CcsStubImplDefault::AaGpuAdler32Init(SAaGpuChecksumHandler* const handler)
{
    dbg_prints::instance()->addPrint("CcsStubImplDefault::AaGpuAdler32Init");
    return EAaGpuChecksumsRet_Ok; 
}
void* CcsStubImplDefault::AaMemAlloc(i32 const poolId, u32 const size )
{
    dbg_prints::instance()->addPrint("CcsStubImplDefault::AaMemAlloc");
    return 0; 
}
void* CcsStubImplDefault::AaMemAllocId( i32 const poolId, u32 const size, u32 const blockId )
{
    dbg_prints::instance()->addPrint("CcsStubImplDefault::AaMemAllocId");
    return 0; 
}
u32 CcsStubImplDefault::AaMemSizeGet( void const * const ptr )
{
    dbg_prints::instance()->addPrint("CcsStubImplDefault::AaMemSizeGet");
    return 0; 
}
void* CcsStubImplDefault::AaMemAllocSafe( i32 const poolId, u32 const size )
{
    dbg_prints::instance()->addPrint("CcsStubImplDefault::AaMemAllocSafe");
    return 0; 
}
void* CcsStubImplDefault::AaMemAllocSafeId(i32 const poolId, u32 const size, u32 const blockId )
{
    dbg_prints::instance()->addPrint("CcsStubImplDefault::AaMemAllocSafeId");
    return 0; 
}
EAaMemRet CcsStubImplDefault::AaMemBlockAddr2Obj(const void* const ptr, SAaMemBlockObj* blockObj)
{
    dbg_prints::instance()->addPrint("CcsStubImplDefault::AaMemBlockAddr2Obj");
    return EAaMemRet_Ok;
}
void* CcsStubImplDefault::AaMemBlockBaseGet( const void *ptr )
{
    dbg_prints::instance()->addPrint("CcsStubImplDefault::AaMemBlockBaseGet");
    return 0;
}
EAaMemRet CcsStubImplDefault::AaMemBlockObj2Addr(const SAaMemBlockObj* const blockObj, void** ptr)
{
    dbg_prints::instance()->addPrint("CcsStubImplDefault::AaMemBlockObj2Addr");
    return EAaMemRet_Ok;
}
void* CcsStubImplDefault::AaMemBlockPayloadGet( const void *ptr )
{
    dbg_prints::instance()->addPrint("CcsStubImplDefault::AaMemBlockPayloadGet");
    return 0;
}
EAaMemRet CcsStubImplDefault::AaMemCeInit( void )
{
    dbg_prints::instance()->addPrint("CcsStubImplDefault::AaMemCeInit");
    return EAaMemRet_Ok;
}
EAaMemRet CcsStubImplDefault::AaMemCeUninit( void )
{
    dbg_prints::instance()->addPrint("CcsStubImplDefault::AaMemCeUninit");
    return EAaMemRet_Ok;
}
EAaMemRet CcsStubImplDefault::AaMemEeInit(void)
{
    dbg_prints::instance()->addPrint("CcsStubImplDefault::AaMemEeInit");
    return EAaMemRet_Ok;
}
EAaMemRet CcsStubImplDefault::AaMemEeUninit(void)
{
    dbg_prints::instance()->addPrint("CcsStubImplDefault::AaMemEeUninit");
    return EAaMemRet_Ok;
}
void* CcsStubImplDefault::AaMemMalloc( u32 const size )
{
    dbg_prints::instance()->addPrint("CcsStubImplDefault::AaMemMalloc");
    return 0;
}
SAaMemBlockObjClass* CcsStubImplDefault::AaMemObjectClassGet( void const *ptr )
{
    dbg_prints::instance()->addPrint("CcsStubImplDefault::AaMemObjectClassGet");
    return 0;
}
EAaMemRet CcsStubImplDefault::AaMemPoolAttach( i32* poolId, const char* poolName, const SAaMemPoolHandler* poolHndlr )
{
    dbg_prints::instance()->addPrint("CcsStubImplDefault::AaMemPoolAttach");
    return EAaMemRet_Ok;
}
EAaMemRet CcsStubImplDefault::AaMemPoolDetach( i32 const poolId )
{
    dbg_prints::instance()->addPrint("CcsStubImplDefault::AaMemPoolDetach");
    return EAaMemRet_Ok;
}
void CcsStubImplDefault::AaMemObjectClassSet( void const * const ptr, SAaMemBlockObjClass const * const objClass )
{
    dbg_prints::instance()->addPrint("CcsStubImplDefault::AaMemObjectClassSet");    
}
EAaMemRet CcsStubImplDefault::AaMemPoolInfoGet(i32 const poolId, SAaMemPoolInfo * poolInfo)
{
    dbg_prints::instance()->addPrint("CcsStubImplDefault::AaMemPoolInfoGet");
    return EAaMemRet_Ok; 
}
void* CcsStubImplDefault::AaMemPoolOpaqueGet( const void * const basePtr )
{
    dbg_prints::instance()->addPrint("CcsStubImplDefault::AaMemPoolOpaqueGet");
    return 0; 
}
void* CcsStubImplDefault::AaMemRef( void* const ptr )
{
    dbg_prints::instance()->addPrint("CcsStubImplDefault::AaMemRef");
    return 0; 
}
EAaFileRet CcsStubImplDefault::AaFileGzCompress(const char* srcFileName, const char* destFileName)
{
    dbg_prints::instance()->addPrint("CcsStubImplDefault::AaFileGzCompress");
    return EAaFileRet_Ok; 
}
EAaFileRet CcsStubImplDefault::AaFileCeShutdown(void)
{
    dbg_prints::instance()->addPrint("CcsStubImplDefault::AaFileCeShutdown");
    return EAaFileRet_Ok; 
}
EAaFileRet CcsStubImplDefault::AaFileCeStartup(void)
{
    dbg_prints::instance()->addPrint("CcsStubImplDefault::AaFileCeStartup");
    return EAaFileRet_Ok; 
}
EAaFileRet CcsStubImplDefault::AaFileCopyDir(const char* srcPath, const char* destPath)
{
    dbg_prints::instance()->addPrint("CcsStubImplDefault::AaFileCopyDir");
    return EAaFileRet_Ok; 
}
EAaFileRet CcsStubImplDefault::AaFileGzDecompress(const char* srcFileName, const char* destFileName)
{
    dbg_prints::instance()->addPrint("CcsStubImplDefault::AaFileGzDecompress");
    return EAaFileRet_Ok; 
}
EAaFileRet CcsStubImplDefault::AaFileEeShutdown(void)
{
    dbg_prints::instance()->addPrint("CcsStubImplDefault::AaFileEeShutdown");
    return EAaFileRet_Ok; 
}
EAaFileRet CcsStubImplDefault::AaFileEeStartup(void)
{
    dbg_prints::instance()->addPrint("CcsStubImplDefault::AaFileEeStartup");
    return EAaFileRet_Ok; 
}
EAaFileRet CcsStubImplDefault::AaFileFlush(TAaFile *stream)
{
    dbg_prints::instance()->addPrint("CcsStubImplDefault::AaFileFlush");
    return EAaFileRet_Ok; 
}
EAaFileRet CcsStubImplDefault::AaFileForceUnlock(const char *filename)
{
    dbg_prints::instance()->addPrint("CcsStubImplDefault::AaFileForceUnlock");
    return EAaFileRet_Ok; 
}
TAaFile* CcsStubImplDefault::AaFileOpenWithLock(const char *fileName, const char *mode, TBoolean* locked)
{
    dbg_prints::instance()->addPrint("CcsStubImplDefault::AaFileOpenWithLock");
    return 0; 
}
EAaFileRet CcsStubImplDefault::AaFileRemoveDir(const char* path)
{
    dbg_prints::instance()->addPrint("CcsStubImplDefault::AaFileRemoveDir");
    return EAaFileRet_Ok; 
}
int CcsStubImplDefault::AaFileSicFtpInit(void)
{
    dbg_prints::instance()->addPrint("CcsStubImplDefault::AaFileSicFtpInit");
    return 0; 
}
EAaFileSicFtpRet CcsStubImplDefault::AaFileSicFtpPut( TAaSysComNid remoteNode, const char* srcFilePath, const char* destFilePath)
{
    dbg_prints::instance()->addPrint("CcsStubImplDefault::AaFileSicFtpPut");
    return EAaFileSicFtpRet_Ok; 
}
EAaFileTftpErrorCode CcsStubImplDefault::AaFileTftpGetExt(const char *ipAddress,  const char *srcFilename, const char *dstFilename, u32 timeout, u32 retries)
{
    dbg_prints::instance()->addPrint("CcsStubImplDefault::AaFileTftpGetExt");
    return EAaFileTftpErrorCode_NoError; 
}
int CcsStubImplDefault::AaFileTftpInit(void)
{
    dbg_prints::instance()->addPrint("CcsStubImplDefault::AaFileTftpInit");
    return 0; 
}
EAaFileTftpErrorCode CcsStubImplDefault::AaFileTftpPut(const char *ipAddress, const char *srcFilename, const char *dstFilename)
{
    dbg_prints::instance()->addPrint("CcsStubImplDefault::AaFileTftpPut");
    return EAaFileTftpErrorCode_NoError; 
}
EAaFileTftpErrorCode CcsStubImplDefault::AaFileTftpPutExt(const char *ipAddress,  const char *srcFilename, const char *dstFilename, u32 timeout, u32 retries)
{
    dbg_prints::instance()->addPrint("CcsStubImplDefault::AaFileTftpPutExt");
    return EAaFileTftpErrorCode_NoError; 
}
EAaFileRet CcsStubImplDefault::AaFileSeek(TAaFile *stream, long offset, int whence)
{
    dbg_prints::instance()->addPrint("CcsStubImplDefault::AaFileSeek");
    return EAaFileRet_Ok;
}
long CcsStubImplDefault::AaFileTell(TAaFile *stream)
{
    dbg_prints::instance()->addPrint("CcsStubImplDefault::AaFileTell");
    return 0;
}
char * CcsStubImplDefault::AaFileGetAbsPath(const char* path)
{
    dbg_prints::instance()->addPrint("CcsStubImplDefault::AaFileGetAbsPath"); 
    return 0; 
}

EAaFileRet CcsStubImplDefault::AaFileRename(const char* oldPath, const char* newPath)
{
    dbg_prints::instance()->addPrint("CcsStubImplDefault::AaFileRename"); 
    return EAaFileRet_Error; 
}

void CcsStubImplDefault::AaMemUnRef( void const ** const ptr )
{
    dbg_prints::instance()->addPrint("CcsStubImplDefault::AaMemUnRef");
}
EAaFileSicFtpRet CcsStubImplDefault::AaFileSicFtpList(TAaSysComNid remoteNode, const char* path, TAaFileListing *fileList)
{
    dbg_prints::instance()->addPrint("CcsStubImplDefault::AaFileSicFtpList"); 
    return EAaFileSicFtpRet_Ok; 
}

EAaFileSicFtpRet CcsStubImplDefault::AaFileSicFtpRemoveDir(TAaSysComNid remoteNode, const char* dirPath)
{
    dbg_prints::instance()->addPrint("CcsStubImplDefault::AaFileSicFtpRemoveDir"); 
    return EAaFileSicFtpRet_Ok; 
}

EAaFileSicFtpRet CcsStubImplDefault::AaFileSicFtpRemove(TAaSysComNid remoteNode, const char* destFilePath)
{
    dbg_prints::instance()->addPrint("CcsStubImplDefault::AaFileSicFtpRemove"); 
    return EAaFileSicFtpRet_Ok; 
}

EAaFileSicFtpRet CcsStubImplDefault::AaFileSicFtpGet(TAaSysComNid remoteNode, const char* srcFilePath, const char* destFilePath)
{
    dbg_prints::instance()->addPrint("CcsStubImplDefault::AaFileSicFtpGet"); 
    return EAaFileSicFtpRet_Ok; 
}

TBoolean CcsStubImplDefault::AaFileSign(const char* filePath, const char* signaturePath, const char* digestTypeStr)
{
    dbg_prints::instance()->addPrint("CcsStubImplDefault::AaFileSign"); 
    return true; 
}
EAaFileRet CcsStubImplDefault::AaFileCreateDir(const char *path)
{
    return EAaFileRet_Ok;
}

EAaConfigRet CcsStubImplDefault::AaConfigSubscribeService(const char* const namePtr, const u32 major_version, const u32 minor_version, EAaConfigSvcRegScope scope, TAaSysComSicad sicad)
{
    return EAaConfigRet_Ok;
}

EAaConfigRet CcsStubImplDefault::AaConfigUnSubscribeService(const char* const namePtr, const u32 major_version, const u32 minor_version, TAaSysComSicad sicad)
{
    return EAaConfigRet_Ok;
}

TAaSysTime64 CcsStubImplDefault::AaTicks64Get()
{
    dbg_prints::instance()->addPrint("CcsStubImplDefault::AaTicks64Get"); 
    return 0;
}

TAaSysTime64 CcsStubImplDefault::AaSysTime64SinceGet(TAaSysTime64* timeref, const EAaSysTimeScale scale)
{
    dbg_prints::instance()->addPrint("CcsStubImplDefault::AaSysTime64SinceGet"); 
    return 0;
}

u32 CcsStubImplDefault::AaFileGzWrite(void* inbuf, u32 inlen, TAaGzFile* gzstream)
{
    dbg_prints::instance()->addPrint("CcsStubImplDefault::AaFileGzWrite"); 
    return 0;
}

TAaGzFile* CcsStubImplDefault::AaFileGzOpen(const char* fileName, const char *mode)
{
    dbg_prints::instance()->addPrint("CcsStubImplDefault::AaFileGzOpen"); 
    return 0;
}

EAaFileRet CcsStubImplDefault::AaFileGzClose(TAaGzFile* gzstream)
{
    dbg_prints::instance()->addPrint("CcsStubImplDefault::AaFileGzClose"); 
    return EAaFileRet_Ok;
}

void CcsStubImplDefault::AaSysComEnd32Swap(const void* firstField, const u32 numberOfFields)
{
    dbg_prints::instance()->addPrint("CcsStubImplDefault::AaSysComEnd32Swap");
}

TAaSysComNid CcsStubImplDefault::AaSysComSicadGetNid(TAaSysComSicad sicAddress)
{
    dbg_prints::instance()->addPrint("CcsStubImplDefault::AaSysComSicadGetNid");
    return 0;
}

EAaTrblRet CcsStubImplDefault::AaTrblFileRegister(char const* const logicalFileName, char const* const physicalFileName, EAaTrblFilePriority priority,
	TBoolean compressed, TAaTrblPrepareFileCb* const prepareCb, TAaTrblStoreFileCb* const storeCb, TAaTrblDeleteFileCb* const deleteCb, const void* opaque)
{
    dbg_prints::instance()->addPrint("CcsStubImplDefault::AaTrblFileRegister");
    return EAaTrblRet_Ok;    
}

EAaConfigRet CcsStubImplDefault::AaConfigTagSetU32(const char* name, u32 value)
{
    dbg_print(MON_SEVERITY_INFO, FEAT_DBG_Generic, "CcsStubImplDefault::AaConfigTagSetU32");
    return EAaConfigRet_Ok;
}

TBoolean CcsStubImplDefault::AaFileIsSecureEnvironment()
{
    return GLO_TRUE;
}
