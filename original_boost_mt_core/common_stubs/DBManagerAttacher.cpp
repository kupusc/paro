#include "DBManagerAttacher.h"
#include <boost/bind.hpp>
#include <DBStatistics.h>
#include <DBLogger.h>

namespace original_boost_mt_core
{
    namespace common_stubs
    {
        DBManagerAttacher::DBManagerAttacher(DBManager &hostDBManager): Database(hostDBManager.getAppId(), hostDBManager.getThread()), mHostDBManager(hostDBManager)
        {
        }

        DBManagerAttacher::~DBManagerAttacher()
        {
            setInstance(NULL); // < unfortunately DBManager inherits from DistributedObject and DistributedObject unregisters from DBManager...

            delete getItsSubscriptionContainer(); // < Database thinks it's passe to delete it
            setItsSubscriptionContainer(NULL);
            delete getItsDBStatistics();
            setItsDBStatistics(NULL);
            delete getItsDBLogger();
            setItsDBLogger(NULL);

            // note: since Database calls DBLogger constructor and startBehavior (which creates new OMStartBehaviorEvent())
            // its impossible to test it with mem leak detection is on
        }

        bool DBManagerAttacher::AttachPlugIn(DBPlugin* subscriber, ObjectType objectType, String attribute, ObjectId objectId)
        {
            return processCall<bool>(mAttachedAttachPlugIn, boost::bind(&DBManager::AttachPlugIn, _1, subscriber, objectType, attribute, objectId));
        }

        ObjectId DBManagerAttacher::Delete(DBObject* object, int appId)
        {
            return mHostDBManager.Delete(object, appId);
        }

        bool DBManagerAttacher::DetachPlugIn(DBPlugin* subscriber, ObjectType objectType, String attribute, ObjectId objectId)
        {
            return mHostDBManager.DetachPlugIn(subscriber, objectType, attribute, objectId);
        }

        DBResultSet* DBManagerAttacher::Fetch(DBObject* object, int appId)
        {
            return mHostDBManager.Fetch(object, appId);
        }

        map<Query::QueryLevel_key, DBResultSet*> DBManagerAttacher::Fetch(Query* qry, list<Query::QueryLevel_key> subResultsReturned, int appId)
        {
            return mHostDBManager.Fetch(qry, subResultsReturned, appId);
        }

        DBResultSet* DBManagerAttacher::Fetch(String distName, int appId)
        {
            return mHostDBManager.Fetch(distName, appId);
        }

        DBResultSet* DBManagerAttacher::Fetch(Query* qry, int appId)
        {
            return mHostDBManager.Fetch(qry, appId);
        }

        ObjectId DBManagerAttacher::Insert(DBObject* object, int appId)
        {
            return processCall<ObjectId>(mAttachedInsert, boost::bind(&DBManager::Insert, _1, object, appId));
        }

        void DBManagerAttacher::attachInsert(DBManager &dbManager)
        {
            mAttachedInsert.push_back(&dbManager);
        }

        String DBManagerAttacher::PrintXML(AppId appId, ObjectId objectId, ObjectType objectType, DBDumpPolicy* policy)
        {
            return mHostDBManager.PrintXML(appId, objectId, objectType, policy);
        }

        ObjectId DBManagerAttacher::StoreDb(int dbPart, String fileName, tDumpScope pDumpScope)
        {
            return mHostDBManager.StoreDb(dbPart, fileName, pDumpScope);
        }

        bool DBManagerAttacher::SubscribeDBListChange(OMReactive* subscriber, AppId appId, ObjectType objectType, OperationType operation)
        {
            return mHostDBManager.SubscribeDBListChange(subscriber, appId, objectType, operation);
        }

        bool DBManagerAttacher::SubscribeDBObjectChange(OMReactive* subscriber, AppId appId, ObjectType objectType, ObjectId objectId)
        {
            return mHostDBManager.SubscribeDBListChange(subscriber, appId, objectType, objectId);
        }

        bool DBManagerAttacher::SubscribeDBObjectChange(OMReactive* subscriber, AppId appId, String distName)
        {
            return mHostDBManager.SubscribeDBObjectChange(subscriber, appId, distName);
        }

        bool DBManagerAttacher::SubscribeDBParameterChange(OMReactive* subscriber, AppId appId, ObjectType objectType, ObjectId objectId, String attribute)
        {
            return mHostDBManager.SubscribeDBParameterChange(subscriber, appId, objectType, objectId, attribute);
        }

        bool DBManagerAttacher::SubscribeDBParameterChange(OMReactive* subscriber, AppId appId, String distName, String attribute)
        {
            return mHostDBManager.SubscribeDBParameterChange(subscriber, appId, distName, attribute);
        }

        bool DBManagerAttacher::UnsubscribeDBListChange(OMReactive* subscriber, AppId appId, ObjectType objectType)
        {
            return mHostDBManager.UnsubscribeDBListChange(subscriber, appId, objectType);
        }

        bool DBManagerAttacher::UnsubscribeDBObjectChange(OMReactive* subscriber, AppId appId, ObjectType objectType, ObjectId objectId)
        {
            return mHostDBManager.UnsubscribeDBObjectChange(subscriber, appId, objectType, objectId);
        }

        bool DBManagerAttacher::UnsubscribeDBObjectChange(OMReactive* subscriber, AppId appId, String distName)
        {
            return mHostDBManager.UnsubscribeDBObjectChange(subscriber, appId, distName);
        }

        bool DBManagerAttacher::UnsubscribeDBParameterChange(OMReactive* subscriber, AppId appId, ObjectType objectType, ObjectId objectId, String attribute)
        {
            return mHostDBManager.UnsubscribeDBParameterChange(subscriber, appId, objectType, objectId, attribute);
        }

        bool DBManagerAttacher::UnsubscribeDBParameterChange(OMReactive* subscriber, AppId appId, String distName, String attribute)
        {
            return mHostDBManager.UnsubscribeDBParameterChange(subscriber, appId, distName, attribute);
        }

        int DBManagerAttacher::Update(DBObject* object, int appId)
        {
            return processCall<int>(mAttachedUpdate, boost::bind(&DBManager::Update, _1, object, appId));
        }

        void DBManagerAttacher::attachUpdate(DBManager &dbManager)
        {
            mAttachedUpdate.push_back(&dbManager);
        }


    }

}