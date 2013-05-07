#include "DBManagerMock.h"
#include <deque>
#include <string>

using namespace boost::test_tools;

typedef std::map<std::string, DynamicAttribute> Attributes;
typedef std::map<std::string, std::string> StringAttributes;
typedef std::deque<std::string> Keys;


namespace {

    static const int StaticAttributesCount = 21;
    const char *staticAttributes[StaticAttributesCount] = {"HWVersion", "SWState", "blockingState", "bsId", "cabinetId", "commissioned", "exist",
        "logicalId", "manufacturer", "operationalState", "productCode", "rack", "serialNro", "shelf", "slot", "state", "subrack", "unitName", "unitNumber",
        "unitType", "variant"};
    std::deque<std::string> const staticAttributesDeque(staticAttributes, staticAttributes+StaticAttributesCount);

    template<typename Value>
    Keys getKeys(const std::map<std::string, Value> &attributes)
    {
        std::deque<std::string> keys; 
        for(typename std::map<std::string, Value>::const_iterator i = attributes.begin(); attributes.end() != i; ++i)
        {
            keys.push_back(i->first);        
        }
        return keys;
    }

    void removeUnimportantKeys(Attributes &attributes)
    {
        std::deque<std::string> actualKeys(getKeys(attributes));

        for(std::deque<std::string>::const_iterator i = actualKeys.begin(); actualKeys.end() != i; ++i)
        {
            if(std::string::npos != i->find("is set by client"))
            {
                // small chances that anyone would ever care if set by client, and it's hard to compare such keys
                attributes.erase(*i);
                continue;
            }
            if(std::string::npos != i->find("type is bool"))
            {
                // causes problems with comparison when one is set by client
                attributes.erase(*i);
                continue;
            }

            if(std::find(staticAttributes, staticAttributes+StaticAttributesCount, *i) != staticAttributes+StaticAttributesCount)
            {
                // if set by client, units will have those redundant(?) values which breaks our comparison "algorithm"
                attributes.erase(*i);
                continue;
            }
        }
    }

    Keys getSetAttributes(const DBObject &object)
    {
        std::deque<std::string> keys(getKeys(*object.get_dynamicAttributes())), result;
        for(std::deque<std::string>::const_iterator i = keys.begin(); keys.end() != i; ++i)
        {
            if(std::string::npos != i->find(DB_SET_BY_CLIENT_STR))
            {
                continue;
            }
            if(std::string::npos != i->find(DB_TYPED_ATTR_PREFIX))
            {
                continue;
            }
            result.push_back(*i);
        }
        return result;
    }

    bool getAttributeValueAsString(const DBObject &object, const std::string &name, ::string &value)
    {
        return const_cast<DBObject&>(object).getAttribute(name, value);
    }

    StringAttributes getAttributesAsStrings(const DBObject &object, bool onlySetByClient = false)
    {
        std::deque<std::string> const keys = getSetAttributes(object);
        std::map<std::string, std::string> result;

        for(std::deque<std::string>::const_iterator i = keys.begin(); keys.end() != i; ++i)
        {
            if(!onlySetByClient || (object.get_dynamicAttributes()->end() != object.get_dynamicAttributes()->find(*i + DB_SET_BY_CLIENT_STR))
                || (staticAttributesDeque.end() != std::find(staticAttributesDeque.begin(), staticAttributesDeque.end(), *i)))
            {
                result[*i] = "???";
                getAttributeValueAsString(object, *i, result[*i]);
            }
        }

        return result;
    }

