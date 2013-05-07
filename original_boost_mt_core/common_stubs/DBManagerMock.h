#ifndef DBMANAGER_MOCK_H_23094809534
#define DBMANAGER_MOCK_H_23094809534

#include <boost/test/unit_test.hpp>
#include <original_boost_mt_core/test_framework/turtle/mock.hpp>
#include "DBManager.h"
#include <boost/type_traits/is_base_of.hpp>
#include <boost/utility/enable_if.hpp>
#include <exception>
#include <DBObject.h>
#include <memory>
#include <sstream>
#include <boost/shared_ptr.hpp>

namespace mock
{
    mock::stream& operator<<(mock::stream& s, DBObject* t);

    mock::stream& operator<<(mock::stream& s, const ObjectRelation* t);

}

namespace original_boost_mt_core
{
    namespace common_stubs
    {

        struct GlobalDBObjectConstraintBase
        {
            enum ComparisonScale
            {
                csFull, //!< objects must by identical
                csSetByClientString, //!< compares only those set by client by their string value
                csString, //!< compares by string value (deprecated?)
                csNoDynamicHelpers //!< skips some helper values stored in dbobject's attributes field (deprecated?)
            };

            GlobalDBObjectConstraintBase(ComparisonScale comparisonScale);

            static std::string serializeToString(const DBObject &object);
            static std::string serializeToString(const ObjectRelation &object);

            mutable boost::test_tools::predicate_result res;
            ComparisonScale const mComparisonScale;
        };

        template <class DBObjectType>
        struct GlobalDBObjectConstraint: GlobalDBObjectConstraintBase
        {
            // we take a copy, so that even after test is destroyed we are able to print unfulfilled expectations
            mutable boost::shared_ptr<DBObjectType> _expected;

            GlobalDBObjectConstraint(std::auto_ptr<DBObjectType> expected, ComparisonScale comparisonScale)
                :GlobalDBObjectConstraintBase(comparisonScale),_expected(expected.release())
            {
            }

            friend bool operator==( DBObject* actual, const GlobalDBObjectConstraint<DBObjectType>& c)
            {       
                if(NULL == dynamic_cast<DBObjectType*>(actual)) 
                {
                    c.res.message() << "[expected " << mock::format(static_cast<DBObjectType*>(c._expected.get())) << " != actual type ] ";                 
                    return false;
                }

                if( c._expected->get_id() != actual->get_id() )
                {
                    c.res.message() << "[expected " << mock::format( static_cast<DBObjectType*>(c._expected.get())) << " (id: " << c._expected->get_id() << ")"
                        << " != actual: " << mock::format(actual)  << " (id: " << actual->get_id() << ") ] "; 
                    return false;
                }  

                c.res = assertEquals(c._expected.get(), static_cast<DBObjectType*>(actual), c.mComparisonScale);

                return c.res;
            }

            friend std::ostream& operator<<(std::ostream& s, const GlobalDBObjectConstraint& c )
            {
                if(c.res)
                {
                    s << GlobalDBObjectConstraintBase::serializeToString(*c._expected);
                } else
                {
                    s << "Diff: " << c.res.message().str();
                }                
                return s;
            }

        };

        boost::test_tools::predicate_result assertEquals(Unit* expected, Unit* actual, GlobalDBObjectConstraintBase::ComparisonScale comparisonScale);


        template <class DBObjectType>
        GlobalDBObjectConstraint<DBObjectType> dbObjectConstraint(std::auto_ptr<DBObjectType> dbt,
            GlobalDBObjectConstraintBase::ComparisonScale comparisonScale = GlobalDBObjectConstraintBase::csSetByClientString)
        {
            return GlobalDBObjectConstraint<DBObjectType>(dbt, comparisonScale);
        }

        template <class DBObjectType>
        struct DBObjectTypeConstraint
        {
            friend bool operator==(const DBObjectType* actual, const DBObjectTypeConstraint &)
            { 
                return NULL != dynamic_cast<const DBObjectType *>(actual);
            }

            friend std::ostream& operator<<(std::ostream& s, const DBObjectTypeConstraint &)
            {
                return s << "DBObject has wrong type";
            }
        };

