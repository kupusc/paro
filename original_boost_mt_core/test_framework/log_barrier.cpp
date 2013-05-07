#include <sstream>
#include <iostream>
#include <boost/lambda/lambda.hpp>
#include "log_barrier.h"
#include "console_output.h"

LogBarrier::~LogBarrier()
{
    using namespace boost::lambda;
    using boostMT::cout;
    using boostMT::endl;
    LogBarrierManager & manager = LogBarrierManager::get_instance();
    manager.remove_barrier(this);

    std::ostringstream os;
    for_each(m_halted_threads.begin(),m_halted_threads.end() , os <<  constant(">> \t\t") << boost::lambda::_1 << "\n" );

    {
        boost::recursive_mutex::scoped_lock lock(cout.get_mutex() );
        // cout << ">> log barrier removed on " << get_print_log_match() << endl;
        cout << ">> \t" << m_halted_threads.size() << " threads resumed: " << endl;
        cout << os.str();
    }

    // manager.print_barriers();
    m_condition.notify_all();
    // wait for all the halted threads to wake up. destroying a condition
    // variable while there are still threads waiting on it is a Bad Thing
    // and causes a crash when using the pthreads implementation on Linux.
    {
        boost::mutex::scoped_lock lck(m_awake_threads_mtx);
        while(m_awake_threads < m_halted_threads.size())
        {
            m_awake_threads_cond.wait(lck);
        }
    }

    delete m_log_checker;
}

void LogBarrier::init()
{
    using boostMT::cout;
    using boostMT::endl;
    
    m_awake_threads = 0;

    LogBarrierManager & manager = LogBarrierManager::get_instance();
    manager.add_barrier(this);

    boost::recursive_mutex::scoped_lock lock(cout.get_mutex() );
    cout << ">> log barrier set on " << get_print_log_match() << endl;

}
