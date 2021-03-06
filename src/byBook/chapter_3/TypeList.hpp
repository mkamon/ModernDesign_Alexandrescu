#pragma once

#include "chapter_2/NullType.hpp"
#include "chapter_2/Select.hpp"
#include "chapter_2/Conversion.hpp"

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

    /////////////// TypeAtNonStrict /////////////

    template <typename TList, unsigned index, typename Other>
    struct TypeAtNonStrict;
    
    template <unsigned index, typename FallbackType >
    struct TypeAtNonStrict<NullType, index, FallbackType>
    {
        using Result = FallbackType;
    };

    template <typename Head, typename Tail, typename FallbackType>
    struct TypeAtNonStrict<TypeList<Head, Tail>, 0, FallbackType>
    {
        using Result = Head;
    };
    
    template <typename Head, typename Tail, unsigned index, typename FallbackType>
    struct TypeAtNonStrict<TypeList<Head, Tail>, index, FallbackType>
    {
        using Result = typename TypeAtNonStrict<Tail, index - 1, FallbackType>::Result; 
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

    /////////////// Erasing All occurences of a Type from a TypeList /////////////

    template <typename TList, typename T>
    struct EraseAll;

    template <typename T>
    struct EraseAll<NullType, T>
    {
        using Result = NullType;
    };

    template <typename T, typename Tail>
    struct EraseAll<TypeList<T, Tail>, T>
    {
        using Result = typename EraseAll<Tail, T>::Result;
    };

    template <typename Head, typename Tail, typename T>
    struct EraseAll<TypeList<Head, Tail>, T>
    {
        using Result = TypeList<Head, typename EraseAll<Tail, T>::Result>;
    };
    
    /////////////// Erasing duplicates from a TypeList /////////////

    template <typename TList>
    struct NoDuplicates;

    template <>
    struct NoDuplicates<NullType>
    {
        using Result = NullType;
    };

    template <typename Head, typename Tail>
    struct NoDuplicates<TypeList<Head, Tail>>
    {
    private:
        using L1 = typename NoDuplicates<Tail>::Result;
        using L2 = typename Erase<L1, Head>::Result;
    public:
       using Result = TypeList<Head, L2>;
    };

    /////////////// Replacing an Element in a TypeList /////////////

    template <typename TList, typename T, typename U>
    struct Replace;

    template <typename T, typename U>
    struct Replace<NullType, T, U>
    {
        using Result = NullType;
    };

    template <typename T, typename Tail, typename U>
    struct Replace<TypeList<T, Tail>, T, U>
    {
        using Result = TypeList<U, Tail>;
    };

    template <typename Head, typename Tail,typename T, typename U>
    struct Replace<TypeList<Head, Tail>, T, U>
    {
        using Result = TypeList<Head, typename Replace<Tail, T, U>::Result>;
    };

    /////////////// Partial sorting of a TypeList by inheritance hierarchy /////////////

    template <typename TList, typename Base>
    struct MostDerived;

    template <typename Base>
    struct MostDerived<NullType, Base>
    {
        using Result = Base;
    };

    template <typename Head, typename Tail, typename Base>
    struct MostDerived<TypeList<Head, Tail>, Base>
    {
    private:
        using Candidate = typename MostDerived<Tail, Base>::Result;
        static constexpr bool isHeadAChild = SUPERSUBCLASS(Candidate, Head);
    public:
        using Result = typename Select< isHeadAChild, Head, Candidate>::Result;
    };

    template <typename TList>
    struct DerivedToFront;

    template <>
    struct DerivedToFront<NullType>
    {
        using Result = NullType;
    };

    template <typename Head, typename Tail>
    struct DerivedToFront<TypeList<Head, Tail>>
    {
    private:
        using TheMostDerived = typename MostDerived<Tail, Head>::Result;
        using L = typename Replace<Tail, TheMostDerived, Head>::Result;
    public:
        using Result = TypeList<TheMostDerived, L>;
    };
}
