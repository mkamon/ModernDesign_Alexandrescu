#pragma once


    template<bool>
    struct CompileTimeChecker
    {
        CompileTimeChecker(...);
    };

    template<> struct CompileTimeChecker<false> {};

    #define STATIC_CHECK(expr, msg) \
        {\
            class ERROR_##msg {}; \
            (void)sizeof(CompileTimeChecker< (expr) != 0 >(( ERROR_##msg() )));\
        }

namespace ctassert
{

    template<typename To, typename From>
    To safe_reinterpret_cast(From from) {
        static_assert(sizeof(From) <= sizeof(To));
        return reinterpret_cast<To>(from);
    }

    template<typename To, typename From>
    To safe_reinterpret_cast_with_msg(From from) {
        STATIC_CHECK(sizeof(From) <= sizeof(To),
            Destitation_Type_Too_Narrow);
        return reinterpret_cast<To>(from);
    }
    
}