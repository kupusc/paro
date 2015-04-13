#include <implementation/implementation.hpp>
#include <thread>
#include <iostream>

namespace problem
{
    int LegacyRandom::get42()
    {
        std::cerr << std::endl;
        for(int i=0; i < 60; ++i)
        {
            std::cerr << ".";
            std::this_thread::sleep_for(std::chrono::seconds(1));
        }
        std::cerr << std::endl;
        return 42;
    }
}
