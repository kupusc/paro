//
// Copyright Mathieu Champlon 2008
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://turtle.sf.net for documentation.

#ifndef MOCK_MOCK_HPP_INCLUDED
#define MOCK_MOCK_HPP_INCLUDED

#include "config.hpp"
#include "cleanup.hpp"
#include "object.hpp"
#include "function.hpp"
#include "args.hpp"
#include "type_name.hpp"
#include <boost/preprocessor/repetition/repeat.hpp>
#include <boost/preprocessor/stringize.hpp>
#include <boost/function_types/parameter_types.hpp>
#include <boost/function_types/function_type.hpp>
#include <boost/function_types/result_type.hpp>
#include <boost/mpl/joint_view.hpp>
#include <boost/mpl/single_view.hpp>
#include <boost/mpl/pop_front.hpp>
#define BOOST_TYPEOF_SILENT
#include <boost/typeof/typeof.hpp>
#include <boost/type_traits.hpp>

#include <boost/thread/recursive_mutex.hpp>
#include <boost/test/utils/trivial_singleton.hpp>

namespace mock
{
namespace detail
{
    template< typename M >
    struct signature :
        boost::function_types::function_type<
            boost::mpl::joint_view<
                boost::mpl::single_view<
                    BOOST_DEDUCED_TYPENAME
                        boost::function_types::result_type< M >::type
                >,
                BOOST_DEDUCED_TYPENAME boost::mpl::pop_front<
                    BOOST_DEDUCED_TYPENAME
                        boost::function_types::parameter_types< M >
                >::type
            >
        >
    {};

    template< typename T >
    struct base
    {
        typedef T base_type;
    };

    template< typename S >
    struct functor : mock::function< S >
    {
        functor()
        {
            static functor* f = 0;
            if( f )
            {
                *this = *f;
                f = 0;
            }
            else
                f = this;
        }
    };

    struct global_mock_lock_t: public boost::unit_test::singleton<global_mock_lock_t>
    {
        typedef boost::recursive_mutex mutex_type;

        mutex_type mMutex;

    private:
        friend class boost::unit_test::singleton<global_mock_lock_t>;

    };

    BOOST_TEST_SINGLETON_INST(global_mock_lock);

    template<typename F>
    struct global_mock_locker
    {
        global_mock_locker(F &function)
            :mF(function),mLock(new global_mock_lock_t::mutex_type::scoped_lock(global_mock_lock_t::instance().mMutex))
        {
        }

        F &get_functor()
        {
            return mF;
        }

    private:
        F &mF;
        boost::shared_ptr<global_mock_lock_t::mutex_type::scoped_lock> mLock;
    };

    template<typename Signature>
    struct global_mock_locker_holder: mock::function<Signature>
    {
        typedef typename mock::function<Signature>::result_type result_type;
        global_mock_locker_holder &get_functor()
        {
            return *this;
        }

        result_type operator()()
        {
            global_mock_lock_t::mutex_type::scoped_lock guard(global_mock_lock_t::instance().mMutex);
            return mock::function<Signature>::operator()();
        }

        #define MOCK_FUNCTION_OPERATOR(z, n, P) \
        MOCK_DECL(operator(), n, Signature, const, BOOST_DEDUCED_TYPENAME) \
        { \
            global_mock_lock_t::mutex_type::scoped_lock guard(global_mock_lock_t::instance().mMutex); \
            return mock::function<Signature>::operator()(BOOST_PP_ENUM_PARAMS(n, p)); \
        }

        BOOST_PP_REPEAT(
            BOOST_PP_INC(MOCK_MAX_ARGS),
            MOCK_FUNCTION_OPERATOR,
            BOOST_PP_EMPTY)

        #undef MOCK_FUNCTION_OPERATOR

        global_mock_locker_holder& operator()(detail::context& c, boost::unit_test::const_string instance)
        {
            global_mock_lock_t::mutex_type::scoped_lock guard(global_mock_lock_t::instance().mMutex);
            mock::function<Signature>::operator()(c, instance);
            return *this;
        }

    };

}

    // if an error is generated by the line below it means
    // the method is ambiguous : use MOCK_METHOD_EXT instead
    template< typename T >
    T& ambiguous_method_name_use_MOCK_METHOD_EXT_instead( const T& );
}

#define MOCK_BASE_CLASS(T, I) \
    struct T : I, mock::object, mock::detail::base< I >
#define MOCK_CLASS(T) \
    struct T : mock::object
#define MOCK_FUNCTOR(f, S) \
    mock::detail::global_mock_locker_holder<S> f, &f##_mock = f

#define MOCK_HELPER(t) \
    t##_mock( mock::detail::root, BOOST_PP_STRINGIZE(t) ).get_functor()
#define MOCK_ANONYMOUS_HELPER(t) \
    t##_mock( mock::detail::root, "?." ).get_functor()

