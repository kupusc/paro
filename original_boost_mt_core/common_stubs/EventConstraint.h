#ifndef _EVENT_CONSTRAINT_233ED619_9906_4877_962C_6F4BCA88240D_
#define _EVENT_CONSTRAINT_233ED619_9906_4877_962C_6F4BCA88240D_

#include <boost/test/test_tools.hpp>
#include <IOxfEvent.h>
#include <eventComparator.h>
#include <original_boost_mt_core/helper/EventTraits.h>

//
// WARNING! Event constraint is deprecated use OBMC_MOCK_EXPECT_SEND from MakeEventResponse.h
//
namespace common_stubs 
{
    template <class eventType>
    struct GlobalEventConstraint
    {
        mutable eventType* _expected;
        mutable boost::test_tools::predicate_result res;

        GlobalEventConstraint(eventType& expected) : _expected(&expected), res(true){}
        friend bool operator==( IOxfEvent* actual, const GlobalEventConstraint<eventType>& c)
        { 
            if(actual->getId() != c._expected->getId())
            {
                c.res.message() << "[expected " << mock::format( static_cast<IOxfEvent*>(c._expected)) << " (id: " << c._expected->getId() << ")"
                    << " != actual: " << mock::format(actual)  << " (id: " << actual->getId() << ") ] ";
                return false;
            }
            c.res = assertEquals(c._expected, static_cast<eventType*>(actual));

            return c.res;
        }
        friend std::ostream& operator<<(std::ostream& s, const GlobalEventConstraint<eventType>& c )
        {
            return s << c.res.message().str();
        }
    };

    template <class eventType>
    GlobalEventConstraint<eventType> eventConstraint(eventType& ev)
    {
        return GlobalEventConstraint<eventType>(ev);
    }

    template <class EventType>
    struct EventTypeConstraint
    {
        friend bool operator==(const IOxfEvent* actual, const EventTypeConstraint &)
        { 
            return NULL != dynamic_cast<const EventType *>(actual);
        }

        friend std::ostream& operator<<(std::ostream& s, const EventTypeConstraint &)
        {
            return s << "Event has wrong type";
        }
    };

}

#endif //_EVENT_CONSTRAINT_233ED619_9906_4877_962C_6F4BCA88240D_

