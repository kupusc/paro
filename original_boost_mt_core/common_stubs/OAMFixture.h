#ifndef _OAM_FIXTURE_H_1757F5B0_F562_4FB3_B641_23C586922EDA_
#define _OAM_FIXTURE_H_1757F5B0_F562_4FB3_B641_23C586922EDA_

#include <boost/scoped_ptr.hpp>

class Registry;
class ServiceRegistry;

namespace original_boost_mt_core
{
    namespace common_stubs 
    {
        /// @brief Common fixture for MT tests
        /** 
        * @warning Non-thread-safe
        */
        class OAMFixture
        {
        public:
            OAMFixture(bool initEverythingOnConstruction);
            ~OAMFixture();

            void initEverything();

            /// @brief Initializes OXF
            /** Can't be de-initialized
            */
            void initOXF();

            void initHWWAddress();

            void initRegistry();

            /// @brief Creates CServiceRegistry instance
            /** 
            * @todo LEAKS!!!
            */
            void initSSW();

            /// @brief Creates CServiceRegistry instance
            /** Requires SSW
            * @todo LEAKS!!!
            */
            void initCServiceRegistry();

            /// @brief Creates DBManager instance
            /** 
            * @todo LEAKS!!!
            */
            void initDB();

        private:
            void deleteRegistry();

            static bool mOXFInitialized;
            static bool mSSWInitialized;
            static bool mCServiceRegistryInitialized;
            static bool mDBInitialized;
            boost::scoped_ptr<Registry> mDeleteRegistry;
            boost::scoped_ptr<ServiceRegistry> mDeleteServiceRegistry;

        };

    }

}

#endif //_OAM_FIXTURE_H_1757F5B0_F562_4FB3_B641_23C586922EDA_
