//#include "test_framework.h"
#pragma message("including stackWalker.h")
/**********************************************************************
 * 
 * StackWalker.h
 *
 *
 * History:
 *  2005-07-27   v1    - First public release on http://www.codeproject.com/
 *  (for additional changes see History in 'StackWalker.cpp'!
 *
 **********************************************************************/
// #pragma once is supported starting with _MCS_VER 1000, 
// so we need not to check the version (because we only support _MSC_VER >= 1100)!
#pragma once

#include <windows.h>

// special defines for VC5/6 (if no actual PSDK is installed):
#if _MSC_VER < 1300
typedef unsigned __int64 DWORD64, *PDWORD64;
#if defined(_WIN64)
typedef unsigned __int64 SIZE_T, *PSIZE_T;
#else
typedef unsigned long SIZE_T, *PSIZE_T;
#endif
#endif  // _MSC_VER < 1300

class StackWalkerInternal;  // forward
class StackWalker
{
public:
  typedef enum StackWalkOptions
  {
    // No addition info will be retrived 
    // (only the address is available)
    RetrieveNone = 0,
    
    // Try to get the symbol-name
    RetrieveSymbol = 1,
    
    // Try to get the line for this symbol
    RetrieveLine = 2,
    
    // Try to retrieve the module-infos
    RetrieveModuleInfo = 4,
    
    // Also retrieve the version for the DLL/EXE
    RetrieveFileVersion = 8,
    
    // Contains all the abouve
    RetrieveVerbose = 0xF,
    
    // Generate a "good" symbol-search-path
    SymBuildPath = 0x10,
    
    // Also use the public Microsoft-Symbol-Server
    SymUseSymSrv = 0x20,
    
    // Contains all the abouve "Sym"-options
    SymAll = 0x30,
    
    // Contains all options (default)
    OptionsAll = 0x3F
  } StackWalkOptions;

  StackWalker(
    int options = OptionsAll, // 'int' is by design, to combine the enum-flags
    LPCSTR szSymPath = NULL, 
    DWORD dwProcessId = GetCurrentProcessId(), 
    HANDLE hProcess = GetCurrentProcess()
    );
  StackWalker(DWORD dwProcessId, HANDLE hProcess);
  virtual ~StackWalker();

  typedef BOOL (__stdcall *PReadProcessMemoryRoutine)(
    HANDLE      hProcess,
    DWORD64     qwBaseAddress,
    PVOID       lpBuffer,
    DWORD       nSize,
    LPDWORD     lpNumberOfBytesRead,
    LPVOID      pUserData  // optional data, which was passed in "ShowCallstack"
    );

  BOOL LoadModules();

  BOOL ShowCallstack(
    HANDLE hThread = GetCurrentThread(), 
    const CONTEXT *context = NULL, 
    PReadProcessMemoryRoutine readMemoryFunction = NULL,
    LPVOID pUserData = NULL  // optional to identify some data in the 'readMemoryFunction'-callback
    );

#if _MSC_VER >= 1300
// due to some reasons, the "STACKWALK_MAX_NAMELEN" must be declared as "public" 
// in older compilers in order to use it... starting with VC7 we can declare it as "protected"
protected:
#endif
	enum { STACKWALK_MAX_NAMELEN = 1024 }; // max name length for found symbols

protected:
  // Entry for each Callstack-Entry
  typedef struct CallstackEntry
  {
    DWORD64 offset;  // if 0, we have no valid entry
    CHAR name[STACKWALK_MAX_NAMELEN];
    CHAR undName[STACKWALK_MAX_NAMELEN];
    CHAR undFullName[STACKWALK_MAX_NAMELEN];
    DWORD64 offsetFromSmybol;
    DWORD offsetFromLine;
    DWORD lineNumber;
    CHAR lineFileName[STACKWALK_MAX_NAMELEN];
    DWORD symType;
    LPCSTR symTypeString;
    CHAR moduleName[STACKWALK_MAX_NAMELEN];
    DWORD64 baseOfImage;
    CHAR loadedImageName[STACKWALK_MAX_NAMELEN];
  } CallstackEntry;

  typedef enum CallstackEntryType {firstEntry, nextEntry, lastEntry};

  virtual void OnSymInit(LPCSTR szSearchPath, DWORD symOptions, LPCSTR szUserName);
  virtual void OnLoadModule(LPCSTR img, LPCSTR mod, DWORD64 baseAddr, DWORD size, DWORD result, LPCSTR symType, LPCSTR pdbName, ULONGLONG fileVersion);
  virtual void OnCallstackEntry(CallstackEntryType eType, CallstackEntry &entry);
  virtual void OnDbgHelpErr(LPCSTR szFuncName, DWORD gle, DWORD64 addr);
  virtual void OnOutput(LPCSTR szText);

  StackWalkerInternal *m_sw;
  HANDLE m_hProcess;
  DWORD m_dwProcessId;
  BOOL m_modulesLoaded;
  LPSTR m_szSymPath;

  int m_options;

  static BOOL __stdcall myReadProcMem(HANDLE hProcess, DWORD64 qwBaseAddress, PVOID lpBuffer, DWORD nSize, LPDWORD lpNumberOfBytesRead);

  friend StackWalkerInternal;
};


// The "ugly" assembler-implementation is needed for systems before XP
// If you have a new PSDK and you only compile for XP and later, then you can use 
// the "RtlCaptureContext"
// Currently there is no define which determines the PSDK-Version... 
// So we just use the compiler-version (and assumes that the PSDK is 
// the one which was installed by the VS-IDE)

// INFO: If you want, you can use the RtlCaptureContext if you only target XP and later...
//       But I currently use it in x64/IA64 environments...
//#if defined(_M_IX86) && (_WIN32_WINNT <= 0x0500) && (_MSC_VER < 1400)

#if defined(_M_IX86)
#ifdef CURRENT_THREAD_VIA_EXCEPTION
// TODO: The following is not a "good" implementation, 
// because the callstack is only valid in the "__except" block...
#define GET_CURRENT_CONTEXT(c, contextFlags) \
  do { \
    memset(&c, 0, sizeof(CONTEXT)); \
    EXCEPTION_POINTERS *pExp = NULL; \
    __try { \
      throw 0; \
    } __except( ( (pExp = GetExceptionInformation()) ? EXCEPTION_EXECUTE_HANDLER : EXCEPTION_EXECUTE_HANDLER)) {} \
    if (pExp != NULL) \
      memcpy(&c, pExp->ContextRecord, sizeof(CONTEXT)); \
      c.ContextFlags = contextFlags; \
  } while(0);
#else
// The following should be enough for walking the callstack...
#define GET_CURRENT_CONTEXT(c, contextFlags) \
  do { \
    memset(&c, 0, sizeof(CONTEXT)); \
    c.ContextFlags = contextFlags; \
    __asm    call x \
    __asm x: pop eax \
    __asm    mov c.Eip, eax \
    __asm    mov c.Ebp, ebp \
    __asm    mov c.Esp, esp \
  } while(0);
#endif

#else

// The following is defined for x86 (XP and higher), x64 and IA64:
#define GET_CURRENT_CONTEXT(c, contextFlags) \
  do { \
    memset(&c, 0, sizeof(CONTEXT)); \
    c.ContextFlags = contextFlags; \
    RtlCaptureContext(&c); \
} while(0);
#endif
