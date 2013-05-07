
#ifndef __CCS_STUB_H__
#define __CCS_STUB_H__

#include "IfAaGpuDur.h"
#include "IfAaPro.h"
#include "IfAaConfig.h"
#include "IfAaFile.h"
#include "IfAaSysLog.h"
#include "IfAaFileTftp.h"
#include "IfAaSysCom.h"
#include "TAaSysComSicad.h"
#include "TMsgHeaderTypes.h"
#include "IfAaSysMb.h"
#include "IfAaSem.h"
#include "IfAaFileSicFtp.h"
#include "IfAaSNTP.h"
#include "IfAaTrbl.h"
#include "IfAaFileCompression.h"
#include "IfAaCpu.h"
#include "IfAaSemRwLock.h"
#include "IfAaGpuChecksums.h"
#include "IfAaMem.h"
#include "IfAaGpuAdler32.h"


class ICcsStubImpl;
class CcsStubImplDefault;

class CcsStub
{
	CcsStub();
	~CcsStub();
	CcsStub(const CcsStub &);
public:
	static void set(ICcsStubImpl *);
	static void setDefault();
	static ICcsStubImpl * get();
private:
	static ICcsStubImpl * current;
	static ICcsStubImpl * default_impl;
};


class ICcsStubImpl
{
public:
	ICcsStubImpl()
	{
		CcsStub::set(this);
	}
	~ICcsStubImpl()
	{
		CcsStub::setDefault();
	}
	virtual void *AaSysComMsgCreate(const TAaSysComMsgId messageId,
                        const TAaSysComMsgSize messagePayloadSize,
                        const TAaSysComSicad messageTarget) =0 ;
	virtual EAaProEuRetVal 
	AaProEuCreateAndStart( u32*                 euIdPtr,
						   const char          *euNamePtr,
						   TAaProEuEntryPoint  *euEntryPoint,
						   u32                  euStackSize,
						   u32                  euPriority,
						   void*                euArgPtr,
						   u32                  sizeOfeuArg ) = 0;	
	virtual TAaSysComCpid AaSysComUserRegister(const TAaSysComCpid userCpid, const u32 euId) =0;
	virtual TAaSysComSicad AaSysComNmapGetSicad(const TBoard board, const TCpu cpu, const TTask task)=0;
	virtual void AaGpuDurFree(TAaGpuDurHandle *handle)= 0;
	virtual void *AaSysMbPrepare(const TAaSysComMsgSize messagePayloadSize,
                    const TAaSysComMsgId messageId,
                    const TAaSysComSicad publisher,
                    const EAaSysMbPublMode mode,
                    const TAaSysMbZoneId zone) = 0;
	virtual EAaSysMbRetVal AaSysMbSubscribe(const TAaSysComMsgId messageId,
                      const TAaSysComSicad subscriber,
                      const EAaSysMbSubsMode mode,
                      const TAaSysMbZoneId zone) = 0;
	virtual EAaSysMbRetVal AaSysMbPublish(void **payload) = 0;
	virtual u32 AaProEuCurrent(void) = 0;
	virtual TAaSysComNid AaSysComGetOwnNid(void) =0 ;
	virtual TAaSysComSicad AaSysComSicadGet(const TAaSysComCpid userCpid,const TAaSysComNid userNid) =0;
	virtual void *AaSysComMsgGetPayload(const void *message)=0;
	virtual TAaSysComMsgSize AaSysComMsgGetPayloadSize(const void *message)=0;
	virtual TAaSysComMsgId AaSysComMsgGetId(const void *message) = 0;
	virtual TAaSysComSicad AaSysComMsgGetSender(const void *message) = 0;
	virtual TBoard AaSysComNmapGetBoard(TAaSysComSicad sicAddress) = 0;
	virtual TCpu AaSysComNmapGetCpu(TAaSysComSicad sicAddress) = 0 ;
	virtual TAaSysComSicad AaSysComMsgGetReceiver(const void *message) = 0;
	virtual TTask AaSysComNmapGetTask(TAaSysComSicad sicAddress) = 0 ;
	virtual void AaSysComMsgSend(void **message) = 0;
	virtual void AaSysComMsgSetSender(const void *message,const TAaSysComSicad messageSource) = 0;
	virtual TAaSysComCpid AaSysComUserDeregister(const TAaSysComCpid userCpid) = 0;
	virtual u32 AaConfigRadGetValue(u32 tag) = 0;
	virtual const char* AaConfigRadGetTagString(u32 tag) = 0;
	virtual EAaConfigRet AaConfigRadRegisterDomain(u32 domain,
                                       const char* nameStringPtr,
                                       void (*initializeParameters)(void)) = 0;
	virtual EAaConfigRet AaConfigRadSetValue(u32 tag, u32 value) = 0;
	virtual EAaConfigRet AaConfigRadSetDefault(u32         tag,
                                   const char* stringPtr,
                                   u32         initialValue) = 0;
	virtual EAaConfigRet AaConfigRadSetMaxTagCount(u32 domain, u32 count) = 0;
	virtual EAaSysTimeRetVal AaUnixTimeGet(SAaBtsTimeval * const timePtr) = 0;
	virtual EAaFileRet AaFileClose(TAaFile *stream) = 0;
	virtual EAaFileRet AaFileRemove(const char *fileName) = 0;
	virtual void va_AaSysLogPrint(const EAaSysLogSeverityLevel severityLevel,
                   const char*  unformattedStringPtr, va_list argptr) = 0;
	virtual void AaSysLogVPrintE(const EAaSysLogSeverityLevel severityLevel,
                     const u32                    featureId, 
                     const char*                  unformattedStringPtr,
                     va_list                      args) = 0;			   
	virtual TAaFile *AaFileOpen(const char *fileName, const char *mode) = 0;
    virtual size_t AaFileWrite(void *ptr, size_t size, size_t nitems, TAaFile* stream) = 0;
    virtual long AaFileGetSize(TAaFile *stream) = 0;
    virtual size_t AaFileRead(void *ptr, size_t size, size_t nitems, TAaFile *stream) = 0;
	virtual TAaSysComSicad AaSysComNmapGetSicAddress(const TBoard board, 
                                         const TCpu cpu, 
                                         const TTask task) = 0;
	virtual TAaSysTime64 AaSysTimeBcnGet(void) = 0;
	virtual EAaFileTftpErrorCode AaFileTftpGet(const char *ipAddress,
                                   const char *srcFilename,
                                   const char *dstFilename) = 0 ;
	virtual EAaConfigRet AaConfigTagSetString(const char* const name, 
                                  const char* const value) = 0;
	virtual EAaProEuRetVal AaProEuSetPri( u32 euId, u32 euPriority ) = 0;
	virtual u32 AaProEuGetPri(u32 euId) = 0;
	virtual void AaSemPost(TAaSem* semPtr) = 0;
	virtual void AaSemWait(TAaSem* semPtr) = 0;
	virtual u32 GetLteDownlinkFrequency(const u32 earfcn) = 0;
	virtual u32 GetLteUplinkFrequency(const u32 earfcn) = 0;
	virtual u32 GetWcdmaDownlinkFrequency(const u32 earfcn) = 0;
	virtual u32 GetWcdmaUplinkFrequency(const u32 earfcn) = 0;
	virtual void AaSysComMsgSetMtm(const void *message,const EAaSysComMtm requestedTransferMode) = 0;
	virtual TAaGpuDurHandle* AaGpuDurAlloc(char const * const name) = 0 ;
	virtual void AaGpuDurStart(TAaGpuDurHandle *handle) = 0;
	virtual void AaGpuDurStop(TAaGpuDurHandle *handle) = 0;
	virtual void AaFileFreeListDirArray(SAaFileDnode*** dirArray, u32 nfiles) = 0;
	virtual EAaFileRet AaFileListDir(SAaFileDnode*** dirArray, u32* nfilesp, const char* path, TBoolean recursive) = 0;
	virtual char* AaProEuGetName(u32 euId, char* buffer, u32 length)  = 0;
	virtual TAaSysComCpid AaSysComSicadGetCpid(const TAaSysComSicad sicAddress) = 0 ;
	virtual void AaSemCreateC( TAaSem** semPtr, u32      initialValue ) =0;
	virtual void AaSemDestroy(TAaSem* semPtr) = 0; 
	virtual void AaSemGetValue(TAaSem*  semPtr, i32*     semValuePtr) = 0 ;
	virtual void *AaSysComMsgReceiveFromEu(const u32 euId) = 0;
	virtual EAaSysTimeRetVal AaSysTimeSleep(const TAaSysTime sleepTime, const EAaSysTimeScale scale) = 0 ;
    virtual EAaFileRet AaFileCopy(const char* srcPath, const char* destPath)=0;
 	virtual void *AaSysComMsgReceive(const u32 maxTimeToWait) = 0;
    virtual EAaProEuRetVal AaProCmdExec(const char * command, const char * args, u32 flags, int * retVal) = 0;
	virtual TAaSysComHopId AaSysComHopRegister(const TAaSysComSicad destinationAddress, const u32 metric, const TAaSysComLinkId linkId) = 0;