    predicate_result assertEquals(const StringAttributes &expected, const StringAttributes &actual)
    {
        predicate_result res = true;
        std::deque<std::string> expectedKeys(getKeys(expected)); 
        std::deque<std::string> actualKeys(getKeys(actual)); 

        std::deque<std::string> excessExpected;
        std::set_difference(expectedKeys.begin(), expectedKeys.end(), actualKeys.begin(), actualKeys.end(), std::back_inserter(excessExpected));
        std::deque<std::string> excessActual;
        std::set_difference(actualKeys.begin(), actualKeys.end(), expectedKeys.begin(), expectedKeys.end(), std::back_inserter(excessActual));

        if(!excessExpected.empty())
        {
            res = false;
            res.message() << "[";
            for(Keys::const_iterator i = excessExpected.begin(); excessExpected.end() != i; ++i)
            {
                res.message() << "\"" << *i << "\" ";
            }
            res.message() << "] <- excessExpected ";
        }

        if(!excessActual.empty())
        {
            res = false;
            res.message() << "[";
            for(Keys::const_iterator i = excessActual.begin(); excessActual.end() != i; ++i)
            {
                res.message() << "\"" << *i << "\" ";
            }
            res.message() << "] <- excessActual ";
        }

        if(res)
        {
            for(Keys::const_iterator i = expectedKeys.begin(); expectedKeys.end() != i; ++i)
            {
                if(expected.find(*i)->second != actual.find(*i)->second)
                {
                    res = false;
                    res.message() << *i << ": " << expected.find(*i)->second << " != " << actual.find(*i)->second << " ";
                }
            }
        }

        return res;
    }

}

namespace mock
{

    mock::stream& operator<<( mock::stream& s,  DBObject* t )
    {
        return s << original_boost_mt_core::common_stubs::GlobalDBObjectConstraintBase::serializeToString(*t);
    }

    mock::stream& operator<<( mock::stream& s, const ObjectRelation* t )
    {
        return s << original_boost_mt_core::common_stubs::GlobalDBObjectConstraintBase::serializeToString(*t);
    }

}

namespace original_boost_mt_core
{
    namespace common_stubs
    {
        // GlobalDBObjectConstraintBase

        GlobalDBObjectConstraintBase::GlobalDBObjectConstraintBase(ComparisonScale comparisonScale):res(true),mComparisonScale(comparisonScale) 
        {
        }

        std::string GlobalDBObjectConstraintBase::serializeToString(const DBObject &object)
        {
            std::stringstream str;
            str << "(DBObject:" << std::hex << "0x" << object.get_id() << std::dec << " " << mock::format(getAttributesAsStrings(object, true)) << ')';
            return str.str();
        }

        std::string GlobalDBObjectConstraintBase::serializeToString(const ObjectRelation &object)
        {
            std::stringstream str;
            str << "(ObjectRelation:" << std::hex << "0x" << object.get_from() << " -> 0x" << object.get_to() << ')';
            return str.str();
        }

