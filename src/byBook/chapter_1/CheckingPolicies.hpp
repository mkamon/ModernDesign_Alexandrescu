#pragma once

#include <exception>
#include "CreatorPolicies.hpp"

namespace policy
{
    template <typename T> struct NoChecking
    {
        static void check(T *){}
    };
    template <typename T> struct EnforceNotNull
    {
        class NullPointerException : public std::exception {};
        static void check(T *ptr)
        {
            if( ptr == nullptr){
                throw NullPointerException();
            }
        }
    };
    template<typename T>
    struct EnsureNotNull
    {
        static void check(T *&ptr)
        {
            if( ptr == nullptr){
                ptr = getDefaultValue();
            }
        }

        static T *getDefaultValue()
        {
            return OpNewCreator<T>::create();
        }
    };

}


