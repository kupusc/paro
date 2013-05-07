
#include "print_writer.h"
#include <iostream>
#include "console_output.h"
#include "MessageQueue.h"
#include <stdexcept>

using namespace std;

Print_writer::Print_writer()
{
	m_printTopOnly = false;
}

Print_writer::~Print_writer()
{	
	boost::mutex::scoped_lock lock(m_mutex);
}

Print_writer * Print_writer::get_instance()
{
	static Print_writer m_instance;
	return &m_instance;
}

bool Print_writer::open_file(const boost::filesystem::path &file_name)
{
	boost::mutex::scoped_lock lock(m_mutex);
	
    ofstream* test_case = new ofstream;
	test_case->open(file_name.c_str());
	if(test_case->fail())
    {
        std::string error = "Print_writer::open_file: Could not open log file: "; 
        error += file_name.string();
        std::cout << error;
        throw std::runtime_error(error.c_str());
    }
	m_test_cases.push_back(test_case);

	*test_case << m_buffer.str() ;
	
	using boostMT::cout;
	using boostMT::endl;

    boost::recursive_mutex::scoped_lock lock2(cout.get_mutex() );        
	cout << ">> writing test case output to file (stack size: " << m_test_cases.size() << "): " << file_name <<endl; 
	return true;
}

void Print_writer::close_file()
{
	boost::mutex::scoped_lock lock(m_mutex);

	assert(m_test_cases.size() >0);
	//pff nie wazne,       //stoper: nie tu chcialem cos poprawic, ale "owhileowalem" to przez przypadek, i chyba tak jest lepiej
	//while(!m_test_cases.empty()) {
		m_test_cases.back()->close();
		delete m_test_cases.back();
		m_test_cases.pop_back();
	//}
	if (m_test_cases.size()>0)
	{
		//add file name here
		//cout << ">> writing test case output to file (stack size: " << m_test_cases.size() << "): " << file <<endl; 		
	}

	//cout << ">> Print_writer::close_file" << endl; 
	
}

