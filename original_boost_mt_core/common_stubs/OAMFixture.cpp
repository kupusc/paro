#include "OAMFixture.h"
#include <OMTimeout.h>
#include "WorkaroundNonLeakingOXFAllocator.h"
#include <oxf/oxf.h>
#include <exception>
#include <assert.h>
#include "ccs_default_impl.h"
#include <Glo_bs.h>
#include <HWW.h>
#include "Registry.h"
#include <ServiceRegistry.h>
#include <SSW_SupportSoftware/Init.h>
#include "CServiceRegistry.h"
#include "DBW_DbWInitializer.h"
#include <stdexcept>

namespace original_boost_mt_core
{

    namespace common_stubs 
    {
        bool OAMFixture::mOXFInitialized = false;
        bool OAMFixture::mSSWInitialized = false;
        bool OAMFixture::mCServiceRegistryInitialized = false;
        bool OAMFixture::mDBInitialized = false;

        OAMFixture::OAMFixture(bool initEverythingOnConstruction)
        {
            if(initEverythingOnConstruction)
            {
                initEverything();
            }
        }

        OAMFixture::~OAMFixture()
        {
            deleteRegistry();
        }

        void OAMFixture::initEverything()
        {
            initOXF();
            initHWWAddress();
            initRegistry();  
            initSSW();       
            initCServiceRegistry();
            initDB();
        }

        void OAMFixture::initOXF()
        {
            if(!mOXFInitialized)
            {
                // Has it's own leaking memory allocator, so when OXF is initialized it gives one 4400 bytes leak
                OMTimeout::OMSetMemoryAllocator(WorkaroundNonLeakingOXFAllocator<OMTimeout>::allocate);

                if (OXF::init(0, NULL, 0, NULL,
                    OMTimerManagerDefaults::defaultTicktime,
                    OMTimerManagerDefaults::defaultMaxTM, false))
                {
                    OXF::start(true);
                }
                else
                {
                    throw std::runtime_error("Failed to initialize OXF");
                }

                mOXFInitialized = true;
            }
        }

        void OAMFixture::initHWWAddress()
        {
            class myCCSstub : public CcsStubImplDefault
            {
                // this stubs inits HWW so omGetCurrentBoard() returns valid board.
                // DB needs proper value to notify clients about db changes
                TAaSysComSicad AaSysComSicadGet(const TAaSysComCpid userCpid,const TAaSysComNid userNid)
                {
                    return 0;
                }
                TBoard AaSysComNmapGetBoard(TAaSysComSicad sicAddress)
                {
                    return FSM1_FCM;
                }
                TCpu AaSysComNmapGetCpu(TAaSysComSicad sicAddress)
                {
                    return 0;
                }

            };


            myCCSstub stub;
            HWW::omGetCurrentBoard(); // inits HWW board
            HWW::omGetCurrentCpu(); //  inits HWW board

        }

        void OAMFixture::initRegistry()
        {
            assert(mOXFInitialized);

            deleteRegistry();

            mDeleteRegistry.reset(Registry::Instance (HWW::omGetCurrentBoard()));
            mDeleteServiceRegistry.reset(ServiceRegistry::Instance()); //instantiated by Registry anyway
        }

        void OAMFixture::initSSW()
        {
            if(!mSSWInitialized)
            {
                SSW_SupportSoftware::init(); // < leaks like crazy

                mSSWInitialized = true;
            }
        }

        void OAMFixture::initCServiceRegistry()
        {
            assert(mSSWInitialized);

            if(!mCServiceRegistryInitialized)
            {
                ServiceRegistry_Pkg::CServiceRegistry::Instance(HWW::omGetCurrentBoard()); // < no way to deinitialize?

                mCServiceRegistryInitialized = true;
            }
        }

        void OAMFixture::initDB()
        {
            if(!mDBInitialized)
            {
                startDB(cOMCoreDBM); // < no way to deinitialize?
                DBW::DbWInitializer::init();
                DBW::DbWInitializer::dbCreated();
                DBManager *dbm = getDBM();

                mDBInitialized = true;
            }
        }

        void OAMFixture::deleteRegistry() 
        {
            mDeleteRegistry.reset();
            struct HackRegistry: public Registry {
                static void clearInstancePtr()
                {
                    instance = NULL;
                }
            };
            HackRegistry::clearInstancePtr();
        }

    } //common_stubs

} //original_boost_mt_core
