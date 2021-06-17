#pragma once 

namespace typeSpecialization
{

    template <typename From, typename To>
    class Conversion
    {
        using Small = char;
        class Big {char _[2];};

        static Small test(To);
        static Big test(...);
        static From makeFrom();

    public:
        enum {exists = sizeof(test(makeFrom())) == sizeof(Small)};
        enum {sameType = false};
    };

    template <typename T>
    class Conversion<T, T>
    {
    public:
        enum {exists = true, sameType = true};
    };

}
#define SUPERSUBCLASS(T, U) \
    (typeSpecialization::Conversion<const U*, const T*>::exists && \
    !typeSpecialization::Conversion<const T*, const void*>::sameType)
