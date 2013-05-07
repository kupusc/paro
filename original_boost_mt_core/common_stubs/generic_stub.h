#ifndef __GenericStub_H__
#define __GenericStub_H__

#include "omreactive.h"
#include "state.h"
#include "DistributedObject.h"
#include "Registry.h"
//#include <auto_ptr>

#include <string>
#include "boost/date_time/posix_time/posix_time.hpp"
#include <memory>


class IGenericStub 
{
public:
	IGenericStub(std::string name ) : m_name(name)
	{
	}
	void print_event(short id)
	{
		string print = "GENERIC_STUB: name: " + m_name + " got event id: %u";
		dbg_print(MON_SEVERITY_INFO,FEAT_DBG_Generic,print.c_str(),id);
	}
protected:
	//! Waits till value >= countMoreOrEq for waitFor time
	/*! 
	 * Todo: replece spinlock with something more appropieate here
	 * \return True on success, False on timeout
	 */	
	static bool genericWaitForReplyCount(const int &value, int countMoreOrEq, boost::posix_time::time_duration waitFor);
	
protected:
	std::string m_name;
};



class GenericStub :  public OMReactive , public IGenericStub
{

public :
	GenericStub(std::string name, OMThread* p_thread = OMDefaultThread);
    virtual OMBoolean startBehavior();
public :
	virtual int takeEvent(short id);
	IOxfReactive::TakeEventStatus takeEvent(OMEvent* ev);
};

//! Like GenericStub, but with functionality to return last received event
/*! Usage:
 *    GenericStubWithLastEvent gswle("dupa");
 *    ...
 *    GenericStubWithLastEvent::EventsMarker beforeSomeActions = gswle.getEventsMarker();
 *    someClass->GEN(evSomeEvent(&gswle, ..));
 *    BOOST_REQUIRE(gswle.waitForEventsReceived(beforeSomeActions+1)); //if returns false - timeout
 *    BOOST_CHECK(gswle.getLastEvent<evSomeEvent>().value == 69);
 *
 * by Stoper
 */ 
class GenericStubWithLastEvent: public GenericStub
{
public:
	typedef int EventsMarker;

public:
	GenericStubWithLastEvent(std::string name, OMThread* p_thread = OMDefaultThread);
	virtual ~GenericStubWithLastEvent() {}

	//! Returns reference to last received event
	/*! \warning There is an assertion that instance dynamically casts to T
	 */
	template<class T>
	T &getLastEvent();

	//! Used for marking "how many events were received at that point"
	EventsMarker getEventsMarker() const { return eventsReceived; }

	//! Will wait till received events number receives target value
	/*! \note Timeout value can be given, default 5 seconds
	 *  \return True if target was reached, False when timeout occured
	 */
	bool waitForEventsReceived(EventsMarker targetEvents, boost::posix_time::time_duration waitFor = boost::posix_time::milliseconds(5000)) const;

private:
	IOxfReactive::TakeEventStatus takeEvent(OMEvent* ev);

protected:
	EventsMarker eventsReceived;
	std::auto_ptr<OMEvent> lastEvent;
};

template<class T>
T &GenericStubWithLastEvent::getLastEvent() 
{
	typedef T* TPtr;
    assert(NULL != lastEvent.get());
	assert(NULL != dynamic_cast<TPtr>(lastEvent.get()));
	return *dynamic_cast<TPtr>(lastEvent.get());
}


class GenericDistributedStub :  public DistributedObject , public IGenericStub
{
public :
	GenericDistributedStub(std::string name,int AppId, OMThread* p_thread = OMDefaultThread);
	~GenericDistributedStub();
    virtual OMBoolean startBehavior();
public :
	virtual int takeEvent(short id);
	IOxfReactive::TakeEventStatus takeEvent(OMEvent* ev);	
};






#endif //__GenericStub_H__
