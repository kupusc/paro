#ifndef __CONSOLE_OUTPUT_H_
#define __CONSOLE_OUTPUT_H_

#include <iostream>
#include <string>
#include <sstream>
#include <fstream>

#include <boost/thread/thread.hpp>
#include <boost/thread/recursive_mutex.hpp>
#include <boost/test/unit_test_log.hpp>
#include <boost/test/detail/unit_test_parameters.hpp>
#include <boost/test/output/compiler_log_formatter.hpp>


namespace boostMT
{

    class ConsoleOutput : public std::ostream
    {
    public:
        ConsoleOutput(): std::ostream(std::cout.rdbuf())
        {
        }

        static ConsoleOutput & get_instance()
        {
            static ConsoleOutput instance;
            return instance;
        }

        boost::recursive_mutex  & get_mutex()
        {
            return m_mutex;
        }

        // write .err file
        void writeErrorFile(const std::string& filename, const std::string& errorString)
        {
            if (errorString.length() > 0)
            {
                std::ofstream errorFile;
                errorFile.open(filename.c_str());
                if (!errorFile.fail())
                {
                    errorFile << errorString << std::endl;
                    errorFile.close();
                }
            }
        }


    private:
        ConsoleOutput(const ConsoleOutput & c);

    private:
        boost::recursive_mutex m_mutex;   // might be locked many times by the same thread
        std::ofstream m_outFile;          // output file stream
    };

    const char * const endl = "\n" ;
    static ConsoleOutput & cout= ConsoleOutput::get_instance() ;


    class thread_safe_compiler_log_formatter : public boost::unit_test::output::compiler_log_formatter
    {
        typedef boost::unit_test::output::compiler_log_formatter T;
    private:
        thread_safe_compiler_log_formatter();

    public:	
        static thread_safe_compiler_log_formatter & get_instance();

        void log_entry_start( std::ostream& os, boost::unit_test::log_entry_data const& data, log_entry_types let );

        void log_entry_value( std::ostream& os , boost::unit_test::const_string value );

        void log_entry_value( std::ostream& os , boost::unit_test::lazy_ostream const& value );

        void log_entry_finish( std::ostream& os );

    private: 
        thread_safe_compiler_log_formatter( const thread_safe_compiler_log_formatter &);	
        thread_safe_compiler_log_formatter & operator=(const thread_safe_compiler_log_formatter &);	
    private:
        boost::recursive_mutex & m_mutex;   // might be locked many time by the same thread
        std::ostringstream m_logEntryS;     // for storage of the whole log entry

    };


}

#endif //__CONSOLE_OUTPUT_H_
