
#ifndef __SUBCASE_H__
#define __SUBCASE_H__

#include <string>
#include <cassert>

#define BOOST_RUN_SUBCASE(x) SubCase::run_subcase(x##_invoker, #x)  


class SubCase
{
private:
	class runner
	{
	public:
		runner(std::string name)
		{
			pre_subcase_run(name);
		}
		~runner()
		{
			post_subcase_run();
		}
	};


	SubCase();
	~SubCase();
public:
	static inline std::string get_name()
	{
		assert(is_running()==true);
		return m_name;
	}
	static inline bool is_running()
	{
		return m_running_subcase;
	}
	static void run_subcase( void (*f)() , std::string name );
	static void save_name(std::string name)
	{
		m_name=name;
	}
	static void pre_subcase_run(std::string name);
	static void post_subcase_run();


	template <typename R >
	static R run_boost_mt_subcase(std::string name,R (*func)( ) )
	{
		runner run(name);	
		return (*func)(); // this works with func that return void . BUG or FEATURE ??
	}	
	template <typename R, typename T1 >
	static R run_boost_mt_subcase(std::string name,R (*func)( T1) , T1 param1)
	{
		runner run(name);	
		return (*func)(param1);
	}	
	template <typename R, typename T1,typename T2 >
	static R run_boost_mt_subcase(std::string name,R (*func)( T1, T2) , T1 param1, T2 param2)
	{
		runner run(name);	
		return (*func)(param1,param2);
	}	
	template <typename R, typename T1,typename T2,typename T3  >
	static R run_boost_mt_subcase(std::string name,R (*func)( T1, T2, T3) , T1 param1, T2 param2, T3 param3)
	{
		runner run(name);	
		return (*func)(param1,param2,param3);
	}	
	// if needed add more templates functions with more parameters as above
	// beware of BOOST_MT_SUBCASE declaration with references as they might couse ambigous template parameter deduction
	
	
	
private:
	static bool m_running_subcase;
	static std::string m_name;
};


#define BOOST_MT_SUBCASE(name,...) name##_boost_mt_subcase(__VA_ARGS__)
#define BOOST_MT_RUN_SUBCASE(name,...) SubCase::run_boost_mt_subcase(#name,name##_boost_mt_subcase,__VA_ARGS__)



#endif //__SUBCASE_H__