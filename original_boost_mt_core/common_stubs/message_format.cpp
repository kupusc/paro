#include "message_format.h"

#include <sstream>
#include <iomanip>
#include <algorithm>
#include <boost/tokenizer.hpp>

using namespace std;

    namespace
    {
        class SysComMsgPrint
        {
        public:
            SysComMsgPrint(ostringstream & os) :  m_os(os)
            {
            }
            void operator() (unsigned char x)
            {
                m_os << setw(2) <<static_cast<int>(x) << ' ';
            }
        private:
            ostringstream & m_os;
        };
    }
    
    std::string SysComMsgFormat::formatMsg(const std::vector<unsigned char> & vec)
    {
        ostringstream os;
        os << hex << uppercase << setfill('0');    
        SysComMsgPrint d(os);
        for_each(vec.begin(),vec.end(),d);
        return os.str();    
    }

    namespace
    {
        class format
        {
        public:
            format(vector<unsigned char> & os) :  m_os(os)
            {
            }
            void operator() (std::string s)
            {
                istringstream is(s);
                unsigned int x;
                is >> hex >> setw(2) >> x;
                assert(x <256);
                m_os.push_back(x);
            }
        private:
            vector<unsigned char>  & m_os;
        };
    }

    
    std::vector<unsigned char> SysComMsgFormat::formatMsg(const std::string & s)
    {
        boost::tokenizer<> tok(s);
        std::vector<unsigned char> msg;

        for_each(tok.begin(),tok.end(),format(msg));
        return msg;
    }


    
