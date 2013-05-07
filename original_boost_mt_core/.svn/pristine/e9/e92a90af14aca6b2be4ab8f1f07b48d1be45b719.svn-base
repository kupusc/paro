
#include "logcheckerstreamer.h"
#include "dbg_prints.h"
#include "regex_logchecker.h"
#include "multiregex_logchecker.h"
#include "dbchange_logchecker.h"
#include "soap_logchecker.h"

LogCheckerStreamer::LogCheckerStreamer(std::string filename, int line) : m_filename(filename) , m_line(line), waitedForPrint(false)
{
}

LogCheckerStreamer::~LogCheckerStreamer(void)
{
    waitForPrint();
}

LogCheckerStreamer& LogCheckerStreamer::operator<<(const std::string s )
{
    m_listLogChecker.addLogChecker(new SubStringLogChecker(s));
    return *this;
}
LogCheckerStreamer& LogCheckerStreamer::operator<<(LogCheckerBase* logChecker)
{
    m_listLogChecker.addLogChecker(logChecker);
    return *this;
}
LogCheckerStreamer& LogCheckerStreamer::operator<<(const StringLogChecker & logChecker)
{
    m_listLogChecker.addLogChecker(new StringLogChecker(logChecker));
    return *this;
}
LogCheckerStreamer& LogCheckerStreamer::operator<<(const SubStringLogChecker & logChecker)
{
    m_listLogChecker.addLogChecker(new SubStringLogChecker(logChecker));
    return *this;
}
LogCheckerStreamer& LogCheckerStreamer::operator<<(const RegexLogChecker& logChecker)
{
    m_listLogChecker.addLogChecker(new RegexLogChecker(logChecker));
    return *this;
}
LogCheckerStreamer& LogCheckerStreamer::operator<<(const MultiRegexLogChecker& logChecker)
{
    m_listLogChecker.addLogChecker(new MultiRegexLogChecker(logChecker));
    return *this;
}
LogCheckerStreamer& LogCheckerStreamer::operator<<(const DBChangeLogChecker& logChecker)
{
    m_listLogChecker.addLogChecker(new DBChangeLogChecker(logChecker));
    return *this;
}
LogCheckerStreamer& LogCheckerStreamer::operator<<(const SOAPLogChecker& logChecker)
{
    m_listLogChecker.addLogChecker(new SOAPLogChecker(logChecker));
    return *this;
}
LogCheckerStreamer& LogCheckerStreamer::operator<<(boost::posix_time::time_duration timeout)
{
    m_timeout = timeout;
    return *this;
}

LogCheckerBase::TMatches LogCheckerStreamer::waitForPrint() {
    if(!waitedForPrint) {
        waitedForPrint = true;
        return dbg_prints::instance()->wait4print(getLogChecker(),m_filename,m_line,getTimeout());
    } else
        return vector<string>();
}




