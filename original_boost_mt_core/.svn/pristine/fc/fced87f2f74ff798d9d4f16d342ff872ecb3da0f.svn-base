#include "console_output.h"

#include "MessageQueue.h"

namespace boostMT
{
    // ------------------------ thread_safe_compiler_log_formatter --------------------------------

    thread_safe_compiler_log_formatter::thread_safe_compiler_log_formatter() : m_mutex(boostMT::ConsoleOutput::get_instance().get_mutex())
    {
    }

    thread_safe_compiler_log_formatter & thread_safe_compiler_log_formatter::get_instance()
    {
        static thread_safe_compiler_log_formatter instance;
        return instance;
    }

    void thread_safe_compiler_log_formatter::log_entry_start( std::ostream& os, boost::unit_test::log_entry_data const& data, log_entry_types let )
    {
        m_mutex.lock();
        T::log_entry_start( m_logEntryS , data, let );  // append this log entry to error string
        T::log_entry_start( os , data, let );
    }

    void thread_safe_compiler_log_formatter::log_entry_value( std::ostream& os , boost::unit_test::const_string value )
    {
        T::log_entry_value( m_logEntryS , value );      // append this log entry to error string
        T::log_entry_value( os , value );
    }

    void thread_safe_compiler_log_formatter::log_entry_value( std::ostream& os , boost::unit_test::lazy_ostream const& value )
    {
        T::log_entry_value( m_logEntryS , value );      // append this log entry to error string
        T::log_entry_value( os , value );
    }

    void thread_safe_compiler_log_formatter::log_entry_finish( std::ostream& os )
    {
        T::log_entry_finish( os );
        GlobalMessage::getSingleton().errorString = m_logEntryS.str(); // store error string in GlobalMessage
        m_mutex.unlock();
    }

}
