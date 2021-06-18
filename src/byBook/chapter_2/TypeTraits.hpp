#pragma once

#include "NullType.hpp"

namespace typeSpecialization
{
    /** PointerTypeTrait is a template class that allows to 
     * discriminate between pointer and non-pointer types
     * in compile time. By the language type deduction rules
     * specialization `U*` will always be better match for
     * pointer types than `U`
    **/   
    template< typename T>
    class PointerTypeTrait
    {
        template <typename U> 
        struct PointerTraits
        {
            enum {result = false};
            using PointeeType = NullType;
        };
        template <typename U>
        struct PointerTraits<U*>
        {
            enum {result = true};
            using PointeeType = U;
        };
    public:
        enum {isPointer = PointerTraits<T>::result};
        using PointeeType = typename PointerTraits<T>::PointeeType;
    };

    /** PointerToMemberTypeTrait is a template class that allows to
     * discriminate between pointers to member and other types. 
    **/
    template <typename T>
    class PointerToMemberTypeTrait
    {
        template <typename U> 
        struct PToMTraits
        {
            enum {result = false};
        };
        template <typename U, typename V>
        struct PToMTraits<U V::*>
        {
            enum {result = true};
        };
    public:
        enum {isMemberPointer = PToMTraits<T>::result};
    };
}
