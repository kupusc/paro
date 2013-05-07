#ifndef __TEST_TOOLS_H__
#define __TEST_TOOLS_H__

#include <string>
#include <sstream>
#include <cassert>

void hex_dump(void* ptr, size_t size);

template <typename T>
T * parse_ptr(std::string ptr)
{
    T * res;
    assert( std::string::npos==ptr.find_first_not_of("0123456789ABCDEFxX"));
    std::istringstream is(ptr);
    unsigned long long ptr_value;
    is >> std::hex >>ptr_value;
    res=reinterpret_cast<T*>(ptr_value);
    return res;
}

template <typename T>
std::string hex_to_string(T number)
{
    std::ostringstream os;

    os << std::hex << number ;
    return os.str();
}


#endif
