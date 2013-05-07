
#ifndef _CCS_SIC_STUB_H_
#define _CCS_SIC_STUB_H_

#include <string>
#include <vector>
#include <list>

#include <boost/thread/thread.hpp>
#include <boost/thread/condition.hpp>

#include "ccs_default_impl.h"



namespace stub
{

class CcsSicStubListener;

class CcsSicStub : public CcsStubImplDefault
{
public:
	typedef unsigned char byte;

private:	
	template <typename R>
	R extract(const void * source, unsigned first_byte_pos = 0) ;
	
	void *AaSysComMsgCreate(const TAaSysComMsgId messageId,const TAaSysComMsgSize messagePayloadSize,const TAaSysComSicad messageTarget)  ;

	void *AaSysComMsgGetPayload(const void *message);

	TAaSysComMsgSize AaSysComMsgGetPayloadSize(const void *message);
	
	void AaSysComMsgSetSender(const void *message,const TAaSysComSicad messageSource);

	TAaSysComSicad AaSysComMsgGetSender(const void *message);
	
	TAaSysComSicad AaSysComMsgGetReceiver(const void *message);

	TBoard AaSysComNmapGetBoard(TAaSysComSicad sicAddress);

	TCpu AaSysComNmapGetCpu(TAaSysComSicad sicAddress);

	TTask AaSysComNmapGetTask(TAaSysComSicad sicAddress);
	
	TAaSysComMsgId AaSysComMsgGetId(const void *message);

	void AaSysComMsgSend(void **message);

	TAaSysComSicad AaSysComNmapGetSicAddress(const TBoard board, 
                                         const TCpu cpu, 
                                         const TTask task);
									 
										 
	void notify(TAaSysComMsgId id 	
								,TAaSysComSicad receiver
								,TAaSysComSicad sender
								,const std::vector<CcsSicStub::byte> & payload );										 
										 
public:

		// user interface
		static std::vector<byte>  make_message(TAaSysComMsgId id
																		,TAaSysComSicad receiver
																		,TAaSysComSicad sender
																		,const  std::vector<byte> & payload
																		);
																		
		static void send_message(const std::vector<byte> & msg);
		
		void add_listener(  CcsSicStubListener &);
		void remove_listener( CcsSicStubListener &);

private:
		std::list<CcsSicStubListener *> m_listeners;
		boost::mutex m_mutex;
};



class CcsSicStubListener
{
public:
virtual void onMessage(TAaSysComMsgId id 
								,TAaSysComSicad receiver
								,TAaSysComSicad sender
								,const std::vector<CcsSicStub::byte> & payload) = 0;

};


}

#endif //_CCS_SIC_STUB_H_