#include <gtest/gtest.h>

#include "chapter_2/Conversion.hpp"
#include "Widgets/ExampleWidgets.hpp"

TEST(ConversionTest, conversionExistsInDownWidgetInheritanceHierarchy)
{
    //given 
    using SameTypeConversion = typeSpecialization::Conversion<widgets::CloneableWidget, widgets::ConcreteWidget>;
    //when
    constexpr bool converts = SameTypeConversion::exists;
    constexpr bool sameType = SameTypeConversion::sameType;
    //then 
    ASSERT_EQ(true, converts);
    ASSERT_EQ(false, sameType);
}

TEST(ConversionTest, conversionNotExistInUpWidgetInheritanceHierarchy)
{
    //given & when
    constexpr bool converts = typeSpecialization::Conversion<widgets::ConcreteWidget, widgets::CloneableWidget >::exists;
    //then 
    ASSERT_EQ(false, converts);
}

TEST(ConversionTest, sameTypeDetectedInWidgetInheritanceHierarchy)
{
    //given
    using SameTypeConversion = typeSpecialization::Conversion<widgets::CloneableWidget, widgets::CloneableWidget >;
    //when
    constexpr bool converts = SameTypeConversion::exists;
    constexpr bool sameType = SameTypeConversion::sameType;
    //then 
    ASSERT_EQ(true, converts);
    ASSERT_EQ(true, sameType);
}

TEST(ConversionTest, detectSuperSubClassInWidgetInheritanceHierarchy)
{
    //given & when
    constexpr bool isSuperClass = SUPERSUBCLASS(widgets::ConcreteWidget, widgets::CloneableWidget );
    //then 
    ASSERT_EQ(true, isSuperClass);
}

TEST(ConversionTest, voidIsNotSuperClass)
{
    //given & when
    constexpr bool isSuperClass = SUPERSUBCLASS(void, widgets::CloneableWidget );
    //then 
    ASSERT_EQ(false, isSuperClass);
}
