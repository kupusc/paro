#ifndef _MAKE_EVENT_RESPONSE_C3440E56_38EA_4B7C_84C_B0834CE5DE0B_
#define _MAKE_EVENT_RESPONSE_C3440E56_38EA_4B7C_84C_B0834CE5DE0B_

#include <boost/preprocessor.hpp>
#include <IOxfEventSender.h>
#include <turtle/mock.hpp>
#include <boost/static_assert.hpp>
#include <boost/type_traits/function_traits.hpp>
#include <original_boost_mt_core/helpers/EventTraits.h>
#include <deque> //for StoperCascade
#include <IOxfEvent.h>
#include <boost/scoped_ptr.hpp>
#include <boost/shared_ptr.hpp>

namespace original_boost_mt_core
{
    namespace helpers
    {

        // ResponseSuccession

        namespace detail 
        {
            template<typename Signature, int Arity>
            struct ResponseSuccessionHelper;

            #define RESPONSE_SUCCESSION_HELPER(z, n, data) \
            template<typename Signature> \
            struct ResponseSuccessionHelper<Signature, n> \
            { \
                typedef boost::function<Signature> Function; \
                BOOST_PP_IF(n, template< , ) BOOST_PP_ENUM_PARAMS(n, typename A) BOOST_PP_IF(n, >, ) \
                void operator()(BOOST_PP_ENUM_BINARY_PARAMS(n, A, a)) \
                { \
                    for(typename std::deque<Function>::iterator i = mCalls.begin(); mCalls.end() != i; ++i) \
                    { \
                        (*i)(BOOST_PP_ENUM_PARAMS(n, a)); \
                    } \
                } \
                std::deque<Function> mCalls; \
            };

            #define BOOST_PP_LOCAL_MACRO(n)   RESPONSE_SUCCESSION_HELPER(~, n, ~)
            #define BOOST_PP_LOCAL_LIMITS     (0, EVENT_TRAITS_MAX_ARGS)
            #include BOOST_PP_LOCAL_ITERATE()

            #undef RESPONSE_SUCCESSION_HELPER

        }

        template<typename Event>
        struct ResponseSuccession: detail::ResponseSuccessionHelper<typename event_traits::detail::event_to_sig<Event>::signature, event_traits::EventTraits<Event>::Arity >
        {
        };

        template<typename Event>
        inline ResponseSuccession<Event> &operator<<(const ResponseSuccession<Event>& other, typename ResponseSuccession<Event>::Function call)
        {
            const_cast<ResponseSuccession<Event>& >(other).mCalls.push_back(call);
            return const_cast<ResponseSuccession<Event>& >(other);
        }

        inline bool deleteEv(IOxfEvent *ev)
        {
            delete ev;
            return true;
        }

        template<typename T>
        boost::function<bool(IOxfEvent* ev, const IOxfEventGenerationParams& params)> makeDeleteEv(T t)
        {
            return boost::bind(&deleteEv, t);
        }

        namespace detail {

            struct IEventToArgsConstraint
            {
                virtual ~IEventToArgsConstraint() {}        

                virtual bool check(const IOxfEvent* actual)=0;

                virtual void print(std::ostream& stream) const=0;
            };

            struct EventToArgsConstraintHolder
            {
                EventToArgsConstraintHolder(std::auto_ptr<IEventToArgsConstraint> impl):impl(impl.release()) {}

                friend bool operator==(const IOxfEvent* actual, const EventToArgsConstraintHolder& c)
                { 
                    return c.impl->check(actual);
                }
                friend std::ostream& operator<<(std::ostream& s, const EventToArgsConstraintHolder& c )
                {
                    c.impl->print(s);
                    return s;
                }

                boost::shared_ptr<IEventToArgsConstraint> impl;
            };

            template <class EventType, int _Arity>
            struct EventToArgsConstraintBase;

            #define EVENT_TO_ARGS_ARG(z, n, data) \
            , event_traits::EventTraits<ExpectedType>::getArg ## n(actual)
                
