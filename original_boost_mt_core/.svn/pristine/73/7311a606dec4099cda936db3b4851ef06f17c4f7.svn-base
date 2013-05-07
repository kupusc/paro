#ifndef _DB_MANAGER_ATTACHER_H_43F62F90_9102_411E_BD4C_AB3DD7D2368C_
#define _DB_MANAGER_ATTACHER_H_43F62F90_9102_411E_BD4C_AB3DD7D2368C_

#include <boost/test/unit_test.hpp>
#include <DBManager.h>
#include <deque>
#include <boost/function.hpp>

#include <Database.h>

namespace original_boost_mt_core
{
    namespace common_stubs
    {
        //! Allows attaching database mocks to existing database
        /*!
         * \note It inherits from Database and not DBManager because DistributedObjects have good old c-style cast to Database* when using it
        */
        class DBManagerAttacher: public Database
        {
        public:
            DBManagerAttacher(DBManager &hostDBManager);
            virtual ~DBManagerAttacher();

            virtual bool AttachPlugIn(DBPlugin* subscriber, ObjectType objectType, String attribute, ObjectId objectId);

            virtual ObjectId Delete(DBObject* object, int appId);

            virtual bool DetachPlugIn(DBPlugin* subscriber, ObjectType objectType, String attribute, ObjectId objectId = 0);

            virtual DBResultSet* Fetch(DBObject* object, int appId);

            virtual map<Query::QueryLevel_key, DBResultSet*> Fetch(Query* qry, list<Query::QueryLevel_key> subResultsReturned, int appId);

            virtual DBResultSet* Fetch(String distName, int appId);

            virtual DBResultSet* Fetch(Query* qry, int appId);

            virtual ObjectId Insert(DBObject* object, int appId);

            void attachInsert(DBManager &dbManager);

            virtual String PrintXML(AppId appId, ObjectId objectId, ObjectType objectType, DBDumpPolicy* policy);

            virtual ObjectId StoreDb(int dbPart, String fileName, tDumpScope pDumpScope = Dump_ALL);

            virtual bool SubscribeDBListChange(OMReactive* subscriber, AppId appId, ObjectType objectType, OperationType operation = INSERT_DELETE_OPERATION);

            virtual bool SubscribeDBObjectChange(OMReactive* subscriber, AppId appId, ObjectType objectType, ObjectId objectId);

            virtual bool SubscribeDBObjectChange(OMReactive* subscriber, AppId appId, String distName);

            virtual bool SubscribeDBParameterChange(OMReactive* subscriber, AppId appId, ObjectType objectType, ObjectId objectId, String attribute);

            virtual bool SubscribeDBParameterChange(OMReactive* subscriber, AppId appId, String distName, String attribute);

            virtual bool UnsubscribeDBListChange(OMReactive* subscriber, AppId appId, ObjectType objectType);

            virtual bool UnsubscribeDBObjectChange(OMReactive* subscriber, AppId appId, ObjectType objectType, ObjectId objectId);

            virtual bool UnsubscribeDBObjectChange(OMReactive* subscriber, AppId appId, String distName);

            virtual bool UnsubscribeDBParameterChange(OMReactive* subscriber, AppId appId, ObjectType objectType, ObjectId objectId, String attribute);

            virtual bool UnsubscribeDBParameterChange(OMReactive* subscriber, AppId appId, String distName, String attribute);

            virtual int Update(DBObject* object, int appId);

            void attachUpdate(DBManager &dbManager);

        protected:
            typedef std::deque<DBManager*> Attached;

            template<typename Result>
            Result processCall(const Attached &attached, boost::function<Result(DBManager*)> call)
            {
                std::for_each(attached.begin(), attached.end(), call);
                return call(&mHostDBManager);
            }


        protected:
            DBManager &mHostDBManager;
            Attached mAttachedAttachPlugIn;
            Attached mAttachedInsert;
            Attached mAttachedUpdate;

        };

    }

}

#endif //_DB_MANAGER_ATTACHER_H_43F62F90_9102_411E_BD4C_AB3DD7D2368C_
