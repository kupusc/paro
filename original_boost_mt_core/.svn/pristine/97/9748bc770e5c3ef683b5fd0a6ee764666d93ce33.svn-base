#include "logformatting.h"

std::string boostMT::formatTime(boost::posix_time::time_duration td)
{
    std::string result = to_simple_string(td);
    // if result is in format "00:00:00" then we add ".00"
    if (result.size() == 8)
    {
        result += ".00";
    }
    else
    {
        // keep only "00:00:00.00"
        result.resize(11);
    }
    return result;
}

