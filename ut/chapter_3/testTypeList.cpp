#include <gtest/gtest.h>

#include "chapter_3/TypeList.hpp"
#include "chapter_3/SpecialTypeLists.hpp"
#include "Widgets/ExampleWidgets.hpp"


TEST(TypeListTest, typeListLengthCalculationTest)
{
    //given
    using TestTypeList = TYPELIST_5(widgets::ConcreteWidget,int,unsigned, char, widgets::CloneableWidget);    
    constexpr auto expectedTypeListLength = 5;
    //when
    constexpr auto length = TL::Length<TestTypeList>::value;
    //then
    ASSERT_EQ(expectedTypeListLength, length); 
    
}

TEST(TypeListTest, typeListTypeAtIndexShouldReturnConcreteWidget)
{
    //given
    using TestTypeList = TYPELIST_6(widgets::CloneableWidget,int,unsigned, char, widgets::ConcreteWidget,int );    
    constexpr auto index = 4;
    //when
    TL::TypeAt<TestTypeList, index>::Result widget;
    //then
    ASSERT_EQ(widgets::defaultWidgetXValue, widget.getX()); 
}

// TEST(TypeListTest, typeListAtOverflowingIndexShouldNotCompile)
// {
//     //given
//     using TestTypeList = TYPELIST_6(widgets::CloneableWidget,int,unsigned, char, widgets::ConcreteWidget,int );    
//     constexpr auto index = 6;
//     //when
//     TL::TypeAt<TestTypeList, index>::Result widget;
//     //then
//     ASSERT_GE(index, TL::Length<TestTypeList>::value) << "Index does not overflow testTypeList";
//     FAIL() << "Index overflows typelist length, TypeAt should not compile";
// }
