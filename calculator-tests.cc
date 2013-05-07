#include <iostream>
#include <unistd.h>

#define BOOST_AUTO_TEST_MAIN
#define BOOST_TEST_MODULE calculator_tests
#define BOOST_TEST_DYN_LINK

#include <boost/test/auto_unit_test.hpp>
#include <original_boost_mt_core/test_framework/turtle/mock.hpp>
#include <boost/bind.hpp>
#include <boost/function.hpp>
#include <boost/assign/list_of.hpp>
#include <string>
#include <functional>
#include <boost/bind/apply.hpp>
#include <boost/thread.hpp>
#include <boost/foreach.hpp>

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

struct sleep_before_call 
{
    explicit sleep_before_call( int ms, boost::function< void() > f )
        : f_( f ), ms_( ms )
    {}
    void operator()()
    {
        //usleep( ms_ * 1000 );
        boost::this_thread::sleep( boost::posix_time::microseconds( ms_ * 1000 ) );
        f_();
    }
private:
    boost::function< void() > f_;
    int ms_;
};

void my_func( int x )
{
    std::cout << boost::posix_time::second_clock::local_time() 
        << " Timer [" << x << "] triggered (thread id = " 
        << boost::this_thread::get_id() << ")." << std::endl;
}

boost::thread timer( int msec, boost::function< void() > f )
{
    return boost::thread( sleep_before_call( msec, f ) );
}

BOOST_FIXTURE_TEST_SUITE(example, Fixture);

/*BOOST_AUTO_TEST_CASE( sendCustomStruct )
{
    BOOST_CHECK_EQUAL(69, 69);
    boost::thread thr1 = timer( 15000, boost::bind( my_func, 10 ) );
    boost::thread thr2 = timer( 5500, boost::bind( my_func, 20 ) );
    std::cout << "waiting for timers trigger...\n";
    thr1.join();
    thr2.join();
}*/

struct greater_than_predicate : problem::IPredicate
{
    greater_than_predicate( float upper )
        : upper_( upper )
    {}
    virtual bool operator()( float val )
    {
        std::cout << "less_than_predicate: val = " << val << std::endl;
        return val > upper_;
    }
    float upper_;
};

MOCK_BASE_CLASS( PredicateMock, problem::IPredicate )
{
    //MOCK_CONVERSION_OPERATOR( bool, conversion_to_bool )
    //MOCK_METHOD( operator bool(), 1, bool( float ), operator_bool );
    //MOCK_METHOD( operator(), 1 );
    //MOCK_METHOD( operator(), 1 );
    MOCK_METHOD_EXT( operator(), 1, bool( float ), pred_mock );
};

BOOST_AUTO_TEST_CASE( findFirst_should_return_first_greater )
{
    problem::Calculator calc;
    greater_than_predicate pred( 3.14 );
    unsigned int ret = calc.findFirst( pred, 0.0, 1 ); 
    std::cout << "ret = " << ret  << std::endl;
    BOOST_CHECK_EQUAL( ret, 4 );

    /*greater_than_predicate p2( 2.0 );
    ret = calc.findFirst( p2, 0.0, 0.3 );
    BOOST_CHECK_EQUAL( ret, 3 );*/
}

BOOST_AUTO_TEST_CASE( findFirst_should_0 )
{
    problem::Calculator calc;
    PredicateMock pred;
    MOCK_EXPECT( pred.pred_mock ).once().with(mock::any).returns( true );
    BOOST_CHECK_EQUAL( calc.findFirst( pred, 1.6, 0.5 ), 0); 
    //BOOST_CHECK_EQUAL( ret, 1 );
 
}

BOOST_AUTO_TEST_CASE( findFirst_should_2 )
{
    problem::Calculator calc;
    PredicateMock pred;
    MOCK_EXPECT( pred.pred_mock ).once().with(mock::any).returns( false );
    MOCK_EXPECT( pred.pred_mock ).once().with(mock::any).returns( false );
    MOCK_EXPECT( pred.pred_mock ).once().with(mock::any).returns( true );
    BOOST_CHECK_EQUAL( calc.findFirst( pred, 1.6, 0.5 ), 2); 
    //BOOST_CHECK_EQUAL( ret, 1 );
}

BOOST_AUTO_TEST_CASE( calcForEach_should_zero )
{
    problem::Calculator calc;
    std::vector<int> vals = boost::assign::list_of(1)(2)(3);
    BOOST_CHECK_EQUAL( vals.size(), 3 );

    MOCK_FUNCTOR( int_ftor, int( int ) );
    //MOCK_EXPECT( int_ftor ).with( mock::any ).returns( 0 );
    MOCK_EXPECT( int_ftor ).once().with( 1 ).returns( 4 );
    MOCK_EXPECT( int_ftor ).once().with( 2 ).returns( 9 );
    MOCK_EXPECT( int_ftor ).once().with( 3 ).returns( 6 );

    calc.calcForEach( int_ftor, vals );

    std::vector<int> out_ints = boost::assign::list_of(4)(9)(6);
    /*BOOST_FOREACH( int i, vals )
    {
        std::cout << i << ", " << std::endl;
    }*/
    BOOST_CHECK_EQUAL_COLLECTIONS( vals.begin(), vals.end(), out_ints.begin(), out_ints.end() );
}

MOCK_BASE_CLASS( SystemMock, problem::ISystem )
{
    MOCK_METHOD_EXT( run, 2, bool( const char*, boost::posix_time::time_duration timeout ), run );
};

BOOST_AUTO_TEST_CASE( makeTransparent_0 )
{
    problem::Calculator calc;
    SystemMock sys_mock;
    MOCK_EXPECT( sys_mock.run )
        .once()
        .with( std::string("convert input_file.png -transparent white output_file.png"), mock::any )
        .returns( true );

    calc.makeTransparent( sys_mock, "input_file.png", "output_file.png" );
}

MOCK_BASE_CLASS( ThreadPoolMock, problem::IThreadPool )
{
    MOCK_METHOD_EXT( join, 0, void(), join );
    MOCK_METHOD_EXT( addTask, 1, void( boost::function<void()> ), addTask );
};

BOOST_AUTO_TEST_CASE( runParallel_0 )
{
    problem::Calculator calc;
    ThreadPoolMock thr_mock;
    MOCK_EXPECT( thr_mock.addTask ).calls(boost::bind(boost::apply<void>(), _1));
    MOCK_EXPECT( thr_mock.join );
    calc.runParallel(thr_mock, 5, 0);
}

//BOOST_AUTO_TEST_CASE()
//{
//


BOOST_AUTO_TEST_SUITE_END();
