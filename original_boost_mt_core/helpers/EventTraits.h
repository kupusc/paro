#ifndef _EVENT_TRAITS_H_41D3D928_ADB7_46C8_B7B7_B9A4998E5AD2_
#define _EVENT_TRAITS_H_41D3D928_ADB7_46C8_B7B7_B9A4998E5AD2_

#include <boost/typeof/typeof.hpp>
#include <IOxfEventSender.h>
#include <boost/test/predicate_result.hpp>
#include <boost/preprocessor.hpp>
#include <boost/function.hpp>
#include <turtle/config.hpp> //MOCK_MAX_ARGS
#include <turtle/log.hpp> //mock::stream
#include <memory>
#include <map>
#include <string>
#include <boost/scoped_ptr.hpp>
#include <boost/shared_ptr.hpp>

/** \file EventTraits.h
 *
 * Provides ways to register and use event traits.
 * Event traits allow doing generic operations on events like replying and sending with boost::bind
 *
 * For each event one needs to use (once per event) a EVENT_TRAITS_<n>() macro where <n> is arity of event's constructor.
 * Example:
 * EVENT_TRAITS_3(evPRDFaultIndication_v2Reply, client, appId, msn)
 * EVENT_TRAITS_7(TechRepMaster_If_Pkg::evCreateLogFileReq, client, msn, unit, logType, logCause, logSize, subunit)
 *
 * Note that this has to be done in global scope.
 *
 * If for some reason this can't be done, one can be more specific:
 * EVENT_TRAITS_DECL_BEGIN(evPRDFaultIndication_v2Reply, 3)
 * EVENT_TRAITS_ARG(1, client)
 * EVENT_TRAITS_ARG_TYPED(2, int, appId)
 * EVENT_TRAITS_ARG(3, msn)
 * EVENT_TRAITS_DECL_END()
 *
 * With event registered like that, one can use its traits. For instance, for evPRDFaultIndication_v2Reply such 
 traits will be generated (in original_boost_mt_core::helpers::event_traits namespace):
 * template<>
 * struct EventTraits<evPRDFaultIndication_v2Reply>
 * {
 *     typedef evPRDFaultIndication_v2Reply EventType;
 *     static const int Arity = 3;
 *     static inline char* getArgName1() { return "client"; }
 *     static inline char* getArgName2() { return "appId"; }
 *     static inline char* getArgName3() { return "msn"; }
 *     typedef OMReactive* ArgType1;
 *     typedef int ArgType2;
 *     typedef int ArgType3;
 *     static inline ArgType1 getArg1(const EventType &ev) { return ev.client; }
 *     static inline ArgType2 getArg2(const EventType &ev) { return ev.appId; }
 *     static inline ArgType3 getArg3(const EventType &ev) { return ev.msn; }
 * }
 *
 * And so one can get name of second argument with EventTraits<evPRDFaultIndication_v2Reply>::getArgName2() or value of third
 EventTraits<evPRDFaultIndication_v2Reply>::getArg3(*event).
 *
 * If special handling of printing parameter types needs to be supplied, see documentation for Turtle Mock.
 * If special handling of printing parameters needs to be supplied, this can be done like this:
 * namespace original_boost_mt_core
 * {
 *   namespace helpers
 *   {
 *       namespace event_traits
 *       {
 *           template<typename Type>
 *           struct FormatForLog<evParseXmlReq, 3, Type>
 *           {
 *               void operator()(mock::stream &s, const Type &value)
 *               {
 *                   s << "XML...";
 *               }
 *           };
 *       }
 *   }
 * }
 * Meaning - for third argument of evParseXmlReq print only  "XML..." string.
 * Note that such specialisation has to be supplied before EVENT_TRAITS_<n> declaration!
 *
 * If you get:
 * error C2027: use of undefined type 'original_boost_mt_core::helpers::event_traits::EventTraits<Event>'
 * That probably means event was not yet registered in traits with EVENT_TRAITS_<n>
 */

#define EVENT_TRAITS_MAX_ARGS MOCK_MAX_ARGS

