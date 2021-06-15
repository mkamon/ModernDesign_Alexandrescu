#pragma once
#include "MapToType.hpp"

namespace typeSpecialization
{
    template <typename T, bool isPolimorphic>
    class NiftyContainer
    {

        T *create(T *someObj, IntToType<false>)
        {
            return new T(*someObj);
        }
        T *create(T *someObj, IntToType<true>)
        {
            return someObj->clone();
        }
    public:
        T *create(T *someObj) 
        {
            return create(someObj, IntToType<isPolimorphic>());
        }
    };
}
