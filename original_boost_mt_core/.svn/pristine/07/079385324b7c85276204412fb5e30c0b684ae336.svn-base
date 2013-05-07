#ifndef __PRINT_WRITER_H__
#define __PRINT_WRITER_H__

#include <stack>
#include <fstream>
#include <string>
#include <list>
#include <boost/thread/mutex.hpp>
#include <boost/filesystem.hpp>

using std::ofstream;
using std::string;
using std::list;

class Print_writer
{
private:
	Print_writer();
	~Print_writer();

public:
	static Print_writer * get_instance();
	template <typename T>
	void write(T something, bool follow_endline=true);
    
    /** @brief Opens log file for writing
    *
    * @param file_name Absolute path to log file
    */
	bool open_file(const boost::filesystem::path &file_name);
	void close_file();
	void flush_log();
	
private:
	list<ofstream *> m_test_cases; //stack is for nested test case calls
	//ofstream m_log0;
	//ofstream m_log1;
	friend struct Print_writer_fixture;
	bool m_printTopOnly;
	boost::mutex m_mutex;
	std::ostringstream m_buffer;
};

template <typename T>
void Print_writer::write(T something, bool follow_endline)
{
	boost::mutex::scoped_lock lock(m_mutex);
	if (m_test_cases.size() !=0 )
	{
		if (m_printTopOnly)
		{
			*m_test_cases.back() << something << (follow_endline ? "\n" : "");
		}
		else
		{
			for (list<ofstream*>::const_iterator it = m_test_cases.begin(); it!=m_test_cases.end(); ++it)
			{
				(**it) << something << (follow_endline ? "\n" : "");
				(**it).flush();
			}
		}
	}
	else
	{
		m_buffer << something << (follow_endline ? "\n" : "") ;
 	}

}

struct AutoPrintWriterFixture 
{
//THIS FEATURE IS NO LONGER IN USE
	AutoPrintWriterFixture() 
	{
		
	}
};


#endif
