#ifndef OBMC_BOOST_TEST_ERROR_POLICY_HPP_INCLUDED
#define OBMC_BOOST_TEST_ERROR_POLICY_HPP_INCLUDED

#include <boost/test/framework.hpp>
#include <boost/test/test_tools.hpp>
#include <boost/test/unit_test_suite.hpp>
#include <boost/test/execution_monitor.hpp>
#include <boost/exception/enable_current_exception.hpp>

#include <boost/thread/recursive_mutex.hpp>
#include <boost/thread/thread.hpp>
#include <stdexcept>
#include <boost/test/utils/trivial_singleton.hpp>
#include <boost/test/detail/unit_test_parameters.hpp>

namespace mock
{
    struct exception : public boost::execution_aborted
    {};

    namespace detail 
    {
        struct delayed_entry
        {
            delayed_entry(const std::string &file, int line, const std::string &context):mFile(file),mLine(line),mContext(context)
            {
            }

            void print()
            {
                boost::unit_test::framework::assertion_result( true );
                boost::unit_test::unit_test_log
                    << boost::unit_test::log::begin( mFile,
                    static_cast< std::size_t >( mLine ) )
                    << boost::unit_test::log_successful_tests
                    << "(delayed print) mock expectation fulfilled: " << mContext << boost::unit_test::log::end();
            }

            std::string const mFile;
            int const mLine;
            std::string const mContext;
        };

        struct print_synchronization_t: public boost::unit_test::singleton<print_synchronization_t>
        {
            bool is_main_thread() const
            {
                return boost::this_thread::get_id() == mMainThreadId;
            }

            void add_delayed_entry(std::auto_ptr<delayed_entry> entry)
            {
                boost::mutex::scoped_lock guard(mMutex);
                mEntries.push_back(boost::shared_ptr<delayed_entry>(entry));
            }

            void print_if_main_thread()
            {
                if(is_main_thread())
                {
                    boost::mutex::scoped_lock guard(mMutex);
                    std::for_each(mEntries.begin(), mEntries.end(), boost::bind(&delayed_entry::print, _1));
                    mEntries.clear();
                }
            }

        private:
            print_synchronization_t():mMainThreadId(boost::this_thread::get_id())
            {                
            }
            
            boost::mutex mMutex;
            boost::thread::id const mMainThreadId;
            std::vector<boost::shared_ptr<delayed_entry> > mEntries;

        private:
            friend class boost::unit_test::singleton<print_synchronization_t>; 

        };

        BOOST_TEST_SINGLETON_INST(print_synchronization);
    }



    template< typename Result >
    struct obmc_boost_test_error_policy
    {
        static Result abort()
        {
            boost::unit_test::framework::test_unit_aborted(
                boost::unit_test::framework::current_test_case() );
            throw boost::enable_current_exception( exception() );
        }

        static void checkpoint( const char* file, int line )
        {
            boost::unit_test::unit_test_log.set_checkpoint( file,
                static_cast< std::size_t >( line ) );
        }

        template< typename Context >
        static void fail(
            const char* message, const Context& context,
            const char* file = "unknown location", int line = 0 )
        {
            boost::unit_test::framework::assertion_result( false );
            boost::unit_test::unit_test_log
                << boost::unit_test::log::begin( file,
                static_cast< std::size_t >( line ) )
                << boost::unit_test::log_all_errors
                << message << ": " << context
                << boost::unit_test::log::end();
        }

        template< typename Context >
        static void expected_call( const Context& context, const char* file, int line )
        {
            if(detail::print_synchronization_t::instance().is_main_thread())
            {
                boost::unit_test::framework::assertion_result( true );
                boost::unit_test::unit_test_log
                    << boost::unit_test::log::begin( file,
                    static_cast< std::size_t >( line ) )
                    << boost::unit_test::log_successful_tests
                    << "mock expectation fulfilled: " << context << boost::unit_test::log::end();
            } else if(boost::unit_test::runtime_config::log_level() <= boost::unit_test::log_successful_tests)
            {
                //note: since we are unable to use lazy stream, above we check log level to avoid unnecessary serializing
                std::stringstream ss;
                ss << context;
                std::auto_ptr<detail::delayed_entry> delayed(new detail::delayed_entry(file, line, ss.str()));
                detail::print_synchronization_t::instance().add_delayed_entry(delayed);
            }
        }

        template< typename Context >
        static void missing_action( const Context& context,
            const char* file, int line )
        {
            fail( "missing action", context, file, line );
        }
        template< typename Context >
        static void unexpected_call( const Context& context )
        {
            fail( "unexpected call", context );
        }
        template< typename Context >
        static void sequence_failed( const Context& context,
            const char* file, int line )
        {
            fail( "sequence failed", context, file, line );
        }
        template< typename Context >
        static void verification_failed( const Context& context,
            const char* file, int line )
        {
            fail( "verification failed", context, file, line );
        }
        template< typename Context >
        static void untriggered_expectation( const Context& context,
            const char* file, int line )
        {
            fail( "untriggered expectation", context, file, line );
        }

    };
}

#endif // OBMC_BOOST_TEST_ERROR_POLICY_HPP_INCLUDED
