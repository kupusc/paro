#include <iostream>
#include <unistd.h>

#define BOOST_AUTO_TEST_MAIN
#define BOOST_TEST_MODULE calculator_tests
#define BOOST_TEST_DYN_LINK

#include <boost/test/auto_unit_test.hpp>
#include <turtle/mock.hpp>

#include <calculator.hpp>
#include <boost/scoped_ptr.hpp>

using namespace std;
using problem::IPredicate;
using problem::CustomStruct;


namespace
{
    struct Fixture
      {
	typedef problem::Calculator uut_t;
	boost::scoped_ptr<uut_t> uut;
        Fixture()
        {
            problem::initBugs();
	    uut.reset(new uut_t());
        }
        
    };

}


BOOST_FIXTURE_TEST_SUITE(example, Fixture);

MOCK_BASE_CLASS(IPredicateMock, IPredicate)
{
  MOCK_METHOD_EXT(operator(), 1, bool(float), pred_mock)
};

BOOST_AUTO_TEST_CASE( calculator_must_return_correct_value_that_fulfills_predicate_for_the_first_iteration )
{
  IPredicateMock IPMock;
  MOCK_EXPECT(IPMock.pred_mock).once().returns(true);
  BOOST_CHECK_EQUAL(0, uut->findFirst(IPMock, 0, 1));
}

BOOST_AUTO_TEST_CASE(calculator_must_return_correct_value_for_the_next_iteratins  )
{
  IPredicateMock IPMock;
  mock::sequence s;
  MOCK_EXPECT(IPMock.pred_mock).at_most(100).in(s).returns(false);
  MOCK_EXPECT(IPMock.pred_mock).once().in(s).returns(true);
  BOOST_CHECK_EQUAL(100, uut->findFirst(IPMock, -2, 1));
}

MOCK_FUNCTION(convert_mock,1,int(int),convert_mock)


BOOST_AUTO_TEST_CASE(calculator_must_not_convert_empty_data_set )
{
  
  std::vector<int> data_set;
  MOCK_EXPECT(convert_mock).never();
  uut->calcForEach(convert_mock,data_set);
}


BOOST_AUTO_TEST_CASE( calculator_must_convert_data_set )
{
  
  
  std::vector<int> data_set;
  data_set.push_back(1);
  MOCK_EXPECT(convert_mock).once().with(1).returns(2);
  uut->calcForEach(convert_mock,data_set);
  BOOST_CHECK_EQUAL(data_set[0],2);
}

MOCK_BASE_CLASS(ISystemMock, problem::ISystem)
{
  MOCK_METHOD_EXT(run, 2, bool(const char*, boost::posix_time::time_duration), run)  
};

BOOST_AUTO_TEST_CASE( calculator_must_make_transparent_image )
{
  ISystemMock ISMock;
  std::string expected_command("convert inputPath -transparent white outputPath");
  MOCK_EXPECT(ISMock.run).once().with(expected_command, mock::any).returns(true);
  //, 215:06:34.430000 )

  uut->makeTransparent(ISMock, "inputPath", "outputPath");
}

BOOST_AUTO_TEST_CASE( calculator_must_throw_exception_when_ISystem_fails )
{
  ISystemMock ISMock;
  std::string expected_command("convert inputPath -transparent white outputPath");
  MOCK_EXPECT(ISMock.run).once().with(expected_command, mock::any).returns(false);

  BOOST_CHECK_THROW(uut->makeTransparent(ISMock, "inputPath", "outputPath"), std::runtime_error);
}


MOCK_BASE_CLASS(IThreadPoolMock, problem::IThreadPool)
{
  typedef void result_type;
   MOCK_METHOD_EXT(addTask, 1, void(boost::function<void()>), addTask)
   MOCK_METHOD_EXT(join, 0, void(), join)
};

BOOST_AUTO_TEST_CASE( calculator_must_run_single_job )
{
  IThreadPoolMock ITPMock;
  MOCK_EXPECT(ITPMock.addTask).once();
  MOCK_EXPECT(ITPMock.join).once();
  uut->runParallel(ITPMock, 1,1);
}

BOOST_AUTO_TEST_CASE( calculator_must_run_parallel_jobs )
{
  IThreadPoolMock ITPMock;
  MOCK_EXPECT(ITPMock.addTask).exactly(2);
  MOCK_EXPECT(ITPMock.join).once();
  uut->runParallel(ITPMock, 2,1);
}

BOOST_AUTO_TEST_CASE( calculator_must_not_run_negative_number_of_jobs )
{
  IThreadPoolMock ITPMock;
  MOCK_EXPECT(ITPMock.addTask).never();
  MOCK_EXPECT(ITPMock.join).never();
  BOOST_CHECK_THROW(uut->runParallel(ITPMock, -1,1), std::exception);
  
}

MOCK_BASE_CLASS(ICustomStructReceiverMock, problem::ICustomStructReceiver)
{
    MOCK_METHOD_EXT(take, 1, void(const problem::CustomStruct&), take )
  
};

BOOST_AUTO_TEST_CASE( calculator_must_send_custom_struct )
{
  ICustomStructReceiverMock ICSRMock;
  const std::string expectedString("expectedString"); 
  float expectedFloat=1.0; 
  std::map<int, bool> expectedMap;
  expectedMap[1]=true;
  
  const std::string actualString; 
  float actualFloat; 
  const std::map<int, bool> actualMap;
 
  CustomStruct actualStruct(actualString, actualFloat, actualMap);
  MOCK_EXPECT(ICSRMock.take).once().with(mock::retrieve(actualStruct));
  uut->sendCustomStruct(ICSRMock,expectedString, expectedFloat, expectedMap);
  BOOST_CHECK_EQUAL(actualStruct.mFloat, expectedFloat);
  BOOST_CHECK_EQUAL(actualStruct.mString, expectedString);
  BOOST_CHECK_EQUAL(actualStruct.mMap[1], expectedMap[1]);
  
}


BOOST_AUTO_TEST_SUITE_END();