        MOCK_BASE_CLASS( DBManagerMock, DBManager )
        {
            DBManagerMock(AppId id = 0, OMThread* p_thread = OMDefaultThread);
            virtual ~DBManagerMock();

            typedef map<Query::QueryLevel_key, DBResultSet*> mapQuery;
            typedef list<Query::QueryLevel_key> listQuery;

            MOCK_METHOD_EXT( AttachPlugIn, 4, bool(DBPlugin* subscriber, ObjectType objectType, String attribute, ObjectId objectId), AttachPlugIn );
            MOCK_METHOD_EXT( Delete, 2, ObjectId (DBObject* object, int appId), Delete );
            MOCK_METHOD_EXT( DetachPlugIn, 4, bool(DBPlugin* subscriber, ObjectType objectType, String attribute, ObjectId objectId), DetachPlugIn );
            MOCK_METHOD_EXT( Fetch, 2, DBResultSet*( DBObject*, int ), Fetch1 );
            MOCK_METHOD_EXT( Fetch, 2, DBResultSet*( Query*, int ), Fetch2 );
            MOCK_METHOD_EXT( Fetch, 2, DBResultSet*( String, int ), Fetch3 );
            MOCK_METHOD_EXT (Fetch, 3, mapQuery (Query*, listQuery, int), Fetch4);
            MOCK_METHOD_EXT( Insert, 2, ObjectId(DBObject* object, int appId), Insert );
            MOCK_METHOD_EXT( PrintXML, 4, String(AppId appId, ObjectId objectId, ObjectType objectType, DBDumpPolicy* policy), PrintXML );
            MOCK_METHOD_EXT( StoreDb, 3, ObjectId(int dbPart, String fileName, tDumpScope pDumpScope), StoreDb );
            MOCK_METHOD_EXT( SubscribeDBListChange, 4, bool (OMReactive* subscriber, AppId appId, ObjectType objectType, OperationType operation), SubscribeDBListChange);
            MOCK_METHOD_EXT( SubscribeDBObjectChange, 4, bool( OMReactive*, AppId, ObjectType, ObjectId ), SubscribeDBObjectChange1 );
            MOCK_METHOD_EXT( SubscribeDBObjectChange, 3, bool( OMReactive* , AppId , String ), SubscribeDBObjectChange2 );
            MOCK_METHOD_EXT( SubscribeDBParameterChange, 5, bool( OMReactive* , AppId , ObjectType , ObjectId , String ), SubscribeDBParameterChange1 );
            MOCK_METHOD_EXT( SubscribeDBParameterChange, 4, bool( OMReactive* , AppId , String , String ), SubscribeDBParameterChange2 );
            MOCK_METHOD_EXT( UnsubscribeDBListChange, 3, bool (OMReactive* subscriber, AppId appId, ObjectType objectType), UnsubscribeDBListChange);
            MOCK_METHOD_EXT( UnsubscribeDBObjectChange, 4, bool( OMReactive* , AppId , ObjectType , ObjectId ), UnsubscribeDBObjectChange1 );
            MOCK_METHOD_EXT( UnsubscribeDBObjectChange, 3, bool( OMReactive* , AppId , String ), UnsubscribeDBObjectChange2 );
            MOCK_METHOD_EXT( UnsubscribeDBParameterChange, 5, bool( OMReactive* , AppId , ObjectType , ObjectId , String ), UnsubscribeDBParameterChange1 );
            MOCK_METHOD_EXT( UnsubscribeDBParameterChange, 4, bool( OMReactive* , AppId , String , String ), UnsubscribeDBParameterChange2 );
            MOCK_METHOD_EXT( Update, 2, int(DBObject* object, int appId), Update );
        };


        template<typename Type>
        typename boost::enable_if<boost::is_base_of<DBObject, Type>, std::auto_ptr<Type> >::type fetchDBObject(ObjectId id)
        {
            std::auto_ptr<Type> result;

            Unit *unit = new Unit;
            unit->set_id(id);
            std::auto_ptr<DBResultSet> res(getDBM()->Fetch(unit, 1234));
            if(res->get_objectCount() == 1)
            {
                result.reset(dynamic_cast<Type*>(res->get_objects()[0]->clone()));
                if(!result.get())
                {
                    throw std::runtime_error("fetchDBObject(): Returned item has wrong type");
                }
            }
            if(res->get_objectCount() > 1)
            {
                throw std::runtime_error("fetchDBObject(): Fetch returned more than one item");
            }
            return result;
        }

        template<typename Type>
        typename boost::enable_if<boost::is_base_of<DBObject, Type>, std::auto_ptr<Type> >::type createDBObject(ObjectId id)
        {
            std::auto_ptr<Type> result(new Type);
            result->set_id(id);
            return result;
        }

    } // common_stubs

} // original_boost_mt_core

#endif //DBMANAGER_MOCK_H_23094809534
