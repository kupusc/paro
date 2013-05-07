

#include "ccs_stub.h"
#include "ccs_default_impl.h"
#ifdef _WIN32
#include "windows.h" //just for Aa...Atomic operations
#endif
#include <cassert>
#include <boost/thread.hpp>

//directly copied from AaCpu_asm_x86.h
/* For aligment check */
#ifdef AACPU_ALIGMENT_CHECK_ENABLED
# include <inttypes.h>
# include <assert.h>
# ifndef AACPU_ADDRESS_ALIGMENT
#  define AACPU_ADDRESS_ALIGMENT 0x3
# endif
# ifndef AACPU_ASSERT
#  define AACPU_ASSERT assert
# endif
# define AACPU_DO_PTR_ALIGMENT_CHECK(__ptr) AACPU_ASSERT((((uintptr_t)(__ptr)) & AACPU_ADDRESS_ALIGMENT) == 0) 
#else
# define AACPU_DO_PTR_ALIGMENT_CHECK(__ptr)
#endif

ICcsStubImpl * CcsStub::current;
ICcsStubImpl * CcsStub::default_impl;

//TAaSem * database_busy_semaphore;
TAaSem *semRhapsStarted;

CcsStub::CcsStub()
{
}
CcsStub::~CcsStub()
{
}
ICcsStubImpl * CcsStub::get()
{
    if (  current == 0 )
    {
        setDefault();
    }
    return current;
}
void CcsStub::set(ICcsStubImpl *s)
{
    current = s;
}
void CcsStub::setDefault()
{
    static CcsStubImplDefault defaultStub;
    default_impl=&defaultStub;

    current= default_impl;
}


