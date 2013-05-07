#ifndef LOGFORMATTING_H_Z6XCR4VT
#define LOGFORMATTING_H_Z6XCR4VT

#include <boost/date_time/posix_time/posix_time.hpp>
#include <string>

namespace boostMT
{
    /**
     * @brief Formats time duration to simple string "00:00:00.00"
     *
     * @param td Elapsed time 
     *
     * @return Formatted time
     */
    std::string formatTime(boost::posix_time::time_duration td);    

}

#endif /* end of include guard: FORMATTING_H_Z6XCR4VT */

