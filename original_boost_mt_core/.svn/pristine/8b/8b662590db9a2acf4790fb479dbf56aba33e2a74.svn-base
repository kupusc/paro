
#include <list>

using namespace std;

#include "generic_stub.h"
#include "omreactive.h"
#include "boost/thread.hpp"
#include "oam_assert.h"
#include "dbg_prints.h"

// -- IGenericStub ---

bool IGenericStub::genericWaitForReplyCount(const int &value, int countMoreOrEq, 
	  boost::posix_time::time_duration waitFor) 
{
	//spinlock, should be replaced by semaphore of some kind since it can take a while	
	boost::posix_time::ptime failAt = boost::posix_time::microsec_clock::local_time() + waitFor;
	while(value < countMoreOrEq) 
	{
		if(boost::posix_time::microsec_clock::local_time() >= failAt)
			return false;
		boost::thread::yield();
	}
	return true;	
}

// -- GenericStub ---

GenericStub::GenericStub(string name, OMThread* p_thread ) :IGenericStub(name)
{
	setThread(p_thread, FALSE);
    startBehavior();
}

OMBoolean GenericStub::startBehavior()
{
    OMBoolean done = FALSE;
    done = OMReactive::startBehavior();
    return done;
}

int GenericStub::takeEvent(short id) 
{
	print_event(id);
	return eventConsumed;
}

IOxfReactive::TakeEventStatus GenericStub::takeEvent(OMEvent* ev)
{
	setCurrentEvent(ev);
	takeEvent(ev->getId());
	setCurrentEvent(0);
	return eventConsumed;
}

// -- GenericStubWithLastEvent ---

GenericStubWithLastEvent::GenericStubWithLastEvent(string name, OMThread* p_thread ):GenericStub(name, p_thread),eventsReceived(0)
{
	setThread(p_thread, FALSE);
    startBehavior();
}

bool GenericStubWithLastEvent::waitForEventsReceived(EventsMarker targetEvents, 
	boost::posix_time::time_duration waitFor) const
{
	//spinlock, should be replaced by semaphore of some kind since it can take a while	
	boost::posix_time::ptime failAt = boost::posix_time::microsec_clock::local_time() + waitFor;
	while(eventsReceived < targetEvents) 
	{
		if(boost::posix_time::microsec_clock::local_time() >= failAt)
			return false;
		boost::thread::yield();
	}
	return true;
}

IOxfReactive::TakeEventStatus GenericStubWithLastEvent::takeEvent(OMEvent* ev)
{
	setCurrentEvent(ev);
	//takeEvent(ev->getId());
	ev->setDeleteAfterConsume(false);
	lastEvent = auto_ptr<OMEvent>(ev);
	eventsReceived++;
	setCurrentEvent(0);
	return eventConsumed;
}


// -- GenericDistributedStub ---

GenericDistributedStub::GenericDistributedStub(string name,int AppId, OMThread* p_thread ) : 
																DistributedObject(AppId,p_thread),IGenericStub(name)
{
	if(!registry->registerObject(this))
	{
		dbg_prints::instance()->addPrint("error in GenericDistributedStub::GenericDistributedStub(" 
			"registry->registerObject(this) returned NULL");
	}
	startBehavior();
}

GenericDistributedStub::~GenericDistributedStub()
{
	registry->unregisterObject(this);
}

OMBoolean GenericDistributedStub::startBehavior()
{
    OMBoolean done = FALSE;
    done = DistributedObject::startBehavior();
    return done ;
}
int GenericDistributedStub::takeEvent(short id) 
{
	print_event(id);
	return eventConsumed;
}

IOxfReactive::TakeEventStatus GenericDistributedStub::takeEvent(OMEvent* ev)
{
	setCurrentEvent(ev);
	takeEvent(ev->getId());
	setCurrentEvent(0);
	return eventConsumed;
}



