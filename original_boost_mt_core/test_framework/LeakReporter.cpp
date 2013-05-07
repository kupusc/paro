#include "LeakReporter.h"

bool LeakReporter::LastLeaked = false;

LeakReporter::LeakReporter():mLeaksAreExpected(false) 
{
#ifdef _MSC_VER
    _CrtSetDbgFlag( _CRTDBG_ALLOC_MEM_DF );
    //_CrtSetReportMode( _CRT_ERROR, _CRTDBG_MODE_FILE);
    //_CrtSetReportFile( _CRT_ERROR, _CRTDBG_FILE_STDERR);
    _CrtSetReportMode( _CRT_WARN, _CRTDBG_MODE_FILE);
    _CrtSetReportFile( _CRT_WARN, _CRTDBG_FILE_STDERR);
    _CrtMemCheckpoint( &memStateBeforeTest ); 
#endif
}

LeakReporter::~LeakReporter()
{
    if(!mLeaksAreExpected)
    {
#ifdef _MSC_VER
        _CrtMemState memStateAfterTest;
        _CrtMemCheckpoint( &memStateAfterTest );

        _CrtMemState diff;
        if(LastLeaked = (0 != _CrtMemDifference( &diff, &memStateBeforeTest, &memStateAfterTest )) )
        {
            _CrtMemDumpAllObjectsSince( &memStateBeforeTest );
            _CrtMemDumpStatistics( &diff );
        }
#endif
    }
}

void LeakReporter::setLeaksAreExpected() 
{
    mLeaksAreExpected = true;
}