            #define EVENT_TO_ARGS_PASS_ARGS(z, n, data) \
            template <class EventType> \
            struct EventToArgsConstraintBase<EventType, n> { \
                static const int Arity = n; \
                typedef EventType ExpectedType; \
                typedef mock::detail::expectation<typename event_traits::detail::event_to_sig<ExpectedType>::signature, Arity> Expectation; \
                Expectation expectation; \
                bool checkValid(const ExpectedType &actual) \
                { \
                    return expectation.is_valid BOOST_PP_IF(n, (event_traits::EventTraits<ExpectedType>::getArg1(actual) BOOST_PP_REPEAT_FROM_TO(2, BOOST_PP_INC(n), EVENT_TO_ARGS_ARG, BOOST_PP_EMPTY)), ()) ; \
                } \
                void callFunctor(const ExpectedType &actual) \
                { \
                    expectation.functor() BOOST_PP_IF(n, (event_traits::EventTraits<ExpectedType>::getArg1(actual) BOOST_PP_REPEAT_FROM_TO(2, BOOST_PP_INC(n), EVENT_TO_ARGS_ARG, BOOST_PP_EMPTY)), ()) ; \
                } \
            };

            #define BOOST_PP_LOCAL_MACRO(n)   EVENT_TO_ARGS_PASS_ARGS(~, n, ~)
            #define BOOST_PP_LOCAL_LIMITS     (0, EVENT_TRAITS_MAX_ARGS)
            #include BOOST_PP_LOCAL_ITERATE()

            #undef EVENT_TO_ARGS_ARG
            #undef EVENT_TO_ARGS_PASS_ARGS

            template <class eventType>
            struct EventToArgsConstraint: IEventToArgsConstraint, EventToArgsConstraintBase<eventType, event_traits::EventTraits<eventType>::Arity>
            {
                typedef eventType ExpectedType;
                typedef EventToArgsConstraint<ExpectedType> OwnType;
                mutable boost::test_tools::predicate_result res;

                EventToArgsConstraint():res(true){}
                ~EventToArgsConstraint(){}

                virtual bool check(const IOxfEvent* actual)
                { 
                    const ExpectedType* casted = dynamic_cast<const ExpectedType*>(actual);
                    if(!casted)
                    {
                        res.message() << "[expected (" << typeid(ExpectedType).name() << ")"
                            << " != actual: " << mock::format(actual)  << " (" << typeid(*actual).name() << ") ] ";
                        return false;
                    }

                    bool result = checkValid(*casted);
                    if(result)
                    {
                        if( ! this->expectation.invoke() ) 
                        {
                            mock::MOCK_ERROR_POLICY<bool>::sequence_failed(
                                boost::unit_test::lazy_ostream::instance() << "EventToArgsConstraint", 
                                this->expectation.file(), this->expectation.line());
                            return false;
                        }

                        if( ! this->expectation.functor() )
                        {
                            mock::MOCK_ERROR_POLICY<bool>::missing_action(
                                boost::unit_test::lazy_ostream::instance() << "EventToArgsConstraint", 
                                this->expectation.file(), this->expectation.line());
                            return false;
                        }
                        callFunctor(*casted);
                        mEvents.push_back(boost::shared_ptr<IOxfEvent const>(actual));
                    }

                    return result;
                }
                virtual void print(std::ostream& stream) const
                {
                    stream << "Event " << event_traits::EventTraits<ExpectedType>::getName() << " to args{" << this->expectation << "}";
                }

                std::deque<boost::shared_ptr<IOxfEvent const> > mEvents;
            };

            struct IMakeMockExpectSendInvocationSelect
            {
                virtual ~IMakeMockExpectSendInvocationSelect() {}
                virtual void once()=0;
                virtual void never()=0;
                virtual void exactly(std::size_t count)=0;
                virtual void at_least(std::size_t min)=0;
                virtual void at_most(std::size_t max)=0;
                virtual void between(std::size_t min, std::size_t max)=0;

            };

            template<typename HostExpectation>
            struct MakeMockExpectSendInvocationSelectSpec: IMakeMockExpectSendInvocationSelect
            {
                MakeMockExpectSendInvocationSelectSpec(HostExpectation &expectation):mExpectation(expectation) 
                {
                    mExpectation.returns(true);    
                }

                virtual void once()
                {
                    mExpectation.once();    
                }

