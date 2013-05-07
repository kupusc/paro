#ifndef _SHOW_CALSTACK_
#define _SHOW_CALSTACK_

#ifndef DISABLE_STACKWALKER

#pragma init_seg(compiler)

#include "StackWalker.h"
#include "dbg_prints.h"
#include <boost/scoped_ptr.hpp>

LONG NTAPI handleException(PEXCEPTION_POINTERS pExceptionInfo ) ;

class MyStackWalker : public StackWalker
{
public:
    MyStackWalker() : StackWalker() {}
    MyStackWalker(DWORD dwProcessId, HANDLE hProcess) : StackWalker(dwProcessId, hProcess) {}
    virtual void OnOutput(LPCSTR szText)
    { 
        dbg_prints::instance()->addPrint(szText);
    }

    virtual ~MyStackWalker(){}
};

class CrashHandler 
{
    friend LONG NTAPI handleException(PEXCEPTION_POINTERS pExceptionInfo ) ;
private:
    bool mCatchesExceptions;
    static boost::scoped_ptr<CrashHandler> __instance;

    CrashHandler() :mCatchesExceptions(true)
    {
        dbg_prints::instance()->addPrint("Registering CrashTest exception handler");
        AddVectoredExceptionHandler( 1, handleException );
    }
public:
    virtual ~CrashHandler(){}

    static CrashHandler* getInstance()
    {    
        if(__instance)
        {
            return __instance.get();
        }
        else
        {
            __instance.reset(new CrashHandler());
            return __instance.get();
        }
    }    

    void setCatchesExceptions(bool works) {
        mCatchesExceptions = works;
    }
};

#endif
#endif
