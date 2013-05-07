#ifndef _TESTIF_H_67856235
#define _TESTIF_H_67856235
/*
* This is main header containing declarations of all testing functionality
*

Examples:

//Wait default time for matching single log line by string comparision (note: the whole string is compared to whole log line)
LOG_CHECK << "Sample debug print line" << WAIT();


//Wait default time for matching single log line using regex pattern
LOG_CHECK << regex("Sample debug print.*") << WAIT();


//Wait default time for matching one or many log lines (eg. databae prints) using regex pattern
//In this case the log lines are concatenated and then compared against the regex pattern;
LOG_CHECK << multiregex("-<DBChange> <ALDCVoltage>.*</ALDCVoltage>.*</DBChange>") << WAIT();


//Wait default time for matching many log lines which may occur in any order
//The matching procedure could be simple string comparision, regex, multiregex, timeout
LOG_CHECK << "Sample debug print line" << regex(Sample debug print.*)<<  WAIT();

*/
#include "logcheckerstreamer.h"
#include "dbg_prints.h"
#include "sw_conf_table.h"

#define LOG_CHECK LogCheckerStreamer(__FILE__,__LINE__) 
#define WAIT(...) LogCheckerStreamer::getTimeoutHelper(__VA_ARGS__)
#define PRINT(x) dbg_print(MON_SEVERITY_INFO, FEAT_DBG_Generic, "%s", "------> " x " <------");
#define LOG_PRINT(...) dbg_print(MON_SEVERITY_INFO,FEAT_DBG_Generic,__VA_ARGS__)
#define RESULTS dbg_prints::instance()->getLastResults()



/*
D E P R E C A T E D
*/
#define CHECK_LOG(a,...) dbg_prints::instance()->wait4print(new StringLogChecker(a),__VA_ARGS__)
#define CHECK_LOG_REGEXP(a,...) dbg_prints::instance()->wait4print(new RegexLogChecker(a),__VA_ARGS__)
#define CHECK_LOG_MULTILINE_REGEXP(a,...) dbg_prints::instance()->wait4print(new MultiRegexLogChecker(a),__VA_ARGS__)

#endif //_TESTIF_H_67856235

