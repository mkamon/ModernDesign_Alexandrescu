#pragma once
#include "chapter_2/NullType.hpp"
#include "chapter_3/TypeList.hpp"
#include "chapter_2/MapToType.hpp"

namespace Private 
{
    template <typename, typename>
    struct ScatterHierarchyTag;
}

template <typename TList, template <typename> typename Unit>
class GenScatterHierarchy;

template <typename T1, typename T2, template <typename> typename Unit>
class GenScatterHierarchy<TypeList<T1,T2>, Unit>
    : public GenScatterHierarchy<Private::ScatterHierarchyTag<T1, T2>, Unit>
    , public GenScatterHierarchy<T2, Unit>
{
public:
    using TList = TypeList<T1, T2>;
    using LeftBase = GenScatterHierarchy<Private::ScatterHierarchyTag<T1, T2>, Unit>;
    using RightBase = GenScatterHierarchy<T2, Unit>;
    template <typename T> 
    struct Rebind
    {
        using Result = Unit<T>;
    };
};

template <typename T1, typename T2, template <typename> typename Unit>
class GenScatterHierarchy<Private::ScatterHierarchyTag<T1, T2>, Unit>
    : public GenScatterHierarchy<T1, Unit>
{};

template <typename NonListType, template <typename> typename Unit>
class GenScatterHierarchy : public Unit<NonListType>
{
    using LeftBase = Unit<NonListType>;

    template <typename T> 
    struct Rebind
    {
        using Result = Unit<T>;
    };
} ;

template <template <typename> typename Unit>
class GenScatterHierarchy<NullType, Unit>
{
    template <typename T> 
    struct Rebind
    {
        using Result = Unit<T>;
    };
};

// Field access to a object genrated wiht GenScatteredHierarchy

template <typename T, typename H>
typename H::template Rebind<T>::Result &Field(H &scatterObj)
{
    return scatterObj;
};

// template <typename T, typename H>
// const typename H::template Rebind<T>::Result &Field(const H &scatterObj)
// {
//     return scatterObj;
// };

template <typename H, unsigned int i>
struct FieldHelper;

template <typename H>
struct FieldHelper<H, 0>
{
    using ElementType = typename H::TList::Head;
    using UnitType = typename H::template Rebind<ElementType>::Result;
    using LeftBase = typename H::LeftBase;
    
    static UnitType &Do(H &obj)
    {
        LeftBase & leftBase = obj;
        return leftBase;
    };
};

template <typename H, unsigned int i>
struct FieldHelper
{
    using ElementType = typename TL::TypeAt<typename H::TList, i>::Result;
    using UnitType = typename H::template Rebind<ElementType>::Result;
    using RightBase = typename H::RightBase;

    static UnitType &Do(H &obj)
    {
        RightBase &rightBase = obj;
        return FieldHelper<RightBase, i - 1>::Do(rightBase);
    };
};

template <int i, typename H>
typename FieldHelper<H, i>::UnitType &
Field(H &obj)
{
    return FieldHelper<H, i>::Do(obj);
};