#define MOCK_METHOD_HELPER(S, t) \
    mutable mock::function< S > t##_mock_; \
    mock::detail::global_mock_locker< mock::function< S > > t##_mock( \
        const mock::detail::context&, \
        boost::unit_test::const_string instance ) const \
    { \
        mock::detail::global_mock_locker< mock::function< S > > locker(t##_mock_); \
        mock::detail::configure( *this, t##_mock_, \
            instance.substr( 0, instance.rfind( BOOST_PP_STRINGIZE(t) ) ), \
            mock::detail::type_name( typeid( *this ) ), \
            BOOST_PP_STRINGIZE(t) ); \
        return locker; \
    }

#define MOCK_SIGNATURE(M) \
    mock::detail::signature< \
        BOOST_TYPEOF( \
            mock::ambiguous_method_name_use_MOCK_METHOD_EXT_instead( \
                &base_type::M ) ) \
    >::type

#define MOCK_METHOD_AUX(M, n, S, t, c, tpn) \
    MOCK_DECL(M, n, S, c, tpn) \
    { \
        return MOCK_ANONYMOUS_HELPER(t)( \
            BOOST_PP_ENUM_PARAMS(n, p) ); \
    }

#define MOCK_METHOD_EXT(M, n, S, t) \
    MOCK_METHOD_AUX(M, n, S, t,,) \
    MOCK_METHOD_AUX(M, n, S, t, const,) \
    MOCK_METHOD_HELPER(S, t)
#define MOCK_CONST_METHOD_EXT(M, n, S, t) \
    MOCK_METHOD_AUX(M, n, S, t, const,) \
    MOCK_METHOD_HELPER(S, t)
#define MOCK_NON_CONST_METHOD_EXT(M, n, S, t) \
    MOCK_METHOD_AUX(M, n, S, t,,) \
    MOCK_METHOD_HELPER(S, t)
#define MOCK_METHOD(M, n) \
    MOCK_METHOD_EXT(M, n, MOCK_SIGNATURE(M), M)

#define MOCK_METHOD_EXT_TPL(M, n, S, t) \
    MOCK_METHOD_AUX(M, n, S, t,, BOOST_DEDUCED_TYPENAME) \
    MOCK_METHOD_AUX(M, n, S, t, const, BOOST_DEDUCED_TYPENAME) \
    MOCK_METHOD_HELPER(S, t)
#define MOCK_CONST_METHOD_EXT_TPL(M, n, S, t) \
    MOCK_METHOD_AUX(M, n, S, t, const, BOOST_DEDUCED_TYPENAME) \
    MOCK_METHOD_HELPER(S, t)
#define MOCK_NON_CONST_METHOD_EXT_TPL(M, n, S, t) \
    MOCK_METHOD_AUX(M, n, S, t,, BOOST_DEDUCED_TYPENAME) \
    MOCK_METHOD_HELPER(S, t)

#define MOCK_CONST_CONVERSION_OPERATOR(T, t) \
    operator T() const { return MOCK_ANONYMOUS_HELPER(t)(); } \
    MOCK_METHOD_HELPER(T(), t)
#define MOCK_NON_CONST_CONVERSION_OPERATOR(T, t) \
    operator T() { return MOCK_ANONYMOUS_HELPER(t)(); } \
    MOCK_METHOD_HELPER(T(), t)
#define MOCK_CONVERSION_OPERATOR(T, t) \
    operator T() const { return MOCK_ANONYMOUS_HELPER(t)(); } \
    operator T() { return MOCK_ANONYMOUS_HELPER(t)(); } \
    MOCK_METHOD_HELPER(T(), t)

#define MOCK_FUNCTION_HELPER(S, t, s) \
    s mock::detail::global_mock_locker< mock::function< S > >& t##_mock( \
        mock::detail::context& context, \
        boost::unit_test::const_string instance ) \
    { \
        static mock::function< S > f; \
        mock::detail::global_mock_locker< mock::function< S > > locker(f( context, instance )); \
        return locker; \
    }

#define MOCK_CONSTRUCTOR_AUX(T, n, A, t, tpn) \
    MOCK_FUNCTION_HELPER(void A, t, static) \
    T( MOCK_ARGS(n, void A, tpn) ) \
    { \
        MOCK_HELPER(t)( BOOST_PP_ENUM_PARAMS(n, p) ); \
    }

#define MOCK_CONSTRUCTOR(T, n, A, t) \
    MOCK_CONSTRUCTOR_AUX(T, n, A, t,)
#define MOCK_CONSTRUCTOR_TPL(T, n, A, t) \
    MOCK_CONSTRUCTOR_AUX(T, n, A, t, BOOST_DEDUCED_TYPENAME)

#define MOCK_DESTRUCTOR(T, t) \
    ~T() { MOCK_ANONYMOUS_HELPER(t).test(); } \
    MOCK_METHOD_HELPER(void(), t)

#define MOCK_FUNCTION_AUX(F, n, S, t, s, tpn) \
    MOCK_FUNCTION_HELPER(S, t, s) \
    s MOCK_DECL(F, n, S,,tpn) \
    { \
        return MOCK_HELPER(t)( BOOST_PP_ENUM_PARAMS(n, p) ); \
    }
#define MOCK_FUNCTION(F, n, S, t) \
    MOCK_FUNCTION_AUX(F, n, S, t,,)
#define MOCK_STATIC_METHOD(F, n, S, t) \
    MOCK_FUNCTION_AUX(F, n, S, t, static,)
#define MOCK_STATIC_METHOD_TPL(F, n, S, t) \
    MOCK_FUNCTION_AUX(F, n, S, t, static, BOOST_DEDUCED_TYPENAME)

#define MOCK_EXPECT(t) MOCK_HELPER(t).expect( __FILE__, __LINE__ )
#define MOCK_RESET(t) MOCK_HELPER(t).reset( __FILE__, __LINE__ )
#define MOCK_VERIFY(t) MOCK_HELPER(t).verify( __FILE__, __LINE__ )

#endif // MOCK_MOCK_HPP_INCLUDED