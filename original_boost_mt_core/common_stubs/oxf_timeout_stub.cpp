
#include "Timeout.h"
#include "OMTimeout.h"

namespace oxf_timeout_stub
{
	void generate(OMReactive *instance,short id )
	{
		OMTimeout* timeout = new OMTimeout(); // TODO: does it leak ??
		timeout->setTimeoutId(id);
		instance->gen(timeout);
	}

}








