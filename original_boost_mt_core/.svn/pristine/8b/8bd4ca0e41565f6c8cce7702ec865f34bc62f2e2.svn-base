#ifndef _DISTRIBUTED_OBJECT_MOCK_36E5E6DF_AF54_4D5F_B194_0E2F55EC4BBF_
#define _DISTRIBUTED_OBJECT_MOCK_36E5E6DF_AF54_4D5F_B194_0E2F55EC4BBF_

#include <turtle/mock.hpp>
#include "DistributedObject.h"

namespace common_stubs
{
    MOCK_BASE_CLASS(DistributedObjectMock, DistributedObject)
    {
        MOCK_METHOD_EXT( send, 2, bool(IOxfEvent* , const IOxfEventGenerationParams& ), send )

        bool startBehavior(void)
        { 
            //do nothing
            return true;
        }
    };

}

#endif //_DISTRIBUTED_OBJECT_MOCK_36E5E6DF_AF54_4D5F_B194_0E2F55EC4BBF_

