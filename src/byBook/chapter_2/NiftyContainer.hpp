#pragma once
#include "MapToType.hpp"
#include "Select.hpp"

namespace typeSpecialization
{

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
