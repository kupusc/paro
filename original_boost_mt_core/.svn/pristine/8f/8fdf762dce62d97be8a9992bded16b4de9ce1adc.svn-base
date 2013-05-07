
#include "SubCase.h"
#include <iostream>
#include "console_output.h"

using namespace std;

bool SubCase::m_running_subcase=false;
string SubCase::m_name;

void SubCase::run_subcase( void (*f)() , string name )
{
	m_name=name;
	m_running_subcase=true;
        using boostMT::cout;
        using boostMT::endl;

        {
                boost::recursive_mutex::scoped_lock lock(cout.get_mutex() );        
                cout << "Entering subcase: " << name << endl;
        }
        (*f)();
	{
                boost::recursive_mutex::scoped_lock lock(cout.get_mutex() );
                cout << "Leaving subcase:  " << name << endl;	
        }
        m_running_subcase=false;
}


 void SubCase::pre_subcase_run(std::string name)
{
	save_name(name);
	m_running_subcase=true;
        using boostMT::cout;
        using boostMT::endl;

        boost::recursive_mutex::scoped_lock lock(cout.get_mutex() );        
	cout << "Entering subcase: " << m_name << endl;	
}
 void SubCase::post_subcase_run()
{
        using boostMT::cout;
        using boostMT::endl;

        boost::recursive_mutex::scoped_lock lock(cout.get_mutex() );
	cout << "Leaving subcase: " << m_name << endl;	
	m_running_subcase=false;
}