#if _MSC_VER >= 1700
// MSVC 2012 supports this from c++11, but it will still work without it
#define EVENT_TRAITS_TYPEOF_CF8ECB55_BCBD_4AE2_961C_54FDA7A77C11(expr) decltype(expr)
#else
//TODO: maybe on gcc it would also make sense, although it has typeof natively in boost so it's not so important
#define EVENT_TRAITS_TYPEOF_CF8ECB55_BCBD_4AE2_961C_54FDA7A77C11(expr) BOOST_TYPEOF((expr))
#endif

#ifdef _MSC_VER 
#define EVENT_TRAITS_STATIC_ASSERT_CF8ECB55_BCBD_4AE2_961C_54FDA7A77C11(expr) BOOST_STATIC_ASSERT(expr)
#else
// gcc is not a big fan of asserts in templates
#define EVENT_TRAITS_STATIC_ASSERT_CF8ECB55_BCBD_4AE2_961C_54FDA7A77C11(expr)
#endif

#define EVENT_TRAITS_DECL_BEGIN(event, argscount) \
    namespace original_boost_mt_core { namespace helpers { namespace event_traits { template<> struct EventTraits<event>: BaseEventTraits<event, argscount> \
    { \
        typedef event EventType; \
        static inline const char* getName() { return &printerRegistrator ? BOOST_STRINGIZE(event) : "this is needed for static initialization of printerRegistrator"; }

#define EVENT_TRAITS_ARG_TYPED(n, type, name) \
    typedef type ArgType ## n; \
    static inline const char* getArgName ## n() { return BOOST_STRINGIZE(name); } \
    static inline ArgType ## n getArg ## n(const EventType &ev) { return ev.name; } \
    static inline void formatArgForLog ## n(mock::stream &s, const EventType &ev) { FormatForLog<EventType, n, ArgType ## n>()(s, getArg ## n(ev)); } \
    EVENT_TRAITS_STATIC_ASSERT_CF8ECB55_BCBD_4AE2_961C_54FDA7A77C11(n <= Arity);

#define EVENT_TRAITS_ARG(n, name) \
    EVENT_TRAITS_ARG_TYPED(n, detail::member_traits<EVENT_TRAITS_TYPEOF_CF8ECB55_BCBD_4AE2_961C_54FDA7A77C11(&EventType::name)>::type, name)

#define EVENT_TRAITS_DECL_END() }; \
 } } }


#define EVENT_TRAITS_0(event)  \
    EVENT_TRAITS_DECL_BEGIN(event, 0) \
    EVENT_TRAITS_DECL_END()

#define EVENT_TRAITS_1(event, p1)  \
    EVENT_TRAITS_DECL_BEGIN(event, 1) \
    EVENT_TRAITS_ARG(1, p1) \
    EVENT_TRAITS_DECL_END()

#define EVENT_TRAITS_2(event, p1, p2)  \
    EVENT_TRAITS_DECL_BEGIN(event, 2) \
    EVENT_TRAITS_ARG(1, p1) \
    EVENT_TRAITS_ARG(2, p2) \
    EVENT_TRAITS_DECL_END()

#define EVENT_TRAITS_3(event, p1, p2, p3)  \
    EVENT_TRAITS_DECL_BEGIN(event, 3) \
    EVENT_TRAITS_ARG(1, p1) \
    EVENT_TRAITS_ARG(2, p2) \
    EVENT_TRAITS_ARG(3, p3) \
    EVENT_TRAITS_DECL_END()

#define EVENT_TRAITS_4(event, p1, p2, p3, p4)  \
    EVENT_TRAITS_DECL_BEGIN(event, 4) \
    EVENT_TRAITS_ARG(1, p1) \
    EVENT_TRAITS_ARG(2, p2) \
    EVENT_TRAITS_ARG(3, p3) \
    EVENT_TRAITS_ARG(4, p4) \
    EVENT_TRAITS_DECL_END()

#define EVENT_TRAITS_5(event, p1, p2, p3, p4, p5)  \
    EVENT_TRAITS_DECL_BEGIN(event, 5) \
    EVENT_TRAITS_ARG(1, p1) \
    EVENT_TRAITS_ARG(2, p2) \
    EVENT_TRAITS_ARG(3, p3) \
    EVENT_TRAITS_ARG(4, p4) \
    EVENT_TRAITS_ARG(5, p5) \
    EVENT_TRAITS_DECL_END()

#define EVENT_TRAITS_6(event, p1, p2, p3, p4, p5, p6) \
    EVENT_TRAITS_DECL_BEGIN(event, 6) \
    EVENT_TRAITS_ARG(1, p1) \
    EVENT_TRAITS_ARG(2, p2) \
    EVENT_TRAITS_ARG(3, p3) \
    EVENT_TRAITS_ARG(4, p4) \
    EVENT_TRAITS_ARG(5, p5) \
    EVENT_TRAITS_ARG(6, p6) \
    EVENT_TRAITS_DECL_END()

#define EVENT_TRAITS_7(event, p1, p2, p3, p4, p5, p6, p7) \
    EVENT_TRAITS_DECL_BEGIN(event, 7) \
    EVENT_TRAITS_ARG(1, p1) \
    EVENT_TRAITS_ARG(2, p2) \
    EVENT_TRAITS_ARG(3, p3) \
    EVENT_TRAITS_ARG(4, p4) \
    EVENT_TRAITS_ARG(5, p5) \
    EVENT_TRAITS_ARG(6, p6) \
    EVENT_TRAITS_ARG(7, p7) \
    EVENT_TRAITS_DECL_END()

#define EVENT_TRAITS_8(event, p1, p2, p3, p4, p5, p6, p7, p8) \
    EVENT_TRAITS_DECL_BEGIN(event, 8) \
    EVENT_TRAITS_ARG(1, p1) \
    EVENT_TRAITS_ARG(2, p2) \
    EVENT_TRAITS_ARG(3, p3) \
    EVENT_TRAITS_ARG(4, p4) \
    EVENT_TRAITS_ARG(5, p5) \
    EVENT_TRAITS_ARG(6, p6) \
    EVENT_TRAITS_ARG(7, p7) \
    EVENT_TRAITS_ARG(8, p8) \
    EVENT_TRAITS_DECL_END()

#define EVENT_TRAITS_9(event, p1, p2, p3, p4, p5, p6, p7, p8, p9) \
    EVENT_TRAITS_DECL_BEGIN(event, 8) \
    EVENT_TRAITS_ARG(1, p1) \
    EVENT_TRAITS_ARG(2, p2) \
    EVENT_TRAITS_ARG(3, p3) \
    EVENT_TRAITS_ARG(4, p4) \
    EVENT_TRAITS_ARG(5, p5) \
    EVENT_TRAITS_ARG(6, p6) \
    EVENT_TRAITS_ARG(7, p7) \
    EVENT_TRAITS_ARG(8, p8) \
    EVENT_TRAITS_ARG(9, p9) \
    EVENT_TRAITS_DECL_END()

#define EVENT_TRAITS_10(event, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10) \
    EVENT_TRAITS_DECL_BEGIN(event, 8) \
    EVENT_TRAITS_ARG(1, p1) \
    EVENT_TRAITS_ARG(2, p2) \
    EVENT_TRAITS_ARG(3, p3) \
    EVENT_TRAITS_ARG(4, p4) \
    EVENT_TRAITS_ARG(5, p5) \
    EVENT_TRAITS_ARG(6, p6) \
    EVENT_TRAITS_ARG(7, p7) \
    EVENT_TRAITS_ARG(8, p8) \
    EVENT_TRAITS_ARG(9, p9) \
    EVENT_TRAITS_ARG(10, p10) \
    EVENT_TRAITS_DECL_END()

namespace original_boost_mt_core
{

    namespace helpers
    {

        namespace event_traits
        {

            // ArgCount
            // Arg1Type
            // Arg2Type
            // Arg3...
            template<typename Event>
            struct EventTraits;

            namespace detail {

                // member_traits

                template<typename Function> struct member_traits_helper;

                template<typename T, typename C>
                struct member_traits_helper<T (C::*)>
                {
                    typedef T type;
                    typedef C class_type;
                };

                template<typename Function>
                struct member_traits :
                    public member_traits_helper<Function>
                {
                };

                // traits_to_sig

                template<typename EventTraits, int Arity>
                struct traits_to_sig_helper;

                template<typename EventTraits>
                struct traits_to_sig: traits_to_sig_helper<EventTraits, EventTraits::Arity>
                {
                };


                #define TRAITS_TO_SIG_HELPER(z, n, data) \
                template<typename EventTraits> \
                struct traits_to_sig_helper<EventTraits, n> \
                { \
                    typedef void (signature)(BOOST_PP_ENUM_SHIFTED_PARAMS(BOOST_PP_INC(n), typename EventTraits::ArgType)); \
                };

                //TRAITS_TO_SIG_HELPER(~, 0, ~)
                #define BOOST_PP_LOCAL_MACRO(n)   TRAITS_TO_SIG_HELPER(~, n, ~)
                #define BOOST_PP_LOCAL_LIMITS     (0, EVENT_TRAITS_MAX_ARGS)
                #include BOOST_PP_LOCAL_ITERATE()

                template<typename Event>
                struct event_to_sig: traits_to_sig<EventTraits<Event> >
                {
                };

            }

            #define EVENT_TRAITS_SEND_X(z, n, data) \
            template<typename Event> \
            typename boost::enable_if_c<EventTraits<Event>::Arity == n, bool >::type send( \
              IOxfEventSender *dest BOOST_PP_COMMA_IF(n) BOOST_PP_ENUM_SHIFTED_BINARY_PARAMS(BOOST_PP_INC(n), typename EventTraits<Event>::ArgType, a)) \
            { \
                return dest->send(new Event(BOOST_PP_ENUM_SHIFTED_PARAMS(BOOST_PP_INC(n), a)), OMOSEventGenerationParams()); \
            }

            #define BOOST_PP_LOCAL_MACRO(n)   EVENT_TRAITS_SEND_X(~, n, ~)
            #define BOOST_PP_LOCAL_LIMITS     (0, EVENT_TRAITS_MAX_ARGS)
            #include BOOST_PP_LOCAL_ITERATE()

            template<typename T>
            struct MemberComparator 
            {
                typedef T Type;
                MemberComparator(const T &expected, const T &actual):mExpected(expected),mActual(actual) {}

                template<typename Result, Result Type::*Member>
                void memberCompare(boost::test_tools::predicate_result &result, const std::string &name) const
                {
                    memberCompare(result, name, mExpected.*Member, mActual.*Member);
                } 

                template<typename Result>
                static void memberCompare(boost::test_tools::predicate_result &result, const std::string &name, Result expected, Result actual)
                {
                    if(expected != actual)
                    {
                        result = false;
                        result.message() << "[expected " << expected << " != actual " << actual << "] " << "<- " << name << " ";
                    }
                }

                const Type &mExpected;
                const Type &mActual;
            };

        } // event_traits

    } // helpers

} // original_boost_mt_core

#define EVENT_TRAITS_ASSERT_EQUALS_COMPARE(z, n, data) \
    Comparator::memberCompare(result, EventTraits<Event>::getArgName ## n(), EventTraits<Event>::getArg ## n(*expected), EventTraits<Event>::getArg ## n(*actual));
      
#define EVENT_TRAITS_ASSERT_EQUALS(z, n, data) \
template<typename Event> \
boost::test_tools::predicate_result assertEquals(Event *expected, Event *actual, \
    typename boost::enable_if_c<original_boost_mt_core::helpers::event_traits::EventTraits<Event>::Arity == n>::type* dummy = 0) \
{ \
    using namespace original_boost_mt_core::helpers::event_traits; \
    boost::test_tools::predicate_result result = true; \
    typedef MemberComparator<Event> Comparator; \
    Comparator comparator(*expected, *actual); \
    BOOST_PP_REPEAT_FROM_TO(1, BOOST_PP_INC(n), EVENT_TRAITS_ASSERT_EQUALS_COMPARE, ~) \
    return result; \
}

#define BOOST_PP_LOCAL_MACRO(n)   EVENT_TRAITS_ASSERT_EQUALS(~, n, ~)
#define BOOST_PP_LOCAL_LIMITS     (1, EVENT_TRAITS_MAX_ARGS)
#include BOOST_PP_LOCAL_ITERATE()
#undef EVENT_TRAITS_ASSERT_EQUALS



// Pretty printing of received events

namespace original_boost_mt_core
{
    namespace helpers
    {
        namespace event_traits
        {
            struct EventParamsPrinter
            {
                struct IPerEventType {
                    virtual ~IPerEventType() {}
                    virtual void print(mock::stream& s, const IOxfEvent* t) const=0;
                };

                template<typename Event, int Arity>
                struct Reg;         

                #define EVENT_TRAITS_OPERATOR_SHIFT_FORMAT(z, n, data) \
                original_boost_mt_core::helpers::event_traits::EventTraits<Event>::formatArgForLog ## n (s, static_cast<const Event&>(*t)); \
                s <<  ", ";

                //mock::format( original_boost_mt_core::helpers::event_traits::EventTraits<Event>::getArg ## n (static_cast<const Event&>(*t)) ) << ", " <<

                #define EVENT_TRAITS_OPERATOR_SHIFT(z, n, data) \
                template<typename Event> \
                struct Reg<Event, n>: IPerEventType \
                { \
                    virtual void print(mock::stream& s, const IOxfEvent* t) const \
                    { \
                        s << original_boost_mt_core::helpers::event_traits::EventTraits<Event>::getName() \
                        << '(';  \
                        BOOST_PP_REPEAT_FROM_TO(1, BOOST_PP_INC(n), EVENT_TRAITS_OPERATOR_SHIFT_FORMAT, BOOST_PP_EMPTY) \
                        s << ')'; \
                    } \
                };

                #define BOOST_PP_LOCAL_MACRO(n)   EVENT_TRAITS_OPERATOR_SHIFT(~, n, ~)
                #define BOOST_PP_LOCAL_LIMITS     (0, EVENT_TRAITS_MAX_ARGS)
                #include BOOST_PP_LOCAL_ITERATE()

                #undef EVENT_TRAITS_OPERATOR_SHIFT_FORMAT
                #undef EVENT_TRAITS_OPERATOR_SHIFT

                void print(mock::stream& s, const IOxfEvent* t);

                template<typename Event>
                void registerEventType()
                {
                    eventTypes[typeid(Event).name()].reset(new Reg<Event, EventTraits<Event>::Arity>);
                }

                typedef std::map<std::string, boost::shared_ptr<IPerEventType> > EventTypes;
                EventTypes eventTypes;

                static EventParamsPrinter &getInstance();

            private:
                static boost::scoped_ptr<EventParamsPrinter> instance;

            private:
                EventParamsPrinter() {}
                void operator=(const EventParamsPrinter &);
            };

            template<typename Event>
            struct EventParamsPrinterRegistrator
            {
                EventParamsPrinterRegistrator(int arity):arity(arity)
                {
                    EventParamsPrinter::getInstance().registerEventType<Event>();
                }
                int const arity;
            };

            template<typename Event, size_t _ArgsCount>
            struct BaseEventTraits {
                BOOST_STATIC_CONSTANT(unsigned, Arity = _ArgsCount);
                static EventParamsPrinterRegistrator<Event> printerRegistrator;
            };

            template<typename Event, size_t _ArgsCount>
            EventParamsPrinterRegistrator<Event> BaseEventTraits<Event, _ArgsCount>::printerRegistrator(_ArgsCount);

            template<typename Event, int ArgNumber, typename Type>
            struct FormatForLog
            {
                void operator()(mock::stream &s, const Type &value)
                {
                    s << mock::format(value);
                }
            };

        } // event_traits

    } // helpers

} // original_boost_mt_core


namespace mock 
{ 
    inline mock::stream& operator<<(mock::stream& s, IOxfEvent* t)
    {
        original_boost_mt_core::helpers::event_traits::EventParamsPrinter::getInstance().print(s, t);
        return s;
    }
}

#endif //_EVENT_TRAITS_H_41D3D928_ADB7_46C8_B7B7_B9A4998E5AD2_
