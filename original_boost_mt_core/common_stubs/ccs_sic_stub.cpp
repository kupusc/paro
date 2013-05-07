
#include "ccs_sic_stub.h"
#include "message_format.h"

#include <cassert>
#include <boost/bind.hpp>

#include "CNmapRouter.h"



using namespace std;

namespace stub
{

	
template <typename R>
R CcsSicStub::extract(const void * source, unsigned first_byte_pos )
{
		R res;
		unsigned char* addr_p  = (unsigned char*) source;
		memcpy(&res,addr_p + first_byte_pos , sizeof(R));
		return res;
}

TAaSysComSicad CcsSicStub::AaSysComNmapGetSicAddress(const TBoard board, 
									 const TCpu cpu, 
									 const TTask task)
{
	TAaSysComSicad ret=0;
	ret |= task << ( 8*sizeof(TBoard) + 8*sizeof(TCpu) );
	ret |= cpu << ( 8*sizeof(TBoard));
	ret |= board ;
	return ret;
}	

void *CcsSicStub::AaSysComMsgCreate(const TAaSysComMsgId messageId,const TAaSysComMsgSize messagePayloadSize,const TAaSysComSicad messageTarget)  
{
	// [id , reciver , sender ,payload size,  payload]
	//  [ board, cpu ,task ]
	unsigned char * msg = new unsigned char[sizeof(TAaSysComMsgId) + 2*sizeof(TAaSysComSicad)+sizeof(TAaSysComMsgSize) + messagePayloadSize];
	assert(msg);
	memcpy(msg,&messageId,sizeof(TAaSysComMsgId));
	memcpy(msg+ sizeof(TAaSysComMsgId),&messageTarget,sizeof(messageTarget));
	memcpy(msg+ sizeof(TAaSysComMsgId)+2*sizeof(TAaSysComSicad) , &messagePayloadSize , sizeof(TAaSysComMsgSize));
	return msg;
}
void *CcsSicStub::AaSysComMsgGetPayload(const void *message)
{
	const unsigned char * payload = reinterpret_cast<const unsigned char *>(message)+sizeof(TAaSysComMsgId)+2*sizeof(TAaSysComSicad)+sizeof(TAaSysComMsgSize);
	return const_cast<unsigned char *>(payload); 
}
TAaSysComMsgSize CcsSicStub::AaSysComMsgGetPayloadSize(const void *message)
{
	assert(message);	
	return extract<TAaSysComMsgSize>(message,sizeof(TAaSysComMsgId)+2*sizeof(TAaSysComSicad));
}
void CcsSicStub::AaSysComMsgSetSender(const void *message,const TAaSysComSicad messageSource)
{
	assert(message);
	unsigned char * msg = (unsigned char *)message;
	memcpy(msg+sizeof(TAaSysComMsgId)+sizeof(TAaSysComSicad), &messageSource,sizeof(TAaSysComSicad));
}
TAaSysComSicad CcsSicStub::AaSysComMsgGetReceiver(const void *message)
{
	assert(message);
	return extract<TAaSysComSicad>(message,sizeof(TAaSysComMsgId) );
}
TAaSysComSicad CcsSicStub::AaSysComMsgGetSender(const void *message)
{
	assert(message);
	return extract<TAaSysComSicad>(message,sizeof(TAaSysComMsgId) +sizeof(TAaSysComSicad));
}
TBoard CcsSicStub::AaSysComNmapGetBoard(TAaSysComSicad sicAddress)
{
	return extract<TBoard>(&sicAddress);
}
TCpu CcsSicStub::AaSysComNmapGetCpu(TAaSysComSicad sicAddress)
{
	return extract<TCpu>(&sicAddress,sizeof(TBoard));	
}
TTask CcsSicStub::AaSysComNmapGetTask(TAaSysComSicad sicAddress)
{
	return extract<TTask>(&sicAddress,sizeof(TBoard) + sizeof(TCpu));	
}
TAaSysComMsgId CcsSicStub::AaSysComMsgGetId(const void *message)
{
	assert(message);	
	return extract<TAaSysComMsgId>(message);
}


void CcsSicStub::AaSysComMsgSend(void **message)
{
	TAaSysComMsgSize payload_size = AaSysComMsgGetPayloadSize(*message);
	TAaSysComMsgId id = AaSysComMsgGetId(*message);
	TAaSysComSicad sender = AaSysComMsgGetSender(*message);
	TAaSysComSicad receiver = AaSysComMsgGetReceiver(*message);
	byte * payload = reinterpret_cast<byte*> ( AaSysComMsgGetPayload(*message) );
	
	
	std::vector<byte> payload_vec( payload, payload + payload_size);

	notify(id,receiver,sender,payload_vec);

}


std::vector<CcsSicStub::byte> CcsSicStub::make_message(TAaSysComMsgId id
																,TAaSysComSicad receiver
																,TAaSysComSicad sender
																,const  std::vector<CcsSicStub::byte> & payload
																)
{
	typedef CcsSicStub::byte byte;
	
	vector<byte> msg_id_vec = SysComMsgFormat::convert<TAaSysComMsgId>(id);
	vector<byte> sender_vec = SysComMsgFormat::convert<TAaSysComSicad>(sender) ;
	vector<byte> receiver_vec = SysComMsgFormat::convert<TAaSysComSicad>(receiver) ; 		
	vector<byte> payload_size_vec = SysComMsgFormat::convert<TAaSysComMsgSize>(payload.size());

	vector<byte> msg_vec;
	msg_vec.insert(msg_vec.end(),msg_id_vec.begin(),msg_id_vec.end());
	msg_vec.insert(msg_vec.end(),receiver_vec.begin(),receiver_vec.end());
	msg_vec.insert(msg_vec.end(),sender_vec.begin(),sender_vec.end());
	msg_vec.insert(msg_vec.end(),payload_size_vec.begin(),payload_size_vec.end());
	msg_vec.insert(msg_vec.end(),payload.begin(),payload.end());	

	return msg_vec;
}																


void CcsSicStub::send_message(const std::vector<byte> & msg_vec)
{
	unsigned char * msg_p = new unsigned char [msg_vec.size()]; //does it leak?
	assert(msg_p);
			
	copy(msg_vec.begin(),msg_vec.end(),msg_p);
	
	APW_pkg::CNmapRouter::onSctMwCallBack(APW_pkg::CNmapRouter::instance(),msg_p,0,0);	

}
		
		
void CcsSicStub::add_listener( CcsSicStubListener & listener)
{
		boost::mutex::scoped_lock lock(m_mutex);
		m_listeners.push_back(&listener);
}


void CcsSicStub::remove_listener( CcsSicStubListener & listener)
{
		boost::mutex::scoped_lock lock(m_mutex);
		m_listeners.remove_if( boost::bind( equal_to<CcsSicStubListener*>() , _1, &listener ) );

}		

void CcsSicStub::notify(TAaSysComMsgId id 
								,TAaSysComSicad receiver
								,TAaSysComSicad sender
								,const std::vector<CcsSicStub::byte> & payload )
{
		boost::mutex::scoped_lock lock(m_mutex);
		std::for_each(m_listeners.begin(),m_listeners.end(), boost::bind( &CcsSicStubListener::onMessage, _1 , id, receiver,sender , payload) );

}

}
