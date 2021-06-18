#include <gtest/gtest.h>

#include "chapter_2/TypeTraits.hpp"
#include "Widgets/ExampleWidgets.hpp"

TEST(TypeTraitsTest, pointerTraitShouldDetectPointerTypeForPointerType)
{
    //given
    using AliasedType = widgets::ConcreteWidget *;
    //when
    constexpr bool isPointerType = typeSpecialization::PointerTypeTrait<AliasedType>::isPointer;
    //then
    ASSERT_EQ(true, isPointerType); 
}

TEST(TypeTraitsTest, pointerTraitShouldNotDetectPointerTypeForNonpointerType)
{
    //given
    using AliasedType = widgets::ConcreteWidget;
    //when
    constexpr bool isPointerType = typeSpecialization::PointerTypeTrait<AliasedType>::isPointer;
    //then
    ASSERT_EQ(false, isPointerType); 
}

struct ClassWrapper
{
    widgets::ConcreteWidget wrapped();
};

TEST(TypeTraitsTest, pointerToMemberTraitShouldDetectPointerTypeForPointerToMemberType)
{
    //given
    using AliasedMember = widgets::ConcreteWidget (ClassWrapper::*)();
    //when
    constexpr bool isPointerType = typeSpecialization::PointerToMemberTypeTrait<AliasedMember>::isMemberPointer;
    //then
    ASSERT_EQ(true, isPointerType); 
}

TEST(TypeTraitsTest, pointerToMemberTraitShouldNotDetectPointerTypeRawPointerType)
{
    //given
    using AliasedType = widgets::ConcreteWidget *;
    //when
    constexpr bool isPointerType = typeSpecialization::PointerToMemberTypeTrait<AliasedType>::isMemberPointer;
    //then
    ASSERT_EQ(false, isPointerType); 
}
