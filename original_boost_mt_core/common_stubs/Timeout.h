
#ifndef __TIMEOUT_H__
#define __TIMEOUT_H__

#include "omreactive.h"

namespace oxf_timeout_stub
{
	void generate(OMReactive *instance,short id );

}

#define GEN_TIMEOUT(object,class_name,state_name) oxf_timeout_stub::generate(object,class_name##_Timeout_##state_name##_id)

// feature not supported anymore
#define TIMEOUT_REQUEST(...) "timeout request is not suppoerted anymore" 

#endif //__TIMEOUT_H__