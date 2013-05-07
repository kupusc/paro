#ifndef __LOG_BARRIER_H__
#define __LOG_BARRIER_H__

#include <memory>
#include <algorithm>
#include <iostream>

#include <boost/thread/thread.hpp>
#include <boost/thread/condition.hpp>
#include <boost/lambda/lambda.hpp>
#include <boost/lambda/if.hpp>
#include <boost/lexical_cast.hpp>

#include "regex_logchecker.h"
#include "string_logchecker.h"
#include "console_output.h"

class LogBarrier;

typedef std::auto_ptr<LogBarrier> auto_log_barrier;

#define LOG_BARRIER(x) auto_log_barrier ( new LogBarrier( x )  )

//auto_log_barrier first = auto_log_barrier ( new LogBarrier( regex("asdasd") )  );
//auto_log_barrier first =  LOG_BARRIER( regex("asdasd")  );


class LogBarrier
{
public:
    LogBarrier(const char * log)
    {
        m_log_checker= new StringLogChecker(log);
        assert(m_log_checker);
        init();
    }

    LogBarrier(const std::string & log)
    {
        m_log_checker= new StringLogChecker(log);
        assert(m_log_checker);
        init();
    }

    LogBarrier(const StringLogChecker & log_checker)
    {
        m_log_checker= new StringLogChecker(log_checker);
        assert(m_log_checker);
        init();
    }

    LogBarrier(const RegexLogChecker & log_checker)
    {
        m_log_checker= new RegexLogChecker(log_checker);
        assert(m_log_checker);
        init();
    }

    ~LogBarrier();

    void init() ;

    template<typename lock_type>
    void halt(lock_type& lock,const std::string & log)
    {
        using boostMT::cout;
        using boostMT::endl;

        thread_info new_t_info = { boost::this_thread::get_id() , log} ;

        std::list<thread_info>::iterator it=find(m_halted_threads.begin(),m_halted_threads.end(),new_t_info);
        assert(it==m_halted_threads.end());
        m_halted_threads.push_back(new_t_info);
        {
            boost::recursive_mutex::scoped_lock lock(cout.get_mutex() );
            // cout << ">> " << new_t_info << " and was halted on log barrier set on " << /* get_print_log_match()  << */ endl;
        }
        m_condition.wait(lock);
        {
            boost::mutex::scoped_lock lck(m_awake_threads_mtx);
            ++m_awake_threads;
            m_awake_threads_cond.notify_all();
        }
    }

    bool match_log(const std::string & log)
    {
        return m_log_checker->checkLog(log);
    }

    std::string get_print_log_match() const
    {
        return m_log_checker->getExpected() ;
    }

public:
    struct thread_info
    {
        boost::thread::id id;
        std::string log;
    };

private:
    LogCheckerBase * m_log_checker;
    boost::condition m_condition;
    std::list<thread_info> m_halted_threads;

    unsigned int m_awake_threads;
    boost::mutex m_awake_threads_mtx;
    boost::condition m_awake_threads_cond;

    friend std::ostream& operator<< (std::ostream& out, const  LogBarrier & barrier );
};


inline std::ostream& operator<< (std::ostream& out, const  LogBarrier & barrier )
{
    if ( barrier.m_halted_threads.size() == 0 )
    {
        out << ">> \tlog barrier set on " <<   barrier.get_print_log_match() << " has no threads halted" << std::endl;
    }
    out << ">> \tlog barrier set on " <<   barrier.get_print_log_match() << " has " << barrier.m_halted_threads.size() << " threads halted: " << std::endl;

    using namespace boost::lambda;
    using boost::lambda::_1;

    std::ostringstream os;
    std::for_each(barrier.m_halted_threads.begin() , barrier.m_halted_threads.end() , os << constant(">> \t\t") << _1 << "\n" );
    out << os.str();

    return out;
}

inline std::ostream& operator<< (std::ostream& out, const  LogBarrier::thread_info & ti )
{
    out << "thread id: " << ti.id ; /* << ", printed log: " << "\"" << ti.log  << "\"" */ ;
    return out;
}

inline bool operator==(const LogBarrier::thread_info & ti1, const LogBarrier::thread_info & ti2)
{
    return ti1.id==ti2.id;
}

class LogBarrierManager
{
public:
    static LogBarrierManager & get_instance()
    {
        static LogBarrierManager instance;
        return instance;
    }

    void pass_barriers(const std::string & log)
    {
        boost::mutex::scoped_lock lock(m_mutex);

        std::list<LogBarrier *>::iterator it ;

        for ( it=m_log_barriers.begin() ; it!=m_log_barriers.end() ; it++)
        {
            if (  (*it)== 0 )
            {
                continue ; //skip . this barrier is already deleted
            }
            else if ( (*it)->match_log(log) == true )
            {
                //stop on this barrier
                (*it)->halt(lock,log);
            }

        }
        //all barriers passed . thread can continue
    }

    void add_barrier( LogBarrier * barrier)
    {
        boost::mutex::scoped_lock lock(m_mutex);
        m_log_barriers.push_front(barrier);
    }

    void remove_barrier( LogBarrier * barrier)
    {
        boost::mutex::scoped_lock lock(m_mutex);

        std::list<LogBarrier *>::iterator it=find(m_log_barriers.begin(),m_log_barriers.end(),barrier);
        assert(it!=m_log_barriers.end());
        // dont remove barrier from list as this will invalidate all iterators. only set it to 0.
        (*it)=0;
    }
private:
    int get_active_barriers_count()
    {
        using namespace boost::lambda;
        using boost::lambda::_1;

        int count=0;
        std::for_each(m_log_barriers.begin() , m_log_barriers.end() ,  if_then(  _1 != (void *)0 , var(count)++ )  );

        return count;
    }
public:
    void print_barriers()
    {
        using boostMT::cout;
        using boostMT::endl;

        lock(m_mutex , cout.get_mutex() ) ; // lock 2 locks
        //boost::mutex::scoped_lock lock(m_mutex);
        //boost::recursive_mutex::scoped_lock lock2(cout.get_mutex() );

        int barriers_count= get_active_barriers_count();
        if ( barriers_count != 0 )
        {
            cout << ">> " << barriers_count <<  " log barriers are active: " << endl;
        }
        else
        {
            cout << ">> NO log barriers are active" << endl;
        }

        using namespace boost::lambda;
        using boost::lambda::_1;

        std::ostringstream os;
        std::for_each(m_log_barriers.begin(), m_log_barriers.end() , if_then(  _1 != (void *)0 , os << *_1 ) ) ;
        cout << os.str();

        m_mutex.unlock();
        cout.get_mutex().unlock();
    }

private:
    std::list<LogBarrier *> m_log_barriers;
    boost::mutex m_mutex;
};

#endif //__LOG_BARRIER_H__
