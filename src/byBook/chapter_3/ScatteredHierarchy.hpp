#pragma once
#include "chapter_2/NullType.hpp"
#include "chapter_3/TypeList.hpp"

template <typename TList, template <typename> typename Unit>
class GenScatterHierarchy;

template <typename T1, typename T2, template <typename> typename Unit>
class GenScatterHierarchy<TypeList<T1,T2>, Unit>
    : public GenScatterHierarchy<T1, Unit>
    , public GenScatterHierarchy<T2, Unit>
{
    using TList = TypeList<T1, T2>;
    using LeftBase = GenScatterHierarchy<T1, Unit>;
    using RightBase = GenScatterHierarchy<T2, Unit>;
};

template <typename NonListType, template <typename> typename Unit>
class GenScatterHierarchy : public Unit<NonListType>
{
    using LeftBase = Unit<NonListType>;
} ;

template <template <typename> typename Unit>
class GenScatterHierarchy<NullType, Unit>
{};
