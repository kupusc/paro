#include <calculator.hpp>
#include <bug-introducer.hpp>
#include <boost/bind.hpp>
#include <boost/thread.hpp>
#include <vector>

using namespace std;

namespace problem
{
    void initBugs()
    {
        bug_introducer::detail::Registry::getInstance().init();
    }


    Calculator::Calculator()
    {
	if(INTRODUCE_BUG(false))
		throw std::runtime_error("Construction bailed out!");
        //cout << "blah" << endl;
    }

    int Calculator::return42()
    {
	int a,b;
	a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8;
	a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8;
	a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8;
	a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8;
	a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8;
	a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8;
	a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8;
	a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8;
	a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8;
	a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8;
	a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8;
	a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8;
	a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8;
	a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8;
	a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8;
	a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8;
	a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8;
	a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8;
	a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8;
	a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8;
	a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8;
	a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8;
	a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8;
	a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8;
	a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8;
	a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8;
	a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8;
	a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8;
	a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8;
	a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8;
	a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8;
	a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8;
	a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8;
	a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8;
	a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8;
	a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8;
	a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8;
	a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8;
	a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8;
	a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8;
        a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8;
        a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8;
        a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8;
        a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8;
        a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8;
        a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8;
        a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8;
        a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8;
        a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8;
        a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8;
        a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8;
        a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8;
        a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8;
        a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8;
        a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8;
        a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8;
        a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8;
        a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8;
        a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8;
        a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8;
        a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8;
        a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8;
        a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8;
        a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8;
        a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8;
        a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8;
        a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8;
        a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8;
        a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8;
        a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8;
        a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8;
        a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8;
        a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8;
        a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8;
        a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8;
        a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8;
        a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8;
        a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8;
        a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8;
	a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8; a = 0; b=8;
	return INTRODUCE_BUG(42); 
    }

    int Calculator::returnSum(int a, int b)
    {
	return(INTRODUCE_BUG(a+b));
    }

    unsigned int Calculator::findFirst(IPredicate &predicate, float start, float step)
    {
        unsigned int i = INTRODUCE_BUG(0);

        if(INTRODUCE_BUG(false))
            start += step;

        while(INTRODUCE_BUG(!predicate(start)))
        {
            start += step;
            ++i;
        }

        if(INTRODUCE_BUG(false))
            (void)predicate(start);

        return INTRODUCE_BUG(i);
    }

    void Calculator::calcForEach(boost::function<int(int)> convert, std::vector<int> &data)
    {
        PROTECT_MAX_CALL_COUNT();

        if(INTRODUCE_BUG(false))
        {
            (int)convert(5);
        }

        for(std::vector<int>::iterator i = data.begin(); data.end() != i; ++i)
        {
            *i = INTRODUCE_BUG(convert(*i));
        }
    }

    void Calculator::makeTransparent(ISystem &system, const std::string &imageIn, const std::string &imageOut)
    {
        PROTECT_MAX_CALL_COUNT();

        srand((unsigned int)time(NULL));

        if(!system.run(("convert " + INTRODUCE_BUG(imageIn) + 
            " -transparent white " +
            INTRODUCE_BUG(imageOut)).c_str(),  boost::posix_time::milliseconds(rand())))
        {
            if(INTRODUCE_BUG(true))
                throw std::runtime_error("system.run failed");
        }
    }

    void calcParallel(float value, float &result)
    {
        result = sin(value + (rand() % 10 - 5) / 20); 
    }

    float Calculator::runParallel(IThreadPool &threadPool, int numberOfTasks, float input)
    {
        srand((unsigned int)time(NULL));

        input += 3;

        std::vector<float> ar(numberOfTasks);

        bool wrongOrder = INTRODUCE_BUG(false);

        if(wrongOrder)
            threadPool.join();

        for(int i = INTRODUCE_BUG(0); i < numberOfTasks; ++i)
        {
            threadPool.addTask(boost::bind(calcParallel, input, boost::ref(ar[i])));
        }

        if(!wrongOrder)
            threadPool.join();

        float result = static_cast<float>(INTRODUCE_BUG(0));
        for(int i = INTRODUCE_BUG(0); i < numberOfTasks; ++i)
        {
            result += ar[i];
        }

        return result / numberOfTasks;
    }

    void Calculator::sendCustomStruct(ICustomStructReceiver &receiver, const std::string &aString, float aFloat, const std::map<int, bool> &aMap)
    {
        if(INTRODUCE_BUG(true))
        {
            receiver.take(CustomStruct(
                INTRODUCE_BUG(aString), 
                INTRODUCE_BUG(aFloat), 
                INTRODUCE_BUG(aMap)));
        }
    }

    /*void timer( int timeMS, boost::function< void() > fun )
    {
	boost::thread thr;
	
	thr.join();
    }*/
    
    
}