    virtual void AaSemRwLockCreate(TAaSemRwLock** const lock) = 0;
    virtual void AaSemRwLockDestroy(TAaSemRwLock** const lock) = 0;
    virtual void AaSemRwLockReadLock(TAaSemRwLock* const lock) = 0;
    virtual void AaSemRwLockReadUnlock(TAaSemRwLock* const lock) = 0;
    virtual void AaSemRwLockWriteLock(TAaSemRwLock* const lock) = 0;
    virtual void AaSemRwLockWriteUnlock(TAaSemRwLock* const lock) = 0;

    virtual EAaConfigRet AaConfigTagRegister(const char* const name, 
                                             TAaConfigTagObserver* const callback) = 0;

    virtual EAaConfigRet AaConfigTagUnregister(const char* const name, 
                                               TAaConfigTagObserver* const callback) = 0;
                                               
    virtual void AaErrorAssertion(const char* const expression, const char* const file, const u32 line) = 0; 
    virtual void AaSysComMsgSetId(const void *message, const TAaSysComMsgId messageId) = 0; 
    virtual void AaSysComMsgSetReceiver(void **message, const TAaSysComSicad receiver) = 0; 
    virtual void* AaSysTimermDelete(const TAaSysTimerId timerId) = 0; 
    virtual EAaSysTimeRetVal AaSysTimermCreate(TAaSysTimerId* const timerIdPtr,	const TAaMicroSecond latency,	
                                        const TAaMicroSecond period,const void* const messagePtr) = 0; 
    virtual void *AaSysComMsgReceiveSelective(const u32 maxTimeToWait, const TAaSysComMsgId *messageIdFilter) = 0 ; 
    virtual EAaGpuChecksumsRet AaGpuChecksumsUninit(SAaGpuChecksumHandler* const handler) = 0; 
    virtual EAaGpuChecksumsRet AaGpuChecksumsUpdate(SAaGpuChecksumHandler* const handler, const void* const data, const u32 length) = 0; 
    virtual u32 AaGpuChecksumsValueGet(SAaGpuChecksumHandler* const handler) = 0; 
    virtual EAaGpuChecksumsRet AaGpuAdler32Init(SAaGpuChecksumHandler* const handler) = 0; 
    virtual void* AaMemAlloc(i32 const poolId, u32 const size ) = 0;
    virtual void* AaMemAllocId( i32 const poolId, u32 const size, u32 const blockId ) = 0;
    virtual u32 AaMemSizeGet( void const * const ptr ) = 0; 
    virtual void* AaMemAllocSafe( i32 const poolId, u32 const size ) = 0;
    virtual void* AaMemAllocSafeId(i32 const poolId, u32 const size, u32 const blockId ) = 0;
    virtual EAaMemRet AaMemBlockAddr2Obj(const void* const ptr, SAaMemBlockObj* blockObj) = 0;
    virtual void* AaMemBlockBaseGet( const void *ptr ) = 0; 
    virtual EAaMemRet AaMemBlockObj2Addr(const SAaMemBlockObj* const blockObj, void** ptr) = 0;
    virtual void* AaMemBlockPayloadGet( const void *ptr ) = 0;
    virtual EAaMemRet AaMemCeInit( void ) = 0;
    virtual EAaMemRet AaMemCeUninit( void ) = 0;
    virtual EAaMemRet AaMemEeInit(void) = 0;
    virtual EAaMemRet AaMemEeUninit(void) = 0; 
    virtual void* AaMemMalloc( u32 const size ) = 0;
    virtual SAaMemBlockObjClass* AaMemObjectClassGet( void const *ptr ) = 0;
    virtual EAaMemRet AaMemPoolAttach( i32* poolId, const char* poolName, const SAaMemPoolHandler* poolHndlr ) = 0;
    virtual EAaMemRet AaMemPoolDetach( i32 const poolId ) = 0;
    virtual void AaMemObjectClassSet( void const * const ptr, SAaMemBlockObjClass const * const objClass ) = 0;
    virtual EAaMemRet AaMemPoolInfoGet(i32 const poolId, SAaMemPoolInfo * poolInfo) = 0;
    virtual void* AaMemPoolOpaqueGet( const void * const basePtr ) = 0;
    virtual void* AaMemRef( void* const ptr ) = 0;
    virtual EAaFileRet AaFileGzCompress(const char* srcFileName, const char* destFileName) = 0;
    virtual EAaFileRet AaFileCeShutdown(void) = 0;
    virtual EAaFileRet AaFileCeStartup(void) = 0;
    virtual EAaFileRet AaFileCopyDir(const char* srcPath, const char* destPath) = 0;
    virtual EAaFileRet AaFileGzDecompress(const char* srcFileName, const char* destFileName) = 0;
    virtual EAaFileRet AaFileEeShutdown(void) = 0;
    virtual EAaFileRet AaFileEeStartup(void) = 0;
    virtual EAaFileRet AaFileFlush(TAaFile *stream) = 0;
    virtual EAaFileRet AaFileForceUnlock(const char *filename) = 0;
    virtual TAaFile *AaFileOpenWithLock(const char *fileName, const char *mode, TBoolean* locked) = 0;
    virtual EAaFileRet AaFileRemoveDir(const char* path) = 0;
    virtual int AaFileSicFtpInit(void) = 0;
    virtual EAaFileSicFtpRet AaFileSicFtpPut( TAaSysComNid remoteNode, const char* srcFilePath, const char* destFilePath) = 0;
    virtual EAaFileTftpErrorCode AaFileTftpGetExt(const char *ipAddress,  const char *srcFilename, const char *dstFilename, u32 timeout, u32 retries) = 0;
    virtual int AaFileTftpInit(void) = 0;
    virtual EAaFileTftpErrorCode AaFileTftpPut(const char *ipAddress, const char *srcFilename, const char *dstFilename) = 0;
    virtual EAaFileTftpErrorCode AaFileTftpPutExt(const char *ipAddress,  const char *srcFilename, const char *dstFilename, u32 timeout, u32 retries) = 0; 
	virtual EAaFileRet AaFileSeek(TAaFile *stream, long offset, int whence)=0;
	virtual long AaFileTell(TAaFile *stream)=0;
    virtual char* AaFileGetAbsPath(const char* path) =0;
    virtual EAaFileRet AaFileRename(const char *oldPath, const char *newPath)=0;
    virtual void AaMemUnRef( void const ** const ptr ) =0;
    virtual EAaFileSicFtpRet AaFileSicFtpList( TAaSysComNid remoteNode, const char* path, TAaFileListing *fileList)=0;
    virtual EAaFileSicFtpRet AaFileSicFtpRemoveDir( TAaSysComNid remoteNode, const char* dirPath)=0;
    virtual EAaFileSicFtpRet AaFileSicFtpRemove( TAaSysComNid remoteNode, const char* destFilePath)=0;
    virtual EAaFileSicFtpRet AaFileSicFtpGet( TAaSysComNid remoteNode, const char* srcFilePath, const char* destFilePath)=0;
    virtual TBoolean AaFileSign(const char* filePath, const char* signaturePath, const char* digestTypeStr) =0; 
	virtual EAaFileRet AaFileCreateDir(const char *path)=0;
    virtual EAaConfigRet AaConfigSubscribeService(const char* const namePtr, const u32 major_version, const u32 minor_version, EAaConfigSvcRegScope scope, TAaSysComSicad sicad) = 0;
    virtual EAaConfigRet AaConfigUnSubscribeService(const char* const namePtr, const u32 major_version, const u32 minor_version, TAaSysComSicad sicad) = 0;
    virtual TAaSysTime64 AaTicks64Get()=0;
    virtual TAaSysTime64 AaSysTime64SinceGet(TAaSysTime64* timeref, const EAaSysTimeScale scale)=0;
    virtual u32 AaFileGzWrite(void *inbuf, u32 inlen, TAaGzFile* gzstream) = 0;
    virtual TAaGzFile* AaFileGzOpen(const char* fileName, const char *mode) = 0;
    virtual EAaFileRet AaFileGzClose(TAaGzFile* gzstream) = 0;
    virtual void AaSysComEnd32Swap(const void *firstField, const u32 numberOfFields)=0;
    virtual TAaSysComNid AaSysComSicadGetNid(TAaSysComSicad sicAddress)=0;
    virtual EAaTrblRet AaTrblFileRegister(char const* const logicalFileName,
                                      char const* const physicalFileName,
                                      EAaTrblFilePriority priority,
                                      TBoolean compressed,                              
                                      TAaTrblPrepareFileCb* const prepareCb,
                                      TAaTrblStoreFileCb* const storeCb,
                                      TAaTrblDeleteFileCb* const deleteCb,
                                      const void* opaque) = 0; 
    virtual EAaConfigRet AaConfigTagSetU32(const char* name, u32 value) = 0;
    virtual TBoolean AaFileIsSecureEnvironment()=0;
}; 

#endif //__CCS_STUB_H__
