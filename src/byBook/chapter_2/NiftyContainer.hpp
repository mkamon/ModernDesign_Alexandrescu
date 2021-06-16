#pragma once
#include "MapToType.hpp"

namespace typeSpecialization
{

    template <bool flag, typename T, typename U>
    struct Select
    {
        using Result = T;
    };

    template <typename T, typename U>
    struct Select<false, T, U>
    {
        using Result = U;
    };

    template <typename T, bool isPolimorphic>
    class NiftyContainer
    {
        using ValueType = typename Select<isPolimorphic, T*, T>::Result;

        T create(T *someObj, IntToType<false>)
        {
            return T(*someObj);
        }
        T *create(T *someObj, IntToType<true>)
        {
            return someObj->clone();
        }
    public:
        ValueType create(T *someObj) 
        {
            return create(someObj, IntToType<isPolimorphic>());
        }
    };
}
