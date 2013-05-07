#include "CrashHandler.h"

PVOID h1;
boost::scoped_ptr<CrashHandler> CrashHandler::__instance;

void showCallstack(PCONTEXT contextRecord) {
    MyStackWalker sw;
    sw.OnOutput("-=-= Kernel Error Handler =-=-");
    sw.ShowCallstack(GetCurrentThread(), contextRecord);
}

LONG NTAPI handleException(PEXCEPTION_POINTERS pExceptionInfo ) 
{
    if(CrashHandler::getInstance()->mCatchesExceptions) {
        if (pExceptionInfo->ExceptionRecord->ExceptionCode == EXCEPTION_ACCESS_VIOLATION) 
        {
            showCallstack(pExceptionInfo->ContextRecord);
            return EXCEPTION_CONTINUE_SEARCH;
        }
        else if (pExceptionInfo->ExceptionRecord->ExceptionCode == EXCEPTION_ARRAY_BOUNDS_EXCEEDED) 
        {
            showCallstack(pExceptionInfo->ContextRecord);
            return EXCEPTION_CONTINUE_SEARCH;
        }
        else if (pExceptionInfo->ExceptionRecord->ExceptionCode == EXCEPTION_BREAKPOINT) 
        {
            showCallstack(pExceptionInfo->ContextRecord);
            return EXCEPTION_CONTINUE_SEARCH;
        }
        if (pExceptionInfo->ExceptionRecord->ExceptionCode == EXCEPTION_DATATYPE_MISALIGNMENT) 
        {
            showCallstack(pExceptionInfo->ContextRecord);
            return EXCEPTION_CONTINUE_SEARCH;
        }
        if (pExceptionInfo->ExceptionRecord->ExceptionCode == EXCEPTION_FLT_DENORMAL_OPERAND) 
        {
            showCallstack(pExceptionInfo->ContextRecord);
            return EXCEPTION_CONTINUE_SEARCH;
        }
        if (pExceptionInfo->ExceptionRecord->ExceptionCode == EXCEPTION_FLT_DIVIDE_BY_ZERO) 
        {
            showCallstack(pExceptionInfo->ContextRecord);
            return EXCEPTION_CONTINUE_SEARCH;
        }
        if (pExceptionInfo->ExceptionRecord->ExceptionCode == EXCEPTION_FLT_INEXACT_RESULT) 
        {
            showCallstack(pExceptionInfo->ContextRecord);
            return EXCEPTION_CONTINUE_SEARCH;
        }
        if (pExceptionInfo->ExceptionRecord->ExceptionCode == EXCEPTION_FLT_INVALID_OPERATION) 
        {
            showCallstack(pExceptionInfo->ContextRecord);
            return EXCEPTION_CONTINUE_SEARCH;
        }
        if (pExceptionInfo->ExceptionRecord->ExceptionCode == EXCEPTION_FLT_OVERFLOW) 
        {
            showCallstack(pExceptionInfo->ContextRecord);
            return EXCEPTION_CONTINUE_SEARCH;
        }
        if (pExceptionInfo->ExceptionRecord->ExceptionCode == EXCEPTION_FLT_STACK_CHECK) 
        {
            showCallstack(pExceptionInfo->ContextRecord);
            return EXCEPTION_CONTINUE_SEARCH;
        }
        if (pExceptionInfo->ExceptionRecord->ExceptionCode == EXCEPTION_FLT_UNDERFLOW) 
        {
            showCallstack(pExceptionInfo->ContextRecord);
            return EXCEPTION_CONTINUE_SEARCH;
        }
        if (pExceptionInfo->ExceptionRecord->ExceptionCode == EXCEPTION_INT_DIVIDE_BY_ZERO) 
        {
            showCallstack(pExceptionInfo->ContextRecord);
            return EXCEPTION_CONTINUE_SEARCH;
        }
        if (pExceptionInfo->ExceptionRecord->ExceptionCode == EXCEPTION_INT_OVERFLOW) 
        {
            showCallstack(pExceptionInfo->ContextRecord);
            return EXCEPTION_CONTINUE_SEARCH;
        }
        if (pExceptionInfo->ExceptionRecord->ExceptionCode == EXCEPTION_NONCONTINUABLE_EXCEPTION) 
        {
            showCallstack(pExceptionInfo->ContextRecord);
            return EXCEPTION_CONTINUE_SEARCH;
        }
        if (pExceptionInfo->ExceptionRecord->ExceptionCode == EXCEPTION_PRIV_INSTRUCTION) 
        {
            showCallstack(pExceptionInfo->ContextRecord);
            return EXCEPTION_CONTINUE_SEARCH;
        }
        if (pExceptionInfo->ExceptionRecord->ExceptionCode == EXCEPTION_SINGLE_STEP) 
        {
            showCallstack(pExceptionInfo->ContextRecord);
            return EXCEPTION_CONTINUE_SEARCH;
        }
    }

    return EXCEPTION_CONTINUE_SEARCH;
}