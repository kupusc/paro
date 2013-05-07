
#include "test_tools.h"
#include <iostream>
#include <iomanip>
#include "console_output.h"

using namespace std;

void hex_dump(void* ptr, size_t size)
{
        using boostMT::cout;
        using boostMT::endl;

        boost::recursive_mutex::scoped_lock lock(cout.get_mutex() );
        ostringstream os;

        for (size_t i = 0; i < size; ++i)
	{
		os  << "0x" << hex << setw(2) << setfill('0')
			<< static_cast<unsigned int>((reinterpret_cast<unsigned char*>(ptr))[i]) << (i < size - 1 ? "," : "\n");
	}

	cout << os.str();
}