        predicate_result assertEquals(DBObject* expected, DBObject* actual, GlobalDBObjectConstraintBase::ComparisonScale comparisonScale)
        {
            std::map<std::string, DynamicAttribute> expectedMap(*expected->get_dynamicAttributes());
            std::map<std::string, DynamicAttribute> actualMap(*actual->get_dynamicAttributes());

            if(GlobalDBObjectConstraintBase::csString == comparisonScale)
            {
                return ::assertEquals(getAttributesAsStrings(*expected), getAttributesAsStrings(*actual));
            }

            if(GlobalDBObjectConstraintBase::csSetByClientString == comparisonScale)
            {
                return ::assertEquals(getAttributesAsStrings(*expected, true), getAttributesAsStrings(*actual, true));
            }

            if(GlobalDBObjectConstraintBase::csNoDynamicHelpers == comparisonScale)
            {
                removeUnimportantKeys(expectedMap);
                removeUnimportantKeys(actualMap);
            }

            predicate_result res = true;
            if( expectedMap.size() != actualMap.size())
            {
                res = false;
                res.message() << "[" << expected->get_dynamicAttributes()->size() << " != " << actual->get_dynamicAttributes()->size() << "] " << "<- dynamicAttributes.size() ";
            }

            // first compare names, no point comparing if they differ (and its easier that way)
            {
                std::deque<std::string> expectedKeys(getKeys(expectedMap)); 
                std::deque<std::string> actualKeys(getKeys(actualMap)); 

                std::deque<std::string> excessExpected;
                std::set_difference(expectedKeys.begin(), expectedKeys.end(), actualKeys.begin(), actualKeys.end(), std::back_inserter(excessExpected));
                std::deque<std::string> excessActual;
                std::set_difference(actualKeys.begin(), actualKeys.end(), expectedKeys.begin(), expectedKeys.end(), std::back_inserter(excessActual));

                if(!excessExpected.empty())
                {
                    res = false;
                    res.message() << "[";
                    for(std::deque<std::string>::const_iterator i = excessExpected.begin(); excessExpected.end() != i; ++i)
                    {
                        res.message() << "\"" << *i << "\" ";
                    }
                    res.message() << "] <- excessExpected ";
                }
                if(!excessActual.empty())
                {
                    res = false;
                    res.message() << "[";
                    for(std::deque<std::string>::const_iterator i = excessActual.begin(); excessActual.end() != i; ++i)
                    {
                        res.message() << "\"" << *i << "\" ";
                    }
                    res.message() << "] <- excessActual ";
                }
            }

            if(res)
            {
                for(std::map<std::string, DynamicAttribute>::const_iterator expectedMapIter = expectedMap.begin(), actualMapIter = actualMap.begin(); 
                    expectedMapIter != expectedMap.end(); ++expectedMapIter, ++actualMapIter)
                {
                    if((*expectedMapIter).first != (*actualMapIter).first)
                    {
                        res = false;
                        res.message() << "[" << (*expectedMapIter).first << " != " << (*actualMapIter).first << "] " << "<- dynamicAttributes ";
                    }

                    if((*expectedMapIter).second.get_access() != (*actualMapIter).second.get_access())
                    {
                        res = false;
                        res.message() << "[" << (*expectedMapIter).second.get_access()  << " != " << (*actualMapIter).second.get_access() << "] " << "<- dynamicAttributes\"" << actualMapIter->first <<  "\".access ";
                    }

                    if((*expectedMapIter).second.get_value() != (*actualMapIter).second.get_value())
                    {
                        res = false;
                        res.message() << "[" << (*expectedMapIter).second.get_value() << " != " << (*actualMapIter).second.get_value() << "] " << "<- dynamicAttributes\"" << actualMapIter->first <<  "\".value "; 
                    }   

                    if((*expectedMapIter).second.get_volatile() != (*actualMapIter).second.get_volatile())
                    {
                        res = false;
                        res.message() << "[" << (*expectedMapIter).second.get_volatile() << " != " << (*actualMapIter).second.get_volatile() << "] " << "<- dynamicAttributes\"" << actualMapIter->first <<  "\".volatile ";
                    }           
                }
            }

            return res; 
        }
        
