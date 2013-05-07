//#include "test_framework.h"

#ifndef _MESSAGE_FORMAT_H__
#define _MESSAGE_FORMAT_H__

#include <string>
#include <vector>
#include <cassert>

class SysComMsgFormat
{
public:

	static std::string formatMsg(const std::vector<unsigned char> & vec) ;

	static std::vector<unsigned char> formatMsg(const std::string & s);

	template <typename T> 
	static std::vector<unsigned char> convert(T item)	
	{
		unsigned char * item_p = reinterpret_cast<unsigned char *>(&item);
		std::vector<unsigned char> item_vec (item_p,item_p+sizeof(T));
		return item_vec;
	}

	template <typename T> 
	static T convert(const std::vector<unsigned char> & item)	
	{
			assert( sizeof(T) == item.size() );

			T ret;
			unsigned char * ret_p = reinterpret_cast<unsigned char *>(&ret);
			std::copy( item.begin(), item.end() , ret_p);
			return ret;		
	}
	
	
};


#endif //_MESSAGE_FORMAT_H__
