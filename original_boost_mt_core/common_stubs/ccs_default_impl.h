#ifndef __CCS_DEFAULT_IMPL_H__
#define __CCS_DEFAULT_IMPL_H__

#include "ccs_stub.h"
#include <IfAaGpuChecksums.h>
#include <IfAaMem.h>

class CcsStubImplDefault : public ICcsStubImpl
{
public:
    virtual void *AaSysComMsgCreate(const TAaSysComMsgId messageId,
                                    const TAaSysComMsgSize messagePayloadSize,
                                    const TAaSysComSicad messageTarget)  ;
    virtual EAaProEuRetVal
    AaProEuCreateAndStart( u32*                 euIdPtr,
                           const char          *euNamePtr,
                           TAaProEuEntryPoint  *euEntryPoint,
                           u32                  euStackSize,
                           u32                  euPriority,
                           void*                euArgPtr,
                           u32                  sizeOfeuArg ) ;
    TAaSysComCpid AaSysComUserRegister(const TAaSysComCpid userCpid, const u32 euId);
    TAaSysComSicad AaSysComNmapGetSicad(const TBoard board, const TCpu cpu, const TTask task);
    void AaGpuDurFree(TAaGpuDurHandle *handle);
    virtual void *AaSysMbPrepare(const TAaSysComMsgSize messagePayloadSize,
                                 const TAaSysComMsgId messageId,
                                 const TAaSysComSicad publisher,
                                 const EAaSysMbPublMode mode,
                                 const TAaSysMbZoneId zone);
    EAaSysMbRetVal AaSysMbSubscribe(const TAaSysComMsgId messageId,
                                    const TAaSysComSicad subscriber,
                                    const EAaSysMbSubsMode mode,
                                    const TAaSysMbZoneId zone);
    EAaSysMbRetVal AaSysMbPublish(void **payload);
    u32 AaProEuCurrent(void);
    void AaSysComMsgDestroy(void **message);
    TAaSysComNid AaSysComGetOwnNid(void);
    TAaSysComSicad AaSysComSicadGet(const TAaSysComCpid userCpid,const TAaSysComNid userNid);
    void *AaSysComMsgGetPayload(const void *message);
    TAaSysComMsgSize AaSysComMsgGetPayloadSize(const void *message);
    TAaSysComMsgId AaSysComMsgGetId(const void *message);
    TAaSysComSicad AaSysComMsgGetSender(const void *message);
    TBoard AaSysComNmapGetBoard(TAaSysComSicad sicAddress);
    TCpu AaSysComNmapGetCpu(TAaSysComSicad sicAddress);
    TAaSysComSicad AaSysComMsgGetReceiver(const void *message);
    void AaSysComMsgSend(void **message);
    TTask AaSysComNmapGetTask(TAaSysComSicad sicAddress);
    void AaSysComMsgSetSender(const void *message,const TAaSysComSicad messageSource);
    TAaSysComCpid AaSysComUserDeregister(const TAaSysComCpid userCpid);
    u32 AaConfigRadGetValue(u32 tag);
    const char* AaConfigRadGetTagString(u32 tag);
    EAaConfigRet AaConfigRadRegisterDomain(u32 domain,
                                           const char* nameStringPtr,
                                           void (*initializeParameters)(void));
    EAaConfigRet AaConfigRadSetValue(u32 tag, u32 value);
    EAaConfigRet AaConfigRadSetDefault(u32         tag,
                                       const char* stringPtr,
                                       u32         initialValue);
    EAaConfigRet AaConfigRadSetMaxTagCount(u32 domain, u32 count);
    EAaSysTimeRetVal AaUnixTimeGet(SAaBtsTimeval * const timePtr);
    EAaFileRet AaFileClose(TAaFile *stream);
    EAaFileRet AaFileRemove(const char *fileName);
    void va_AaSysLogPrint(const EAaSysLogSeverityLevel severityLevel,
                          const char* unformattedStringPtr, va_list argptr);
    void AaSysLogVPrintE(const EAaSysLogSeverityLevel severityLevel,
                         const u32                    featureId,
                         const char*                  unformattedStringPtr,
                         va_list                      args);
    TAaFile *AaFileOpen(const char *fileName, const char *mode);
    size_t AaFileWrite(void *ptr, size_t size, size_t nitems, TAaFile* stream);
    long AaFileGetSize(TAaFile *stream);
    size_t AaFileRead(void *ptr, size_t size, size_t nitems, TAaFile *stream);
    TAaSysComSicad AaSysComNmapGetSicAddress(const TBoard board,
            const TCpu cpu,
            const TTask task);
    TAaSysTime64 AaSysTimeBcnGet(void);
    EAaFileTftpErrorCode AaFileTftpGet(const char *ipAddress,
                                       const char *srcFilename,
                                       const char *dstFilename);
    EAaConfigRet AaConfigTagSetString(const char* const name,
                                      const char* const value);
    EAaProEuRetVal AaProEuSetPri( u32 euId, u32 euPriority );
    u32 AaProEuGetPri(u32 euId);
    void AaSemPost(TAaSem* semPtr);
    void AaSemWait(TAaSem* semPtr);
    u32 GetLteDownlinkFrequency(const u32 earfcn);
    u32 GetLteUplinkFrequency(const u32 earfcn);
    u32 GetWcdmaDownlinkFrequency(const u32 earfcn);
    u32 GetWcdmaUplinkFrequency(const u32 earfcn);
    void AaSysComMsgSetMtm(const void *message,const EAaSysComMtm requestedTransferMode);
    TAaGpuDurHandle* AaGpuDurAlloc(char const * const name) ;
    void AaGpuDurStart(TAaGpuDurHandle *handle) ;
    void AaGpuDurStop(TAaGpuDurHandle *handle) ;
    void AaFileFreeListDirArray(SAaFileDnode*** dirArray, u32 nfiles);
    EAaFileRet AaFileListDir(SAaFileDnode*** dirArray, u32* nfilesp, const char* path, TBoolean recursive);
    char* AaProEuGetName(u32 euId, char* buffer, u32 length);
    TAaSysComCpid AaSysComSicadGetCpid(const TAaSysComSicad sicAddress);
    void AaSemCreateC( TAaSem** semPtr, u32      initialValue );
    void AaSemDestroy(TAaSem* semPtr) ;
    void AaSemGetValue(TAaSem*  semPtr, i32*     semValuePtr) ;
    void *AaSysComMsgReceiveFromEu(const u32 euId) ;
    EAaSysTimeRetVal AaSysTimeSleep(const TAaSysTime sleepTime, const EAaSysTimeScale scale);
    EAaFileRet AaFileCopy(const char* srcPath, const char* destPath);
    void *AaSysComMsgReceive(const u32 maxTimeToWait) ;