        predicate_result assertEquals(Unit* expected, Unit* actual, GlobalDBObjectConstraintBase::ComparisonScale comparisonScale)
        {
            predicate_result res = assertEquals(static_cast<DBObject *>(expected), static_cast<DBObject *>(actual), comparisonScale);

            if(GlobalDBObjectConstraintBase::csString == comparisonScale || GlobalDBObjectConstraintBase::csSetByClientString == comparisonScale)
            {
                return res;
            }

            if(expected->get_HWversion() != actual->get_HWversion())
            {
                res = false;
                res.message() << "[" << expected->get_HWversion() << " != " << actual->get_HWversion() << "] " << "<- HWversion "; 
            }

            if(expected->get_SWState() != actual->get_SWState())
            {
                res = false;
                res.message() << "[" << expected->get_SWState() << " != " << actual->get_SWState() << "] " << "<- SWState "; 
            }

            if(expected->get_blockingState() != actual->get_blockingState())
            {
                res = false;
                res.message() << "[" << expected->get_blockingState() << " != " << actual->get_blockingState() << "] " << "<- blockingState "; 
            }

            if(expected->get_bsId() != actual->get_bsId())
            {
                res = false;
                res.message() << "[" << expected->get_bsId() << " != " << actual->get_bsId() << "] " << "<- bsId "; 
            }

            if(expected->get_cabinetId() != actual->get_cabinetId())
            {
                res = false;
                res.message() << "[" << expected->get_cabinetId() << " != " << actual->get_cabinetId() << "] " << "<- cabinetId ";
            }

            if(expected->get_commissioned() != actual->get_commissioned())
            {
                res = false;
                res.message() << "[" << expected->get_commissioned() << " != " << actual->get_commissioned() << "] " << "<- commissioned "; 
            }

            if(expected->get_exist() != actual->get_exist())
            {
                res = false;
                res.message() << "[" << expected->get_exist() << " != " << actual->get_exist() << "] " << "<- exist "; 
            }

            if(expected->get_logicalId() != actual->get_logicalId())
            {
                res = false;
                res.message() << "[" << expected->get_logicalId() << " != " << actual->get_logicalId() << "] " << "<- logicalId "; 
            }

            if(expected->get_manufacturer() != actual->get_manufacturer())
            {
                res = false;
                res.message() << "[" << expected->get_manufacturer() << " != " << actual->get_manufacturer() << "] " << "<- manufacturer ";
            }

            if(expected->get_operationalState() != actual->get_operationalState())
            {
                res = false;
                res.message() << "[" << expected->get_operationalState() << " != " << actual->get_operationalState() << "] " << "<- operationalState ";
            }

            if(expected->get_productCode() != actual->get_productCode())
            {
                res = false;
                res.message() << "[" << expected->get_productCode() << " != " << actual->get_productCode() << "] " << "<- productCode ";
            }

            if(expected->get_rack() != actual->get_rack())
            {
                res = false;
                res.message() << "[" << expected->get_rack() << " != " << actual->get_rack() << "] " << "<- rack "; 
            }

            if(expected->get_serialNro() != actual->get_serialNro())
            {
                res = false;
                res.message() << "[" << expected->get_serialNro() << " != " << actual->get_serialNro() << "] " << "<- serialNro ";
            }    

            if(expected->get_shelf() != actual->get_shelf())
            {
                res = false;
                res.message() << "[" << expected->get_shelf() << " != " << actual->get_shelf() << "] " << "<- shelf "; 
            }  

            if(expected->get_slot() != actual->get_slot())
            {
                res = false;
                res.message() << "[" << expected->get_slot() << " != " << actual->get_slot() << "] " << "<- slot "; 
            }  

            if(expected->get_state() != actual->get_state())
            {
                res = false;
                res.message() << "[" << expected->get_state() << " != " << actual->get_state() << "] " << "<- state "; 
            }

            if(expected->get_subrack() != actual->get_subrack())
            {
                res = false;
                res.message() << "[" << expected->get_subrack() << " != " << actual->get_subrack() << "] " << "<- subrack "; 
            }    

            if(expected->get_unitName() != actual->get_unitName())
            {
                res = false;
                res.message() << "[" << expected->get_unitName() << " != " << actual->get_unitName() << "] " << "<- unitName ";
            } 

            if(expected->get_unitNumber() != actual->get_unitNumber())
            {
                res = false;
                res.message() << "[" << expected->get_unitNumber() << " != " << actual->get_unitNumber() << "] " << "<- unitNumber "; 
            }     

            if(expected->get_unitType() != actual->get_unitType())
            {
                res = false;
                res.message() << "[" << expected->get_unitType() << " != " << actual->get_unitType() << "] " << "<- unitType ";
            } 

            if(expected->get_variant() != actual->get_variant())
            {
                res = false;
                res.message() << "[" << expected->get_variant() << " != " << actual->get_variant() << "] " << "<- variant ";
            } 
            return res; 
        }

        DBManagerMock::DBManagerMock(AppId id, OMThread* p_thread) : DBManager(0, OMDefaultThread) 
        {
        }

        DBManagerMock::~DBManagerMock() 
        {

        }

    } // common_stubs

} // original_boost_mt_core
