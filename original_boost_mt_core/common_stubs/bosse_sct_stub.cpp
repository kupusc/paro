
#include <cassert>
#include "Bosse_Mw.h"
#include "dbg_prints.h"
#include <fstream>
#include <oxf/omtypes.h>
#ifdef _WIN32
#include <windows.h>
#endif
#include "message_format.h"

int rhmain(int, char *[])
{
	dbg_prints::instance()->addPrint("rhmain");
	return 0;
}

namespace stub
{
namespace swbus
{

class message
{
public:	// message format
	//  reciver (4) , sender(4) , payload length(4) , payload( payload length) 
		
	typedef unsigned int u32; 
	typedef unsigned char u8; 
	
	message( u32 receiver , u32 sender , const std::vector<u8> & payload)
		: m_receiver(receiver), m_sender(sender) , m_payload(payload)
	{
	}
	std::vector<u8> data()
	{
		std::vector<u8> ret;
		unsigned char * p = (unsigned char*)&m_receiver;
		ret.insert( ret.end(), p, p+sizeof(m_receiver) );

		p = (unsigned char*)&m_sender;
		ret.insert( ret.end(), p, p+sizeof(m_sender) );

		u32 payloadsize= m_payload.size();
		p = (unsigned char*)&payloadsize;
		ret.insert( ret.end(), p, p+sizeof(payloadsize) );

		ret.insert( ret.end(), m_payload.begin(), m_payload.end() );
		return ret;
	}
	std::string str()
	{
		const std::vector<u8> & d = data();
		const std::string & s = SysComMsgFormat::formatMsg(d);	
		return s;
	}
	
private:
	u32 m_receiver;
	u32 m_sender;
	std::vector<u8> m_payload;
};


class event
{
public:
	typedef message::u8 u8;
	typedef message::u32 u32;
	
	event( u8 type, u32 id, const std::vector<u8> & payload )
		: m_type(type), m_id(id) ,m_payload(payload)
	{
	}
	
	
private:
	u8 m_type;
	u32 m_id;
	std::vector<u8> m_payload;
};




}
}



namespace BosseMw
{

void install(	InterfaceType interfaceType, CallBackHandler callBackHandler, void *callBackParm)
{
		dbg_prints::instance()->addPrint("BosseMw::install");
		//assert(0);
}

void send(InterfaceType interfaceType, void *msg, unsigned int msgLen, void *aux )
{
		assert(msg);
		std::string prefix("BosseMw::send: ");
		unsigned char * pmsg = reinterpret_cast<unsigned char* > ( msg);
		std::vector<unsigned char > v_data( pmsg , pmsg + msgLen);

		const std::string & data = SysComMsgFormat::formatMsg(v_data);
		dbg_prints::instance()->addPrint( prefix + data);

		stub::swbus::message m(0x1234,0x5678,std::vector<stub::swbus::message::u8>());
		std::vector<stub::swbus::message::u8> temp = m.data();


}
 
void unHook(InterfaceType interfaceType)
{
		dbg_prints::instance()->addPrint("BosseMw::unHook");
		//assert(0);
}

void oxfInitialized(void)
{
		dbg_prints::instance()->addPrint("BosseMw::oxfInitialized");
}

//{sync, async}
enum TimingModel  getTimingModel(	void)
{
//		dbg_prints::instance()->addPrint("BosseMw::getTimingModel");
	return async;
}
bool isRevDeinterl(void	)
{
		dbg_prints::instance()->addPrint("BosseMw::isRevDeinterl");
	return false;
}

unsigned __int64 getIniTime (	void)
{
		dbg_prints::instance()->addPrint("BosseMw::getIniTime");
	return 0;
}


}

namespace BosseApi
{

std::filebuf fb;

std::ostream log(&fb);

std::ostream& lock(std::ostream& x)
{
	//dbg_prints::instance()->addPrint("BosseApi::lock");
	return x;
}
std::ostream& unlock(std::ostream& x)
{
	//	dbg_prints::instance()->addPrint("BosseApi::unlock");
	return x;
}

void logAssert( bool pCond,const char *pErr)
{ 
		dbg_prints::instance()->addPrint("BosseApi::logAssert");	
}


}