                virtual void never()
                {
                    mExpectation.never();
                }

                virtual void exactly(std::size_t count)
                {
                    mExpectation.exactly(count);
                }

                virtual void at_least(std::size_t min)
                {
                    mExpectation.at_least(min);
                }

                virtual void at_most(std::size_t max)
                {
                    mExpectation.at_most(max);
                }
                
                virtual void between(std::size_t min, std::size_t max)
                {
                    mExpectation.between(min, max);
                }

                HostExpectation &mExpectation;
            };

            template<typename HostExpectation>
            std::auto_ptr<IMakeMockExpectSendInvocationSelect> makeMakeMockExpectSendInvocationSelectSpec(HostExpectation &expectation)
            {
                std::auto_ptr<IMakeMockExpectSendInvocationSelect> result(new MakeMockExpectSendInvocationSelectSpec<HostExpectation>(expectation));
                return result;
            }

            // Needed so that invocation selection can be passed to host expectation
            template<typename Event>
            struct MakeMockExpectSendInvocationSelect {
                typedef typename EventToArgsConstraint<Event>::Expectation Expectation;

                MakeMockExpectSendInvocationSelect(Expectation &expectation, 
                    std::auto_ptr<IMakeMockExpectSendInvocationSelect> impl):mExpectation(expectation),mImpl(impl.release()) {}

                Expectation &unlimited()
                {
                    return mExpectation;
                }

                Expectation &once()
                {
                    mImpl->once();
                    mExpectation.once(); //TODO: to resolve, should both host and client expectation be set, or just host?
                    return mExpectation;
                }

                Expectation &never()
                {
                    mImpl->never();
                    mExpectation.never();
                    return mExpectation;
                }

                Expectation &exactly(std::size_t count)
                {
                    mImpl->exactly(count);
                    mExpectation.exactly(count);
                    return mExpectation;
                }

                Expectation &at_least(std::size_t min)
                {
                    mImpl->at_least(min);
                    mExpectation.at_least(min);
                    return mExpectation;
                }

                Expectation &at_most(std::size_t max)
                {
                    mImpl->at_most(max);
                    mExpectation.at_most(max);
                    return mExpectation;
                }
                
                Expectation &between(std::size_t min, std::size_t max)
                {
                    mImpl->between(min, max);
                    mExpectation.between(min, max);
                    return mExpectation;
                }

            private:
                Expectation &mExpectation;
                boost::shared_ptr<IMakeMockExpectSendInvocationSelect> mImpl;
            };            

            template<typename Event, typename Object>
            MakeMockExpectSendInvocationSelect<Event> makeMockExpectSend(const Object &object, const std::string &file, int line)
            {
                EventToArgsConstraint<Event> *blah(new EventToArgsConstraint<Event>());
                blah->expectation.set_location(file.c_str(), line);
                std::auto_ptr<IEventToArgsConstraint> testConstraint(blah);
                std::auto_ptr<IMakeMockExpectSendInvocationSelect> impl(
                    makeMakeMockExpectSendInvocationSelectSpec(MOCK_HELPER(object.send).expect(file.c_str(), line)
                    .with(EventToArgsConstraintHolder(testConstraint), mock::any)));               
                return MakeMockExpectSendInvocationSelect<Event>(blah->expectation, impl);
            }

        }

    }

}

/*! Allows expecting events just like regular functions - instead of using comparator
  one can setup per argument expectations.
 * Only events registered previously with EVENT_TRAITS can be used this way.
 * 
 * Example:
 * OBMC_MOCK_EXPECT_SEND(omrMock, evExampleEvent).once().with(mock::any, 3, "4").calls(boost::bind(mockFunctor, _2, _3));
 * \warning Contrary to IOxfEventSender::send .returns(true); at the end of invocation is not needed.
 * \param object Mock object that has send function
 * \param event Type of event
 * \sa EVENT_TRAITS_0
 */
#define OBMC_MOCK_EXPECT_SEND(object, event) ::original_boost_mt_core::helpers::detail::makeMockExpectSend<event>(object, __FILE__, __LINE__)


#endif //_MAKE_EVENT_RESPONSE_C3440E56_38EA_4B7C_84C_B0834CE5DE0B_
