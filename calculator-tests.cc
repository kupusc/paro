#include <iostream>
#include <unistd.h>

#define BOOST_AUTO_TEST_MAIN
#define BOOST_TEST_MODULE calculator_tests
#define BOOST_TEST_DYN_LINK

#include <boost/test/auto_unit_test.hpp>

#include <calculator.hpp>

using namespace std;

namespace
{
    struct Fixture
    {
        Fixture()
        {
            problem::initBugs();
        }
    };

}


BOOST_FIXTURE_TEST_SUITE(example, Fixture);

BOOST_AUTO_TEST_CASE( stub_test )
{
    BOOST_CHECK_EQUAL(69, 69);
}


BOOST_AUTO_TEST_SUITE_END();
