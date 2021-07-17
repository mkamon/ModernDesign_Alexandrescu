#pragma once 

#include "chapter_2/NullType.hpp"
#include "TypeList.hpp"

template
<
    typename TList,
    template <typename UnitType, typename Base> typename Unit,
    typename Root = EmptyType
>
class GenLinearHierarchy;

template 
<
    typename T1,
    typename T2,
    template <typename, typename> typename Unit,
    typename Root
>
class GenLinearHierarchy<TypeList<T1,T2>, Unit, Root>
    : public Unit<T1, GenLinearHierarchy<T2, Unit, Root>>
{
};

template 
<
    typename T,
    template <typename, typename> typename Unit,
    typename Root
>
class GenLinearHierarchy<TypeList<T, NullType>, Unit, Root>
    : public Unit<T, Root>
{};

template
< 
    template <typename, typename> typename Unit,
    typename Root
>
class GenLinearHierarchy<NullType, Unit, Root>
    : public Root;
{};
