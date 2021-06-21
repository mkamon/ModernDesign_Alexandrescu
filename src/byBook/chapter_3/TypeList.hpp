#pragma once

#include "chapter_2/NullType.hpp"

template <typename T, typename U>
struct TypeList
{
    using Head = T;
    using Tail = U;
};

#define TYPELIST_1(T1) TypeList<T1, NullType>
#define TYPELIST_2(T1, T2) TypeList< T1, TYPELIST_1(T2) >
#define TYPELIST_3(T1, T2, T3) TypeList< T1, TYPELIST_2(T2, T3) >
#define TYPELIST_4(T1, T2, T3, T4) TypeList< T1, TYPELIST_3(T2, T3, T4) >
#define TYPELIST_5(T1, T2, T3, T4, T5) TypeList< T1, TYPELIST_4(T2, T3, T4, T5) >
#define TYPELIST_6(T1, T2, T3, T4, T5, T6) TypeList< T1, TYPELIST_5(T2, T3, T4, T5, T6) >
#define TYPELIST_7(T1, T2, T3, T4, T5, T6, T7) TypeList< T1, TYPELIST_6(T2, T3, T4, T5, T6, T7) >
#define TYPELIST_8(T1, T2, T3, T4, T5, T6, T7, T8) TypeList< T1, TYPELIST_7(T2, T3, T4, T5, T6, T7, T8) >
#define TYPELIST_9(T1, T2, T3, T4, T5, T6, T7, T8, T9) TypeList< T1, TYPELIST_8(T2, T3, T4, T5, T6, T7, T8, T9) >
#define TYPELIST_10(T1, T2, T3, T4, T5, T6, T7, T8, T9, T10) TypeList< T1, TYPELIST_9(T2, T3, T4, T5, T6, T7, T8, T9, T10) >

namespace TL
{
    /////////////// Length /////////////

    template <typename TList> 
    struct Length;
    
    template <>
    struct Length<NullType>
    {
        enum { value = 0 };
    };

    template <class T, class U>
    struct Length<TypeList<T,U>>
    {
        enum { value = 1 + Length<U>::value };
    };

    /////////////// TypeAt /////////////

    template <typename TList, unsigned index>
    struct TypeAt;

    template <typename Head, typename Tail>
    struct TypeAt<TypeList<Head, Tail>, 0>
    {
        using Result = Head;
    };
    
    template <typename Head, typename Tail, unsigned index>
    struct TypeAt<TypeList<Head, Tail>, index>
    {
        using Result = typename TypeAt<Tail, index - 1>::Result; 
    };

    /////////////// Appending to TypeList /////////////

    template <typename TList, typename T>
    struct Append;

    template <>
    struct Append<NullType, NullType>
    {
        using Result = NullType;
    };

    template <typename T>
    struct Append<NullType, T>
    {
        using Result = TYPELIST_1(T);
    };

    template <typename Head, typename Tail>
    struct Append<NullType, TypeList<Head, Tail>>
    {
        using Result = TypeList<Head, Tail>;
    };

    template <typename Head, typename Tail, typename T>
    struct Append<TypeList<Head,Tail>, T>
    {
        using Result =  TypeList< Head,
            typename Append<Tail, T>::Result >;
    };

    /////////////// Erasing Type from a TypeList /////////////

    template <typename TList, typename T>
    struct Erase;

    template <typename T>
    struct Erase<NullType, T>
    {
        using Result = NullType;
    };

    template <typename Head, typename Tail>
    struct Erase<TypeList<Head, Tail>, Head>
    {
        using Result = Tail;
    };

    template <typename Head, typename Tail, typename T>
    struct Erase<TypeList<Head, Tail>, T>
    {
        using Result = TypeList<Head, typename Erase<Tail, T>::Result>;
    };
}
