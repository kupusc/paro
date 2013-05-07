#include "EventTraits.h"
#include <IOxfEvent.h>

namespace original_boost_mt_core
{

    namespace helpers
    {

        namespace event_traits
        {

            boost::scoped_ptr<EventParamsPrinter> EventParamsPrinter::instance;

            void EventParamsPrinter::print(mock::stream& s, const IOxfEvent* t)
            {
                std::string const typeName = typeid(*t).name();
                EventTypes::const_iterator i = eventTypes.find(typeName);
                if(eventTypes.end() != i)
                {
                    i->second->print(s, t);
                } else 
                {
                    s << "Unregistered event type (see EventTraits.h): " << typeName.c_str();
                }
            }

            EventParamsPrinter &EventParamsPrinter::getInstance()
            {
                //TODO: mutex
                if(!instance)
                {
                    instance.reset(new EventParamsPrinter);
                }
                return *instance;
            }

        }
    }
}