    EAaProEuRetVal AaProCmdExec(const char * command, const char * args, u32 flags, int * retVal);
    TAaSysComHopId AaSysComHopRegister(const TAaSysComSicad destinationAddress, const u32 metric, const TAaSysComLinkId linkId);

    void AaSemRwLockCreate(TAaSemRwLock** const lock);
    void AaSemRwLockDestroy(TAaSemRwLock** const lock);
    void AaSemRwLockReadLock(TAaSemRwLock* const lock);
    void AaSemRwLockReadUnlock(TAaSemRwLock* const lock);
    void AaSemRwLockWriteLock(TAaSemRwLock* const lock);
    void AaSemRwLockWriteUnlock(TAaSemRwLock* const lock);

    EAaConfigRet AaConfigTagRegister(const char* const name,
                                     TAaConfigTagObserver* const callback);

    EAaConfigRet AaConfigTagUnregister(const char* const name,
                                       TAaConfigTagObserver* const callback);

    //referenced by SWBUS, but SWBUS is not used, only for linking process
    virtual void AaErrorAssertion(const char* const expression, const char* const file, const u32 line) {}
    virtual void AaSysComMsgSetId(const void *message, const TAaSysComMsgId messageId) {}
    virtual void AaSysComMsgSetReceiver(void **message, const TAaSysComSicad receiver) {}
    virtual void* AaSysTimermDelete(const TAaSysTimerId timerId)
    {
        return 0;
    }
    virtual EAaSysTimeRetVal AaSysTimermCreate(TAaSysTimerId* const timerIdPtr,	const TAaMicroSecond latency,
            const TAaMicroSecond period,const void* const messagePtr)
    {
        return EAaSysTimeRetVal_NoError;
    }
    virtual void *AaSysComMsgReceiveSelective(const u32 maxTimeToWait, const TAaSysComMsgId *messageIdFilter)
    {
        return 0;
    }
    virtual EAaGpuChecksumsRet AaGpuChecksumsUninit(SAaGpuChecksumHandler* const handler); 
    virtual EAaGpuChecksumsRet AaGpuChecksumsUpdate(SAaGpuChecksumHandler* const handler, const void* const data, const u32 length);
    virtual u32 AaGpuChecksumsValueGet(SAaGpuChecksumHandler* const handler); 
    virtual EAaGpuChecksumsRet AaGpuAdler32Init(SAaGpuChecksumHandler* const handler); 
    virtual void* AaMemAlloc(i32 const poolId, u32 const size ); 
    virtual void* AaMemAllocId( i32 const poolId, u32 const size, u32 const blockId ); 
    virtual u32 AaMemSizeGet( void const * const ptr ); 
    virtual void* AaMemAllocSafe( i32 const poolId, u32 const size ); 
    virtual void* AaMemAllocSafeId(i32 const poolId, u32 const size, u32 const blockId );
    virtual EAaMemRet AaMemBlockAddr2Obj(const void* const ptr, SAaMemBlockObj* blockObj);
    virtual void* AaMemBlockBaseGet( const void *ptr ); 
    virtual EAaMemRet AaMemBlockObj2Addr(const SAaMemBlockObj* const blockObj, void** ptr); 
    virtual void* AaMemBlockPayloadGet( const void *ptr ); 
    virtual EAaMemRet AaMemCeInit( void ); 
    virtual EAaMemRet AaMemCeUninit( void ); 
    virtual EAaMemRet AaMemEeInit(void); 
    virtual EAaMemRet AaMemEeUninit(void); 
    virtual void* AaMemMalloc( u32 const size ); 
    virtual SAaMemBlockObjClass* AaMemObjectClassGet( void const *ptr ); 
    virtual EAaMemRet AaMemPoolAttach( i32* poolId, const char* poolName, const SAaMemPoolHandler* poolHndlr ); 
    virtual EAaMemRet AaMemPoolDetach( i32 const poolId ); 
    virtual void AaMemObjectClassSet( void const * const ptr, SAaMemBlockObjClass const * const objClass ); 
    virtual EAaMemRet AaMemPoolInfoGet(i32 const poolId, SAaMemPoolInfo * poolInfo); 
    virtual void* AaMemPoolOpaqueGet( const void * const basePtr ); 
    virtual void* AaMemRef( void* const ptr ); 
    virtual EAaFileRet AaFileGzCompress(const char* srcFileName, const char* destFileName); 
    virtual EAaFileRet AaFileCeShutdown(void); 
    virtual EAaFileRet AaFileCeStartup(void); 
    virtual EAaFileRet AaFileCopyDir(const char* srcPath, const char* destPath); 
    virtual EAaFileRet AaFileGzDecompress(const char* srcFileName, const char* destFileName); 
    virtual EAaFileRet AaFileEeShutdown(void); 
    virtual EAaFileRet AaFileEeStartup(void); 
    virtual EAaFileRet AaFileFlush(TAaFile *stream); 
    virtual EAaFileRet AaFileForceUnlock(const char *filename); 
    virtual TAaFile *AaFileOpenWithLock(const char *fileName, const char *mode, TBoolean* locked);
    virtual EAaFileRet AaFileRemoveDir(const char* path); 
    virtual  int AaFileSicFtpInit(void); 
    virtual EAaFileSicFtpRet AaFileSicFtpPut( TAaSysComNid remoteNode, const char* srcFilePath, const char* destFilePath); 
    virtual EAaFileTftpErrorCode AaFileTftpGetExt(const char *ipAddress,  const char *srcFilename, const char *dstFilename, u32 timeout, u32 retries);
    virtual int AaFileTftpInit(void); 
    virtual EAaFileTftpErrorCode AaFileTftpPut(const char *ipAddress, const char *srcFilename, const char *dstFilename);
    virtual EAaFileTftpErrorCode AaFileTftpPutExt(const char *ipAddress,  const char *srcFilename, const char *dstFilename, u32 timeout, u32 retries);
	virtual EAaFileRet AaFileSeek(TAaFile *stream, long offset, int whence);
	virtual long AaFileTell(TAaFile *stream);
    virtual char* AaFileGetAbsPath(const char* path);  
    virtual EAaFileRet AaFileRename(const char *oldPath, const char *newPath);
    virtual void AaMemUnRef( void const ** const ptr ); 
    virtual EAaFileSicFtpRet AaFileSicFtpList( TAaSysComNid remoteNode, const char* path, TAaFileListing *fileList);
    virtual EAaFileSicFtpRet AaFileSicFtpRemoveDir( TAaSysComNid remoteNode, const char* dirPath);
    virtual EAaFileSicFtpRet AaFileSicFtpRemove( TAaSysComNid remoteNode, const char* destFilePath);
    virtual EAaFileSicFtpRet AaFileSicFtpGet( TAaSysComNid remoteNode, const char* srcFilePath, const char* destFilePath);
    virtual TBoolean AaFileSign(const char* filePath, const char* signaturePath, const char* digestTypeStr);  
	virtual EAaFileRet AaFileCreateDir(const char *path);
    virtual EAaConfigRet AaConfigSubscribeService(const char* const namePtr, const u32 major_version, const u32 minor_version, EAaConfigSvcRegScope scope, TAaSysComSicad sicad);
    virtual EAaConfigRet AaConfigUnSubscribeService(const char* const namePtr, const u32 major_version, const u32 minor_version, TAaSysComSicad sicad);
    virtual TAaSysTime64 AaTicks64Get();
    virtual TAaSysTime64 AaSysTime64SinceGet(TAaSysTime64* timeref, const EAaSysTimeScale scale);
    virtual u32 AaFileGzWrite(void *inbuf, u32 inlen, TAaGzFile* gzstream);
    virtual TAaGzFile* AaFileGzOpen(const char* fileName, const char *mode);
    virtual EAaFileRet AaFileGzClose(TAaGzFile* gzstream);
    virtual void AaSysComEnd32Swap(const void *firstField, const u32 numberOfFields);
    virtual TAaSysComNid AaSysComSicadGetNid(TAaSysComSicad sicAddress);
	EAaTrblRet AaTrblFileRegister(char const* const logicalFileName,
                              char const* const physicalFileName,
                              EAaTrblFilePriority priority,
                              TBoolean compressed,                              
                              TAaTrblPrepareFileCb* const prepareCb,
                              TAaTrblStoreFileCb* const storeCb,
                              TAaTrblDeleteFileCb* const deleteCb,
                              const void* opaque);
    virtual EAaConfigRet AaConfigTagSetU32(const char* name, u32 value);
    virtual TBoolean AaFileIsSecureEnvironment();
};
#endif //__CCS_DEFAULT_IMPL_H__
