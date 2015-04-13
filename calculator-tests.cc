#define BOOST_AUTO_TEST_MAIN
#define BOOST_TEST_MODULE calculator_tests
#define BOOST_TEST_DYN_LINK

#include <boost/test/auto_unit_test.hpp>
#include <turtle/mock.hpp>

#include <calculator.hpp>

using namespace std;
using namespace problem;

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

BOOST_AUTO_TEST_CASE(dummy)
{
    Calculator c;
}

BOOST_AUTO_TEST_SUITE_END();