extern "C"
{

    void AaGpuDurFree(TAaGpuDurHandle *handle)
    {
        CcsStub::get()->AaGpuDurFree(handle);
    }

    TAaSysComSicad AaSysComNmapGetSicad(const TBoard board, const TCpu cpu, const TTask task)
    {
        return CcsStub::get()->AaSysComNmapGetSicad( board,cpu,task);
    }

    void AaSysComMsgSend(void **message)
    {
        CcsStub::get()->AaSysComMsgSend(message);
    }

    void *AaSysComMsgGetPayload(const void *message)
    {
        return CcsStub::get()->AaSysComMsgGetPayload(message);
    }
    void *AaSysComMsgCreate(const TAaSysComMsgId messageId,
        const TAaSysComMsgSize messagePayloadSize,
        const TAaSysComSicad messageTarget)
    {
        return CcsStub::get()->AaSysComMsgCreate(messageId,messagePayloadSize,messageTarget);
    }
    TAaSysComCpid AaSysComUserRegister(const TAaSysComCpid userCpid,
        const u32 euId)
    {
        return CcsStub::get()->AaSysComUserRegister(userCpid,euId);
    }

    EAaProEuRetVal
        aProEuCreateAndStart( u32*                 euIdPtr,
        const char          *euNamePtr,
        TAaProEuEntryPoint  *euEntryPoint,
        u32                  euStackSize,
        u32                  euPriority,
        void*                euArgPtr,
        u32                  sizeOfeuArg )
    {
        assert(false);
        return EAaProEuRetVal_Error;
    }

    EAaProEuRetVal 
        AaProEuCreateAndStart( u32*                 euIdPtr,
        const char          *euNamePtr,
        TAaProEuEntryPoint  *euEntryPoint,
        u32                  euStackSize,
        u32                  euPriority,
        void*                euArgPtr,
        u32                  sizeOfeuArg )
    {
        return CcsStub::get()->AaProEuCreateAndStart( euIdPtr,euNamePtr,euEntryPoint,euStackSize,euPriority,euArgPtr,sizeOfeuArg );
    }
    TAaSysComMsgId AaSysComMsgGetId(const void *message)
    {
        return CcsStub::get()->AaSysComMsgGetId(message);
    }
    TTask AaSysComNmapGetTask(const TAaSysComSicad sicAddress)
    {
        return CcsStub::get()->AaSysComNmapGetTask(sicAddress);
    }
    TAaSysComSicad AaSysComMsgGetReceiver(const void *message)
    {
        return CcsStub::get()->AaSysComMsgGetReceiver(message);
    }
    TAaSysComCpid AaSysComUserDeregister(const TAaSysComCpid userCpid)
    {
        return CcsStub::get()->AaSysComUserDeregister(userCpid);
    }
    EAaSysMbRetVal AaSysMbPublish(void **payload)
    {
        return CcsStub::get()->AaSysMbPublish(payload);
    }

    void AaSysComMsgSendViaLink(void **message,
        const EAaSysComSendPriority priority,
        const TAaSysComLinkId requestedLink)
    {
        assert(false);
    }
    void AaSysComMsgDestroy(void **message)
    {
        assert(false);
    }
    TAaSysComSicad AaSysComMsgGetSender(const void *message)
    {
        return CcsStub::get()->AaSysComMsgGetSender(message);
    }
    TBoard AaSysComNmapGetBoard(const TAaSysComSicad sicAddress)
    {
        return CcsStub::get()->AaSysComNmapGetBoard(sicAddress);
    }
    TCpu AaSysComNmapGetCpu(const TAaSysComSicad sicAddress)
    {
        return CcsStub::get()->AaSysComNmapGetCpu(sicAddress);
    }
    void *AaSysComMsgReceive(const u32 maxTimeToWait)
    {
        return CcsStub::get()->AaSysComMsgReceive(maxTimeToWait);
    }
    EAaSysMbRetVal AaSysMbSubscribe(const TAaSysComMsgId messageId,
        const TAaSysComSicad subscriber,
        const EAaSysMbSubsMode mode,
        const TAaSysMbZoneId zone)
    {
        return CcsStub::get()->AaSysMbSubscribe(messageId,subscriber,mode,zone);
    }
    EAaSysMbRetVal AaSysMbUnsubscribe(const TAaSysComMsgId messageId,
        const TAaSysComSicad subscriber,
        const TAaSysMbZoneId zone)
    {
        assert(false);
        return EAaSysMbRetVal_Ok;
    }
    void *AaSysMbPrepare(const TAaSysComMsgSize messagePayloadSize,
        const TAaSysComMsgId messageId,
        const TAaSysComSicad publisher,
        const EAaSysMbPublMode mode,
        const TAaSysMbZoneId zone)
    {
        return CcsStub::get()->AaSysMbPrepare(messagePayloadSize,messageId,publisher,mode,zone);
    }
    void *AaSysComMsgCreateX(const TAaSysComMsgId messageId,
        const TAaSysComMsgSize messagePayloadSize,
        const TAaSysComSicad messageTarget,
        const EAaSysComMtm requestedTransferMode,
        const TAaSysComLinkId requestedLink)
    {
        assert(false);
        return 0;
    }
    void AaSysComMsgSetMtm(const void *message, 
        const EAaSysComMtm requestedTransferMode)
    {
        CcsStub::get()->AaSysComMsgSetMtm(message,requestedTransferMode);
        return;
    }

    TAaSysComMsgSize AaSysComMsgGetPayloadSize(const void *message)
    {
        return CcsStub::get()->AaSysComMsgGetPayloadSize(message);
    }
    u32 AaProEuCurrent(void)
    {
        return CcsStub::get()->AaProEuCurrent();
    }
    TAaSysComSicad AaSysComSicadGet(const TAaSysComCpid userCpid, 
        const TAaSysComNid userNid)
    {
        return CcsStub::get()->AaSysComSicadGet(userCpid,userNid);
    }
    TAaSysComNid AaSysComGetOwnNid(void)
    {
        return CcsStub::get()->AaSysComGetOwnNid();
    }
    void AaSysComMsgSetSender(const void *message,const TAaSysComSicad messageSource)
    {
        CcsStub::get()->AaSysComMsgSetSender(message, messageSource);
    }
    u32 AaConfigRadGetValue(u32 tag)
    {
        return CcsStub::get()->AaConfigRadGetValue(tag);
    }
    const char* AaConfigRadGetTagString(u32 tag)
    {
        return CcsStub::get()->AaConfigRadGetTagString(tag);
    }

    EAaConfigRet AaConfigRadRegisterDomain(u32 domain,
        const char* nameStringPtr,
        void (*initializeParameters)(void))
    {
        return CcsStub::get()->AaConfigRadRegisterDomain(domain,nameStringPtr,initializeParameters);
    }
    EAaConfigRet AaConfigRadSetValue(u32 tag, u32 value)
    {
        return CcsStub::get()->AaConfigRadSetValue(tag,value);
    }
    EAaConfigRet AaConfigRadSetDefault(u32         tag,
        const char* stringPtr,
        u32         initialValue)
    {
        return CcsStub::get()->AaConfigRadSetDefault(tag,stringPtr,initialValue);
    }
    EAaConfigRet AaConfigRadSetMaxTagCount(u32 domain, u32 count)
    {
        return CcsStub::get()->AaConfigRadSetMaxTagCount(domain,count);
    }
    EAaSysTimeRetVal AaUnixTimeGet(SAaBtsTimeval * const timePtr)
    {
        return CcsStub::get()->AaUnixTimeGet(timePtr);
    }
    EAaFileRet AaFileClose(TAaFile *stream)
    {
        return CcsStub::get()->AaFileClose(stream);
    }
    EAaFileRet AaFileRemove(const char *fileName)
    {
        return CcsStub::get()->AaFileRemove(fileName);
    }
    void AaSysLogPrint(const EAaSysLogSeverityLevel severityLevel,
        const char*     unformattedStringPtr,
        ... )
    {
        va_list argptr;
        va_start(argptr,unformattedStringPtr);
        CcsStub::get()->va_AaSysLogPrint(severityLevel,unformattedStringPtr,argptr);
        va_end(argptr);
    }

    void AaSysLogPrintE(const EAaSysLogSeverityLevel severityLevel,
        const u32                    feature, 
        const char*                  unformattedStringPtr,
        ...)
    {
        va_list argptr;
        va_start(argptr,unformattedStringPtr);
        //CcsStub::get()->va_AaSysLogPrintE(severityLevel,feature,unformattedStringPtr,argptr);
        va_end(argptr);
    }					

    void AaSysLogVPrintE(const EAaSysLogSeverityLevel severityLevel,
        const u32                    featureId, 
        const char*                  unformattedStringPtr,
        va_list                      args)
    {
        CcsStub::get()->AaSysLogVPrintE(severityLevel,featureId,unformattedStringPtr,args);
    }					 
    TAaFile *AaFileOpen(const char *fileName, const char *mode)
    {
        return CcsStub::get()->AaFileOpen(fileName,mode);
    }
    size_t AaFileWrite(void *ptr, size_t size, size_t nitems, TAaFile *stream)
    {
        return CcsStub::get()->AaFileWrite(ptr, size, nitems, stream);
    }
    size_t AaFileRead(void *ptr, size_t size, size_t nitems, TAaFile *stream)
    {
        return CcsStub::get()->AaFileRead(ptr, size, nitems, stream);
    }
    TAaSysComSicad AaSysComNmapGetSicAddress(const TBoard board, 
        const TCpu cpu, 
        const TTask task)
    {
        return CcsStub::get()->AaSysComNmapGetSicAddress(board,cpu,task);
    }
    TAaSysTime64 AaSysTimeBcnGet(void)
    {
        return CcsStub::get()->AaSysTimeBcnGet();
    }
    EAaFileTftpErrorCode AaFileTftpGet(const char *ipAddress,
        const char *srcFilename,
        const char *dstFilename)
    {
        return CcsStub::get()->AaFileTftpGet(ipAddress,srcFilename,dstFilename);
    }
    EAaConfigRet AaConfigTagSetString(const char* const name, 
        const char* const value)
    {
        return CcsStub::get()->AaConfigTagSetString(name,value);
    }
    EAaProEuRetVal AaProEuSetPri( u32 euId, u32 euPriority )
    {
        return CcsStub::get()->AaProEuSetPri(euId,euPriority);
    }
    u32 AaProEuGetPri(u32 euId)
    {
        return CcsStub::get()->AaProEuGetPri(euId);
    }
    void AaSemPost(TAaSem* semPtr)
    {
        return CcsStub::get()->AaSemPost(semPtr);
    }
    void AaSemWait(TAaSem* semPtr)
    {
        return CcsStub::get()->AaSemWait(semPtr);
    }

    u32 GetLteDownlinkFrequency(const u32 earfcn)
    {
        return CcsStub::get()->GetLteDownlinkFrequency(earfcn);
    }
    u32 GetLteUplinkFrequency(const u32 earfcn)
    {
        return CcsStub::get()->GetLteUplinkFrequency(earfcn);
    }
    u32 GetWcdmaDownlinkFrequency(const u32 earfcn)
    {
        return CcsStub::get()->GetWcdmaDownlinkFrequency(earfcn);
    }
    u32 GetWcdmaUplinkFrequency(const u32 earfcn)
    {
        return CcsStub::get()->GetWcdmaUplinkFrequency(earfcn);
    }
    TAaSysTime AaTicksGet (void)
    {
        return 0;
    }
    TAaTickRes AaTickResolutionGet(void)
    {
        return 0;
    }



    TAaGpuDurHandle* AaGpuDurAlloc(char const * const name)
    {
        //	assert(0);
        return CcsStub::get()->AaGpuDurAlloc(name);
    }

    void AaGpuDurStart(TAaGpuDurHandle *handle)
    {
        CcsStub::get()->AaGpuDurStart(handle);
    }

    void AaGpuDurStop(TAaGpuDurHandle *handle)
    {
        CcsStub::get()->AaGpuDurStop(handle);
    }

    EAaFileRet AaFileRename(const char *oldPath, const char *newPath)
    {
        return CcsStub::get()->AaFileRename(oldPath, newPath); 
    }

    char* AaFileGetAbsPath(const char* path)    
    { 
        return CcsStub::get()->AaFileGetAbsPath(path); 
    }

    EAaFileRet AaFileSeek(TAaFile *stream, long offset, int whence)
    {
        return CcsStub::get()->AaFileSeek( stream, offset, whence);
    }

    long AaFileTell(TAaFile *stream)
    {
        return CcsStub::get()->AaFileTell(stream);
    }
    long AaFileGetSize(TAaFile *stream)
    {
        return CcsStub::get()->AaFileGetSize(stream);
    }

    void AaSemCreateNamedC( TAaSem** semPtr,  char const * const namePtr,  u32  initialValue )
    {

    }

    void AaFileFreeListDirArray(SAaFileDnode*** dirArray, u32 nfiles)
    {
        CcsStub::get()->AaFileFreeListDirArray(dirArray, nfiles);
    }

    EAaFileRet AaFileListDir(SAaFileDnode*** dirArray, u32* nfilesp, const char* path, TBoolean recursive)
    {
        return CcsStub::get()->AaFileListDir(dirArray, nfilesp, path, recursive);
    }

    EAaConfigRet AaConfigTagSet(const char* const name, const void* const value, const u32 length)
    {
        assert(0);
        return EAaConfigRet_Error;
    }

    TAaSysComNid AaSysComSicadGetNid(const TAaSysComSicad sicAddress)
    {
        return CcsStub::get()->AaSysComSicadGetNid(sicAddress);
    }

    EAaSysTimeRetVal AaSysTimeSleep(const TAaSysTime sleepTime, const EAaSysTimeScale scale)
    {
        return CcsStub::get()->AaSysTimeSleep(sleepTime,scale);
    }

    EAaConfigRet AaConfigTagPublicSet(const char* const name,  const void* const value,  const u32 length)
    {
        assert(0);
        return EAaConfigRet_Error;
    }

    EAaFileRet AaFileCopy(const char* srcPath, const char* destPath)
    {
        return CcsStub::get()->AaFileCopy(srcPath, destPath);
    }

    EAaConfigRet AaConfigTagSetU32(const char* const name,  const u32 value)
    {
        return CcsStub::get()->AaConfigTagSetU32(name, value);
    }

    void AaMemUnRef( void const ** const ptr )
    {
        CcsStub::get()->AaMemUnRef(ptr); 
    }

    EAaFileSicFtpRet AaFileSicFtpListRecursive( TAaSysComNid remoteNode, const char* path, TAaFileListing *fileList)
    {
        assert(0);
        return EAaFileSicFtpRet_UndefinedError;
    }

    EAaTrblRet AaTrblFileRegister(char const * const logicalFileName,
        char const * const physicalFileName,
        EAaTrblFilePriority priority,
        TBoolean compressed,                              
        TAaTrblPrepareFileCb * const prepareCb,
        TAaTrblStoreFileCb * const storeCb,
        TAaTrblDeleteFileCb * const deleteCb,
        const void * opaque)
    {
        return CcsStub::get()->AaTrblFileRegister(logicalFileName, physicalFileName, priority, compressed, prepareCb, storeCb, deleteCb, opaque);
    }							  

    EAaFileSicFtpRet AaFileSicFtpCopy( TAaSysComNid remoteNode, const char* srcFilePath, const char* destFilePath)
    {
        assert(0);
        return EAaFileSicFtpRet_UndefinedError;
    }

    EAaFileSicFtpRet AaFileSicFtpCopyDir( TAaSysComNid remoteNode, const char* srcDirPath, const char* destDirPath)
    {
        assert(0);
        return EAaFileSicFtpRet_UndefinedError;
    }

    EAaFileRet AaFileCreateDir(const char* path)
    {
        return CcsStub::get()->AaFileCreateDir( path );
    }

    EAaFileSicFtpRet AaFileSicFtpList( TAaSysComNid remoteNode, const char* path, TAaFileListing *fileList)
    {
        return CcsStub::get()->AaFileSicFtpList( remoteNode, path, fileList);
    }

    EAaFileSicFtpRet AaFileSicFtpRemoveDir( TAaSysComNid remoteNode, const char* dirPath)
    {
        return CcsStub::get()->AaFileSicFtpRemoveDir(remoteNode, dirPath);
    }

    EAaFileSicFtpRet AaFileSicFtpRemove( TAaSysComNid remoteNode, const char* destFilePath)
    {
        return CcsStub::get()->AaFileSicFtpRemove(remoteNode, destFilePath);
    }

    EAaFileSicFtpRet AaFileSicFtpGet( TAaSysComNid remoteNode, const char* srcFilePath, const char* destFilePath)
    {
        return CcsStub::get()->AaFileSicFtpGet(remoteNode, srcFilePath, destFilePath);
    }

    EAaSNTPRet AaSNTPStop()
    {
        assert(0);
        return EAaSNTPRet_TaskError;
    }

    EAaSNTPRet AaSNTPStart(u32 flags)
    {
        assert(0);
        return EAaSNTPRet_TaskError;
    }

    EAaSNTPRet AaSNTPConfigure(const char *ipAddress)
    {
        assert(0);
        return EAaSNTPRet_TaskError;
    }

    EAaSNTPConnectionStatus AaSNTPConnectionStatus()
    {
        assert(0);
        return EAaSNTPConnectionStatus_NeverConnected;
    }

    EAaSysTimeRetVal AaLocalTimeGet(SAaTime * const timePtr)
    {
       // assert(0);
        return EAaSysTimeRetVal_Error;
    }

    char* AaFileReadLine(char *buf, size_t size, TAaFile *stream)
    {
        assert(0);
        return 0;
    }

    void AaSysComMsgSendS(void **message, const TAaSysComSicad messageSender)
    {
        assert(0);
    }

    u32 AaSysComUserQueryEuid(const TAaSysComCpid userCpid)
    {
        assert(0);
        return 0;
    }

    TAaSysTime64 AaSysTimeBcnAtPpsGet(void)
    {
        assert(0);
        return 0;
    }

    EAaSysTimeRetVal AaSysTimeRtcSync(TBoolean ntpUsed,
        SAaTime *utcPtr,
        TAaSysTime64 utcValidAtBcn)
    {
        assert(0);
        return EAaSysTimeRetVal_Error;
    }

    char* AaProEuGetName(u32 euId, char* buffer, u32 length)
    {
        return CcsStub::get()->AaProEuGetName(euId,buffer,length);
    }
    TAaSysComCpid AaSysComSicadGetCpid(const TAaSysComSicad sicAddress)
    {
        return CcsStub::get()->AaSysComSicadGetCpid(sicAddress);
    }
    void AaSemCreateC( TAaSem** semPtr, u32      initialValue )
    {
        CcsStub::get()->AaSemCreateC(semPtr,initialValue);
    }
    void AaSemDestroy(TAaSem* semPtr)
    {
        CcsStub::get()->AaSemDestroy(semPtr);
    }
    void AaSemGetValue(TAaSem*  semPtr, i32*     semValuePtr)
    {
        CcsStub::get()->AaSemGetValue(semPtr,semValuePtr);
    }
    void *AaSysComMsgReceiveFromEu(const u32 euId)
    {
        return CcsStub::get()->AaSysComMsgReceiveFromEu(euId);
    }

    // --------------- IfAaCPU -----------------------------------------------

#ifdef _WIN32
    int AaCpuSpinLockTryLock(TAaCpuSpinLock* lock)
    {
        return AaCpuAtomicCmpSwap32((TAaCpuAtomic32*)&lock->value, AACPU_SPINLOCK_UNLOCKED, AACPU_SPINLOCK_LOCKED);
    } 
#elif __GNUC__
    int AaCpuSpinLockTryLock(TAaCpuSpinLock* lock)
    {
        volatile int oldValue = AACPU_SPINLOCK_LOCKED; /* We try to acquire the lock */

        AACPU_DO_PTR_ALIGMENT_CHECK(lock);

        __asm__ __volatile__(
            "lock xchg %0,%1" /* Use i386 Exchange data instruction to swap lock's value to oldValue atomically */
            : "=r" (oldValue), "+m" (lock->value) /* Use register for oldValue and direct memory address for lock->value output */
            : "r" (oldValue) /* Input is oldValue */ 
            : "memory"); /* Some updates to memory done by xchg so inform asm about it */

        /* If lock acquiring succeeded, old value should be unlocked (i.e. 1), otherwice
        someone is already owning the lock */
        return oldValue;

    } /* AaCpuSpinLockTryLock */
#endif

#ifdef _WIN32
    i32 AaCpuAtomicAdd32(TAaCpuAtomic32* atomic, const i32 data)
    {
        return InterlockedExchangeAdd((volatile LONG *)&atomic->data, data) + data;
        /* replace with this for nonatomic test
        return atomic->data += data;
        */
    }

#elif __GNUC__
    i32 AaCpuAtomicAdd32(TAaCpuAtomic32* atomic, const i32 value)
    {
        i32 i = value;

        AACPU_DO_PTR_ALIGMENT_CHECK(atomic);

        __asm__ __volatile__(
            "lock xaddl %0,%1" /* Use x86 exchange (x..) and add (..add..) to atomically add 32bit (..l) value */
            :"+r" (i), "+m" (atomic->data) /* out (i must be here too); + means R/W */
            : : "memory");                 /* scratch */

        return value + i;
    } /* AaCpuAtomicAdd32 */
#endif

#ifdef _WIN32
    i32 AaCpuAtomicCmpSwap32(TAaCpuAtomic32* atomic, i32 comp, i32 value)
    {
        //http://msdn.microsoft.com/en-us/library/windows/desktop/ms683560%28v=vs.85%29.aspx
        return InterlockedCompareExchange((volatile LONG *)&atomic->data, value, comp);
        /* replace with this for nonatomic test
        if((volatile LONG )atomic->data == comp) {
        atomic->data = value;
        return comp;
        } else
        return atomic->data;*/
    } 
#elif __GNUC__
    i32 AaCpuAtomicCmpSwap32(TAaCpuAtomic32* atomic, i32 comp, i32 value)
    {
        AACPU_DO_PTR_ALIGMENT_CHECK(atomic);

        __asm__ __volatile__(
            "lock cmpxchgl %0,%2" /* Swap value and atomic->data if comp equals to atomic->data */
            : "+r"(value), "+a"(comp) /* According to Intel's manual, comp value must be in EAX register i.e. "a" */
            : "m"(atomic->data)
            : "memory");

        return comp;
    } /* AaCpuAtomicCmpSwap32 */
#endif

#ifdef _WIN32
    i32 AaCpuAtomicSwap32(TAaCpuAtomic32* atomic, i32 value)
    {
        return InterlockedExchange((volatile LONG *)&atomic->data, value);
    }
#elif __GNUC__
    i32 AaCpuAtomicSwap32(TAaCpuAtomic32* atomic, i32 value)
    {
        AACPU_DO_PTR_ALIGMENT_CHECK(atomic);

        __asm__ __volatile__(
            "lock xchgl %0,%1" /* Use x86 exchange word to atomically swap 32bit values */
            :"=r" (value) 
            :"m" (atomic->data), "0" (value) /* "0" means that 'value' stays in the same register (more efficient register usage) */
            :"memory");

        return value;
    } /* AaCpuAtomicDec32 */
#endif

#if !defined(AACPU_ATOMIC_SET_32_OPTIMIZED)
    void AaCpuAtomicSet32 (TAaCpuAtomic32 * atomic, const i32 value)
    {
        atomic->data = value;
    }                               /* AaCpuAtomicSet32 */
#endif

#if !defined(AACPU_ATOMIC_READ_32_OPTIMIZED)
    i32 AaCpuAtomicRead32 (TAaCpuAtomic32 * atomic)
    {
        return atomic->data;
    }                               /* AaCpuAtomicRead32 */
#endif

    i32 AaCpuAtomicSub32 (TAaCpuAtomic32 * atomic, const i32 value)
    {
        return AaCpuAtomicAdd32 (atomic, -value);
    }                               /* AaCpuAtomicSub32 */

    i32 AaCpuAtomicInc32 (TAaCpuAtomic32 * atomic)
    {
        return AaCpuAtomicAdd32 (atomic, 1);
    }                               /* AaCpuAtomicInc32 */


    i32 AaCpuAtomicDec32 (TAaCpuAtomic32 * atomic)
    {
        return AaCpuAtomicSub32 (atomic, 1);
    }                               /* AaCpuAtomicDec32 */

    i32 AaCpuAtomicAddIf32 (TAaCpuAtomic32 * atomic, i32 comp, i32 value)
    {
        i32 old, curr = AaCpuAtomicRead32 (atomic);

        for (;;)
        {
            if ( (curr != comp))  /* Does not match */
            {
                return comp;
            }

            old = AaCpuAtomicCmpSwap32 (atomic, curr, curr + value);    /* Try to swap */

            if ( (old == curr)) /* Swap succeeded if AaCpuAtomicCmpSwap32 returns comp (curr) value */
            {
                return curr + value;
            }

            curr = old;             /* Try again with new current value since it was changed before CmpSwap */
        }                           /* for */

    }                               /* AaCpuAtomicAddIf32 */


    i32 AaCpuAtomicAddUnless32 (TAaCpuAtomic32 * atomic, i32 comp, i32 value)
    {
        i32 old, curr = AaCpuAtomicRead32 (atomic);

        for (;;)
        {
            if ( (curr == comp))  /* Already matches */
            {
                return comp;
            }

            old = AaCpuAtomicCmpSwap32 (atomic, curr, curr + value);    /* Try to swap */

            if ( (old == curr)) /* Swap succeeded if AaCpuAtomicCmpSwap32 returns comp (curr) value */
            {
                return curr;
            }

            curr = old;             /* Try again with new current value since it was changed before CmpSwap */
        }                           /* for */

    }                               /* AaCpuAtomicAddUnless32 */

    i32 AaCpuAtomicAddGreater32 (TAaCpuAtomic32 * atomic, i32 comp, i32 value)
    {
        i32 old, curr = AaCpuAtomicRead32 (atomic);

        for (;;)
        {
            if ( (!(comp < curr)))    /* NOT greater */
            {
                return comp;
            }

            old = AaCpuAtomicCmpSwap32 (atomic, curr, curr + value);    /* Try to swap */

            if ( (old == curr)) /* Swap succeeded if AaCpuAtomicCmpSwap32 returns comp (curr) value */
            {
                return curr;
            }

            curr = old;             /* Try again with new current value since it was changed before CmpSwap */
        }                           /* for */

    }                               /* AaCpuAtomicAddGreater32 */

    i32 AaCpuAtomicIncNotZero32 (TAaCpuAtomic32 * atomic)
    {
        return AaCpuAtomicAddUnless32 (atomic, 0, 1);
    }                               /* AaCpuAtomicIncNotZero32 */

    i32 AaCpuAtomicDecNotZero32 (TAaCpuAtomic32 * atomic)
    {
        return AaCpuAtomicAddUnless32 (atomic, 0, -1);
    }                               /* AaCpuAtomicDecNotZero32 */


    i32 AaCpuAtomicDecGreater32 (TAaCpuAtomic32 * atomic, i32 comp, i32 value)
    {
        return AaCpuAtomicAddGreater32 (atomic, comp, -value);
    }                               /* AaCpuAtomicDecGreater32 */

    void AaCpuSpinLockInit (TAaCpuSpinLock * lock) {
        lock->value = AACPU_SPINLOCK_INIT;
        lock->spinThold = AACPU_SPINLOCK_MAX_SPINS;
        lock->yieldThold = AACPU_SPINLOCK_MAX_YIELDS;
    }

    void AaCpuSpinLockLock (TAaCpuSpinLock * lock) {
        i32 localSpins = 0, localYield = 0;
        const i32 localSpinThold = lock->spinThold;

        /* Try to lock */
        while (!AaCpuSpinLockTryLock (lock))
        {
            /* If spin threshold is exceeded, time to yield */
            if (localSpins > localSpinThold)
            {
                AaCpuYield ();
                ++localYield;
            }

            ++localSpins;
        }                           /* while */
    }

    void AaCpuSpinLockUnlock (TAaCpuSpinLock * lock) {
        lock->value = AACPU_SPINLOCK_UNLOCKED;  /* We shall release the lock (no owner checks are done) */
    }

    void AaCpuYield (void)
    {
        boost::this_thread::yield();
    }

    void AaSemRwLockCreate(TAaSemRwLock** const lock)
    {
        CcsStub::get()->AaSemRwLockCreate(lock);
    }

    void AaSemRwLockDestroy(TAaSemRwLock** const lock)
    {
        CcsStub::get()->AaSemRwLockDestroy(lock);
    }
    //referenced by SWBUS, but SWBUS is not used, only for linking process

    void AaErrorAssertion(const char* const expression, const char* const file, const u32 line)
    {
        CcsStub::get()->AaErrorAssertion(expression, file, line);
    }
    void AaSysComMsgSetId(const void *message, const TAaSysComMsgId messageId)
    {
         CcsStub::get()->AaSysComMsgSetId(message, messageId);
    }
    
    void AaSysComMsgSetReceiver(void **message, const TAaSysComSicad receiver)
    {
         CcsStub::get()->AaSysComMsgSetReceiver(message, receiver); 
    }
    void* AaSysTimermDelete(const TAaSysTimerId timerId)
    {
        return CcsStub::get()->AaSysTimermDelete(timerId); 
    }
    
    EAaSysTimeRetVal AaSysTimermCreate(TAaSysTimerId* const timerIdPtr, const TAaMicroSecond latency,
        const TAaMicroSecond period, const void* const messagePtr)
    {
        return CcsStub::get()->AaSysTimermCreate(timerIdPtr, latency, period, messagePtr); 
    }
    
    void *AaSysComMsgReceiveSelective(const u32 maxTimeToWait, const TAaSysComMsgId *messageIdFilter)
    {
        return CcsStub::get()->AaSysComMsgReceiveSelective( maxTimeToWait, messageIdFilter); 
    }
    //end referenced by SWBUS, but SWBUS is not used, only for linking process
    
    void AaSemRwLockReadLock(TAaSemRwLock* const lock)
    {
        CcsStub::get()->AaSemRwLockReadLock(lock);
    }

    void AaSemRwLockReadUnlock(TAaSemRwLock* const lock)
    {
        CcsStub::get()->AaSemRwLockReadUnlock(lock);
    }

    void AaSemRwLockWriteLock(TAaSemRwLock* const lock)
    {
        CcsStub::get()->AaSemRwLockWriteLock(lock);
    }

    void AaSemRwLockWriteUnlock(TAaSemRwLock* const lock)
    {
        CcsStub::get()->AaSemRwLockWriteUnlock(lock);
    }

    EAaConfigRet AaConfigTagRegister(const char* const name, TAaConfigTagObserver* const callback)
    {
        return CcsStub::get()->AaConfigTagRegister(name, callback);
    }

    EAaConfigRet AaConfigTagUnregister(const char* const name, TAaConfigTagObserver* const callback)
    {
        return CcsStub::get()->AaConfigTagUnregister(name, callback);
    }

    EAaProEuRetVal AaProCmdExec(const char * command, const char * args, u32 flags, int * retVal)
    {
        return CcsStub::get()->AaProCmdExec(command, args, flags, retVal);
    }

    TAaSysComHopId AaSysComHopRegister(const TAaSysComSicad destinationAddress, const u32 metric, const TAaSysComLinkId linkId)
    {
        return CcsStub::get()->AaSysComHopRegister(destinationAddress, metric, linkId);
    }

    EAaGpuChecksumsRet AaGpuChecksumsUninit(SAaGpuChecksumHandler* const handler)
    {
        return CcsStub::get()->AaGpuChecksumsUninit(handler); 
    }
    
    EAaGpuChecksumsRet AaGpuChecksumsUpdate(SAaGpuChecksumHandler* const handler, const void* const data, const u32 length)
    {
        return CcsStub::get()->AaGpuChecksumsUpdate(handler, data, length); 
    }
    
    u32 AaGpuChecksumsValueGet(SAaGpuChecksumHandler* const handler)
    {
        return CcsStub::get()->AaGpuChecksumsValueGet(handler); 
    }
    
    EAaGpuChecksumsRet AaGpuAdler32Init(SAaGpuChecksumHandler* const handler)
    {
        return CcsStub::get()->AaGpuAdler32Init(handler); 
    }

    void* AaMemAlloc(i32 const poolId, u32 const size )
    {
        return CcsStub::get()->AaMemAlloc(poolId, size); 
    }

    void* AaMemAllocId( i32 const poolId, u32 const size, u32 const blockId )
    {
        return CcsStub::get()->AaMemAllocId(poolId, size, blockId ); 
    }

    u32 AaMemSizeGet( void const * const ptr )
    {
        return CcsStub::get()->AaMemSizeGet( ptr ); 
    }

    void* AaMemAllocSafe( i32 const poolId, u32 const size )
    {
        return CcsStub::get()->AaMemAllocSafe( poolId, size ); 
    }
     
    void* AaMemAllocSafeId(i32 const poolId, u32 const size, u32 const blockId )
    {
        return CcsStub::get()->AaMemAllocSafeId( poolId, size, blockId ); 
    }

    EAaMemRet AaMemBlockAddr2Obj(const void* const ptr, SAaMemBlockObj* blockObj)
    {
        return CcsStub::get()->AaMemBlockAddr2Obj( ptr, blockObj ); 
    }
     
    void* AaMemBlockBaseGet( const void *ptr )
    {
        return CcsStub::get()->AaMemBlockBaseGet( ptr ); 
    }     
    
    EAaMemRet AaMemBlockObj2Addr(const SAaMemBlockObj* const blockObj, void** ptr)
    {
        return CcsStub::get()->AaMemBlockObj2Addr( blockObj, ptr ); 
    }
    void* AaMemBlockPayloadGet( const void *ptr )
    {
        return CcsStub::get()->AaMemBlockPayloadGet( ptr ); 
    }
    
    EAaMemRet AaMemCeInit( void )
    {
        return CcsStub::get()->AaMemCeInit(); 
    }
    
    EAaMemRet AaMemCeUninit( void )
    {
        return CcsStub::get()->AaMemCeUninit(); 
    }
    
    EAaMemRet AaMemEeInit(void)
    {
       return CcsStub::get()->AaMemEeInit(); 
    }
    
    EAaMemRet AaMemEeUninit(void)
    {
        return CcsStub::get()->AaMemEeUninit(); 
    }
    
    void* AaMemMalloc( u32 const size )
    {
        return CcsStub::get()->AaMemMalloc(size); 
    }
    
    SAaMemBlockObjClass* AaMemObjectClassGet( void const *ptr )
    {
        return CcsStub::get()->AaMemObjectClassGet(ptr); 
    }
    
    EAaMemRet AaMemPoolAttach( i32* poolId, const char* poolName, const SAaMemPoolHandler* poolHndlr )
    {
        return CcsStub::get()->AaMemPoolAttach(poolId, poolName, poolHndlr); 
    }
    
    EAaMemRet AaMemPoolDetach( i32 const poolId )
    {
        return CcsStub::get()->AaMemPoolDetach(poolId); 
    }
    
    void AaMemObjectClassSet( void const * const ptr, SAaMemBlockObjClass const * const objClass )
    {
       CcsStub::get()->AaMemObjectClassSet(ptr, objClass);
    }
    
    EAaMemRet AaMemPoolInfoGet(i32 const poolId, SAaMemPoolInfo * poolInfo)
    {
        return CcsStub::get()->AaMemPoolInfoGet(poolId, poolInfo); 
    }
    
    void* AaMemPoolOpaqueGet( const void * const basePtr )
    {
       return CcsStub::get()->AaMemPoolOpaqueGet(basePtr); 
    }
    
    void* AaMemRef( void* const ptr )
    {
        return CcsStub::get()->AaMemRef(ptr); 
    }
    
    EAaFileRet AaFileGzCompress(const char* srcFileName, const char* destFileName)
    {
        return CcsStub::get()->AaFileGzCompress(srcFileName, destFileName); 
    }
    
    EAaFileRet AaFileCeShutdown(void)
    {
        return CcsStub::get()->AaFileCeShutdown(); 
    }
    
    EAaFileRet AaFileCeStartup(void)
    {
        return CcsStub::get()->AaFileCeStartup(); 
    }
    
    EAaFileRet AaFileCopyDir(const char* srcPath, const char* destPath)
    {
        return CcsStub::get()->AaFileCopyDir(srcPath, destPath); 
    }
    
    EAaFileRet AaFileGzDecompress(const char* srcFileName, const char* destFileName)
    {
        return CcsStub::get()->AaFileGzDecompress(srcFileName, destFileName); 
    }
    EAaFileRet AaFileEeShutdown(void)
    {
        return CcsStub::get()->AaFileEeShutdown();   
    }
    
    EAaFileRet AaFileEeStartup(void)
    {
        return CcsStub::get()->AaFileEeStartup();   
    }
    
    EAaFileRet AaFileFlush(TAaFile *stream)
    {
        return CcsStub::get()->AaFileFlush(stream); 
    }
    
    EAaFileRet AaFileForceUnlock(const char *filename)
    {
        return CcsStub::get()->AaFileForceUnlock(filename); 
    }
    
    TAaFile *AaFileOpenWithLock(const char *fileName, const char *mode, TBoolean* locked)
    {
        return CcsStub::get()->AaFileOpenWithLock(fileName, mode, locked); 
    }
    
    EAaFileRet AaFileRemoveDir(const char* path)
    {
        return CcsStub::get()->AaFileRemoveDir(path);   
    }
    
    int AaFileSicFtpInit(void)
    {
        return CcsStub::get()->AaFileSicFtpInit();   
    }
    
    EAaFileSicFtpRet AaFileSicFtpPut( TAaSysComNid remoteNode, const char* srcFilePath, const char* destFilePath)
    {
        return CcsStub::get()->AaFileSicFtpPut(remoteNode, srcFilePath, destFilePath);   
    }

    EAaFileTftpErrorCode AaFileTftpGetExt(const char *ipAddress,  const char *srcFilename, const char *dstFilename, u32 timeout, u32 retries)
    {
        return CcsStub::get()->AaFileTftpGetExt(ipAddress, srcFilename, dstFilename, timeout, retries);   
    }
    
    int AaFileTftpInit(void)
    {
        return CcsStub::get()->AaFileTftpInit();   
    }
    
    EAaFileTftpErrorCode AaFileTftpPut(const char *ipAddress, const char *srcFilename, const char *dstFilename)
    {
        return CcsStub::get()->AaFileTftpPut(ipAddress, srcFilename, dstFilename);  
    }
    
    EAaFileTftpErrorCode AaFileTftpPutExt(const char *ipAddress,  const char *srcFilename, const char *dstFilename, u32 timeout, u32 retries)
    {
        return CcsStub::get()->AaFileTftpPutExt(ipAddress, srcFilename, dstFilename, timeout, retries);  
    }
    
    TBoolean AaFileSign(const char* filePath, const char* signaturePath, const char* digestTypeStr)
    {
        return CcsStub::get()->AaFileSign(filePath, signaturePath, digestTypeStr);  
    }
	 
	TBoolean AaFileVerify(const char* filePath, const char* signaturePath)
	{
		return true;
	}	 

    EAaConfigRet AaConfigSubscribeService(const char* const namePtr, const u32 major_version, const u32 minor_version, EAaConfigSvcRegScope scope, TAaSysComSicad sicad)
    {
          return CcsStub::get()->AaConfigSubscribeService(namePtr, major_version, minor_version, scope, sicad);  
    }

    EAaConfigRet AaConfigUnSubscribeService(const char* const namePtr, const u32 major_version, const u32 minor_version, TAaSysComSicad sicad)
    {
          return CcsStub::get()->AaConfigUnSubscribeService(namePtr, major_version, minor_version, sicad);  
    }
    
    TAaSysTime64 AaTicks64Get()
    {
        return CcsStub::get()->AaTicks64Get();
    }

    TAaSysTime64 AaSysTime64SinceGet(TAaSysTime64* timeref, const EAaSysTimeScale scale)
    {
        return CcsStub::get()->AaSysTime64SinceGet(timeref, scale);
    }
    
    u32 AaFileGzWrite(void* inbuf, u32 inlen, TAaGzFile* gzstream)
    {
        return CcsStub::get()->AaFileGzWrite(inbuf,inlen,gzstream);
    }
    
    TAaGzFile* AaFileGzOpen(const char* fileName, const char* mode)
    {
        return CcsStub::get()->AaFileGzOpen(fileName,mode);
    }
    
    EAaFileRet AaFileGzClose(TAaGzFile* gzstream)
    {
        return CcsStub::get()->AaFileGzClose(gzstream);
    }

    void AaSysComEnd32Swap(const void* firstField, const u32 numberOfFields)
    {
        CcsStub::get()->AaSysComEnd32Swap(firstField,numberOfFields);
    }
    
    TBoolean AaFileIsSecureEnvironment() 
    {
        return CcsStub::get()->AaFileIsSecureEnvironment();
    }

}
