#include <iostream>
#include <boost/function.hpp>
#include <boost/bind.hpp>
#include <boost/thread.hpp>

void createTimer(int timeout, boost::function<void(int,float)> fun)
{
    sleep(timeout);
    fun(timeout, 2);
}

struct A
{
    void operator()(int a, float b)
    {
        std::cout << __PRETTY_FUNCTION__ << a << b << std::endl;
    }

    void operator()(int a, int b)
    {
        std::cout << __PRETTY_FUNCTION__ << a << b << std::endl;
    }
};

struct B
{
    void report(char a)
    {
        std::cout << __PRETTY_FUNCTION__ << a << std::endl;
    }

    int report(char a, int b)
    {
        std::cout << __PRETTY_FUNCTION__ << a << b << std::endl;
    }
};

void blah(void* a)
{
    std::cout << __PRETTY_FUNCTION__ << a << std::endl;
}

int main(int argc, char const *argv[])
{
    // A abc;
    createTimer(0, A());

    void* ptr = (void*)2;
    createTimer(0, boost::bind(&blah, ptr));

    B b;
    createTimer(0, boost::bind(&B::report, &b, _1, _2));

    boost::thread t(boost::bind(createTimer, 1, A()));
    // boost::thread tt(boost::bind(createTimer, 1, &blah, ptr));
    
    t.join();
    // tt.join();

    return 0;
}