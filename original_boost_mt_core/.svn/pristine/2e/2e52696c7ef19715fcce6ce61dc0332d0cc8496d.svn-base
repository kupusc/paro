#include "dbg_prints.h"
#include "glo_def.h"
#include <cstdarg>
#include "sw_conf_table.h"
#include "oam_conf_table.h"
#include <cstdio>
#include <SSW_SupportSoftware/dbgPrint/dbgPrint.h>
#include <SSW_SupportSoftware/Logger/dbgPrint.h>

static const char * const mt_FeatureString[] = DBG_FEATURE_STRING;
#ifndef LTE
static const char * const mt_oam_string_tbl[] = DBG_OAM_STRING; 
#endif

namespace SSW_SupportSoftware
{
    namespace Logger
    {
        void dbgVPrint(enum MON_SEVERITY severity, enum ERadParamBtsom featureId, const char* format, va_list args)
        {
			char buffer[1024*32] = {0};
			vsprintf(buffer, format, args);
			std::string const line(buffer);
			std::string severity_str;
			std::string feature;

			u32 max_id = sizeof( mt_oam_string_tbl ) / sizeof( mt_oam_string_tbl[0] );	
			assert( (featureId & 0x0000FFFF) < max_id );  
			feature = mt_oam_string_tbl[featureId & 0x0000FFFF];

			if (MON_SEVERITY_ERROR == severity)
			{
				severity_str = "ERR";
			}
			else if (MON_SEVERITY_WARNING == severity)
			{
				severity_str = "WRN";
			}
			else if (MON_SEVERITY_INFO == severity)
			{
				severity_str = "INF";
			}
			else if (MON_SEVERITY_DEBUG == severity)
			{
				severity_str = "DBG";
			}
			else
			{
				assert(false);
			}	
			dbg_prints::instance()->addPrint(severity_str + "/" + feature + ", " + line);
        }

        void dbgPrint(enum MON_SEVERITY severity, enum ERadParamBtsom featureId, const char* format, ...)
        {
            va_list args;
            va_start(args, format);
            dbgVPrint(severity, featureId, format, args);
            va_end(args);
        }

        void dbgPrint(enum MON_SEVERITY severity, enum ERadParamBtsom featureId, u32 priority, const char* format, ...)
        {
            va_list args;
            va_start(args, format);
            dbgVPrint(severity, featureId, format, args);
            va_end(args);    
        }        
    }
}


void dbg_print(enum MON_SEVERITY severity,u32 featureId, const char* format, ...)
{
    char buffer[1024*32] = {0};

    va_list args;
    va_start(args, format);
    vsprintf(buffer, format, args);
    va_end(args);


    std::string line(buffer);
    std::string severity_str;
    std::string feature;

    if ( featureId >> 16 != 0 )
    {
#ifdef LTE
        u32 max_id=sizeof(oam_rad_flags)/sizeof(oam_rad_flags[0]);
        assert( (featureId & 0x0000FFFF) < max_id ) ;  
        for (int i=0; i<max_id; i++)
        {
            if (oam_rad_flags[i].id == featureId)
            {
                feature = oam_rad_flags[i].print;
                continue;
            }
        }
#else
        u32 max_id=sizeof(mt_oam_string_tbl)/sizeof(mt_oam_string_tbl[0]);	
        assert( (featureId & 0x0000FFFF) < max_id ) ;  
        feature = mt_oam_string_tbl[featureId & 0x0000FFFF];
#endif
    }
    else
    {
        u32 max_id=sizeof(mt_FeatureString)/sizeof(mt_FeatureString[0]);
        assert( featureId < max_id ) ;  
        feature =  mt_FeatureString[featureId];
    }


    if (severity == MON_SEVERITY_ERROR)
    {
        severity_str = "ERR";
    }
    else if (severity == MON_SEVERITY_WARNING)
    {
        severity_str = "WRN";
    }
    else if (severity == MON_SEVERITY_INFO)
    {
        severity_str = "INF";
    }
    else if (severity == MON_SEVERITY_DEBUG)
    {
        severity_str = "DBG";
    }
    else
    {
        assert(false);
    }	

    std::string full( severity_str + "/" + feature + ", " + line );


    dbg_prints::instance()->addPrint(full);
}

void SSW_SupportSoftware::dbgPrint(enum MON_SEVERITY severity, enum ERadParamBtsom featureId, const char* format, ...)
{
    char buffer[1024*32] = {0};
    va_list args;
    va_start(args, format);
    vsprintf(buffer, format, args);
    va_end(args);
    
    std::string const line(buffer);
    std::string severity_str;
    std::string feature;

    u32 max_id = sizeof( mt_oam_string_tbl ) / sizeof( mt_oam_string_tbl[0] );	
    assert( (featureId & 0x0000FFFF) < max_id );  
    feature = mt_oam_string_tbl[featureId & 0x0000FFFF];

    if (MON_SEVERITY_ERROR == severity)
    {
        severity_str = "ERR";
    }
    else if (MON_SEVERITY_WARNING == severity)
    {
        severity_str = "WRN";
    }
    else if (MON_SEVERITY_INFO == severity)
    {
        severity_str = "INF";
    }
    else if (MON_SEVERITY_DEBUG == severity)
    {
        severity_str = "DBG";
    }
    else
    {
        assert(false);
    }	
    dbg_prints::instance()->addPrint(severity_str + "/" + feature + ", " + line);
}

void SSW_SupportSoftware::dbgPrint(enum MON_SEVERITY severity, enum ERadParamBtsom featureId, u32 priority, const char* format, ...)
{
    va_list arglist;
    va_start (arglist, format);
    SSW_SupportSoftware::dbgPrint(severity, featureId, format, arglist);
    va_end (arglist);
}

extern "C"
{



    void dbg_print(enum MON_SEVERITY severity, enum FEAT_DBG featureId, const char* format, ...)
    {
        char buffer[1024*32] = {0};

        va_list args;
        va_start(args, format);
        vsprintf(buffer, format, args);
        va_end(args);

        std::string line(buffer);
        std::string severity_str;
        std::string feature;

        if ( featureId >> 16 != 0 )
        {
#ifdef LTE
            u32 max_id=sizeof(oam_rad_flags)/sizeof(oam_rad_flags[0]);
            assert( (featureId & 0x0000FFFF) < max_id ) ;  
            for (int i=0; i<max_id; i++)
            {
                if (oam_rad_flags[i].id == featureId)
                {
                    feature = oam_rad_flags[i].print;
                    continue;
                }
            }
#else
            u32 max_id=sizeof(mt_oam_string_tbl)/sizeof(mt_oam_string_tbl[0]);	
            assert( (featureId & 0x0000FFFF) < max_id ) ;  
            feature = mt_oam_string_tbl[featureId & 0x0000FFFF];
#endif
        }
        else
        {
            u32 max_id=sizeof(mt_FeatureString)/sizeof(mt_FeatureString[0]);
            assert( featureId < max_id ) ;  
            feature =  mt_FeatureString[featureId];
        }


        if (severity == MON_SEVERITY_ERROR)
        {
            severity_str = "ERR";
        }
        else if (severity == MON_SEVERITY_WARNING)
        {
            severity_str = "WRN";
        }
        else if (severity == MON_SEVERITY_INFO)
        {
            severity_str = "INF";
        }
        else if (severity == MON_SEVERITY_DEBUG)
        {
            severity_str = "DBG";
        }
        else
        {
            assert(false);
        }	

        std::string full( severity_str + "/" + feature + ", " + line );


        dbg_prints::instance()->addPrint(full);

    }


}
