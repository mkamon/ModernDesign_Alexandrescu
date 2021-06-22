#include <gtest/gtest.h>

#include "chapter_3/TypeList.hpp"
#include "chapter_3/SpecialTypeLists.hpp"
#include "Widgets/ExampleWidgets.hpp"
#include "Utils/PointerHandler.hpp"


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

TEST(TypeListTest, testAppendTypeToNullTypeShuldReturnTypeListOfLengthOne)
{
    //given
    using InitialTypeList = NullType;
    using TypeToBeAdded = widgets::ConcreteWidget;
    constexpr auto expectedTypeListLength = 1;
    //when
    using ResultTypeList = TL::Append<InitialTypeList, TypeToBeAdded>::Result; 
    constexpr auto length = TL::Length<ResultTypeList>::value;
    //then
    ASSERT_EQ(expectedTypeListLength, length);
}

TEST(TypeListTest, testAppendTypeListToNullTypeShuldReturnTypeListWithLengthOfTypeListAdded)
{
    //given
    using InitialTypeList = NullType;
    using TypeToBeAdded = TYPELIST_6(widgets::CloneableWidget,int,unsigned, char, widgets::ConcreteWidget,int );    
    constexpr auto expectedTypeListLength = TL::Length<TypeToBeAdded>::value;
    //when
    using ResultTypeList = TL::Append<InitialTypeList, TypeToBeAdded>::Result; 
    constexpr auto length = TL::Length<ResultTypeList>::value;
    //then
    ASSERT_EQ(expectedTypeListLength, length);
}

TEST(TypeListTest, testAppendTypeListToNotNullTypeListShuldReturnTypeListWithLengthEqualToSumOfBothTypeLists)
{
    //given
    using InitialTypeList = TYPELIST_2(int, unsigned); 
    using TypeToBeAdded = TYPELIST_6(widgets::CloneableWidget,int,unsigned, char, widgets::ConcreteWidget,int );    
    constexpr auto expectedTypeListLength = TL::Length<TypeToBeAdded>::value + TL::Length<InitialTypeList>::value;
    //when
    using ResultTypeList = TL::Append<InitialTypeList, TypeToBeAdded>::Result; 
    constexpr auto length = TL::Length<ResultTypeList>::value;
    //then
    ASSERT_EQ(expectedTypeListLength, length);
}

TEST(TypeListTest, testEraseTypeFromANullTypeShouldReturnNullType)
{
    //given
    using InitialTypeList = NullType; 
    using TypeToBeDeleted = widgets::ConcreteWidget;
    constexpr auto lengthOfNullType = TL::Length<NullType>::value; 
    //when
    using ResultTypeList = TL::Erase<InitialTypeList, TypeToBeDeleted>::Result; 
    constexpr auto length = TL::Length<ResultTypeList>::value;
    //then
    ASSERT_EQ(lengthOfNullType, length);
}

TEST(TypeListTest, testEraseTypeFromNotNullTypeListShouldReturnTypeListShorterByOne)
{
    //given
    using InitialTypeList = TYPELIST_4(int, unsigned, widgets::ConcreteWidget, char); 
    using TypeToBeDeleted = widgets::ConcreteWidget;
    constexpr auto expectedTypeListLength = TL::Length<InitialTypeList>::value - 1; 
    //when
    using ResultTypeList = TL::Erase<InitialTypeList, TypeToBeDeleted>::Result; 
    constexpr auto length = TL::Length<ResultTypeList>::value;
    //then
    ASSERT_EQ(expectedTypeListLength, length);
}

TEST(TypeListTest, testEraseTypeThatIsNotOnATypeListShouldReturnSameTypeList)
{
    //given
    using InitialTypeList = TYPELIST_4(int, unsigned, widgets::ConcreteWidget, char); 
    using TypeToBeDeleted = widgets::TwoArgsWidget;
    constexpr auto expectedTypeListLength = TL::Length<InitialTypeList>::value ; 
    //when
    using ResultTypeList = TL::Erase<InitialTypeList, TypeToBeDeleted>::Result; 
    constexpr auto length = TL::Length<ResultTypeList>::value;
    //then
    ASSERT_EQ(expectedTypeListLength, length);
}

TEST(TypeListTest, testEraseAllTypeFromNullTypeShouldReturnNullType)
{
    //given
    using InitialTypeList = NullType; 
    using TypeToBeDeleted = widgets::ConcreteWidget;
    constexpr auto lengthOfNullType = TL::Length<NullType>::value; 
    //when
    using ResultTypeList = TL::EraseAll<InitialTypeList, TypeToBeDeleted>::Result; 
    constexpr auto length = TL::Length<ResultTypeList>::value;
    //then
    ASSERT_EQ(lengthOfNullType, length);
}

TEST(TypeListTest, testEraseAllTypeFromNotNullTypeListShouldReturnTypeListShorterByTypeOccurences)
{
    //given
    using InitialTypeList = TYPELIST_6(int, unsigned, widgets::ConcreteWidget, char, widgets::ConcreteWidget, widgets::ConcreteWidget); 
    using TypeToBeDeleted = widgets::ConcreteWidget;
    constexpr auto expectedTypeListLength = TL::Length<InitialTypeList>::value - 3; 
    //when
    using ResultTypeList = TL::EraseAll<InitialTypeList, TypeToBeDeleted>::Result; 
    constexpr auto length = TL::Length<ResultTypeList>::value;
    //then
    ASSERT_EQ(expectedTypeListLength, length);
}

TEST(TypeListTest, testEraseAllTypeThatIsNotOnATypeListShouldReturnSameTypeList)
{
    //given
    using InitialTypeList = TYPELIST_4(int, unsigned, widgets::ConcreteWidget, char); 
    using TypeToBeDeleted = widgets::TwoArgsWidget;
    constexpr auto expectedTypeListLength = TL::Length<InitialTypeList>::value ; 
    //when
    using ResultTypeList = TL::EraseAll<InitialTypeList, TypeToBeDeleted>::Result; 
    constexpr auto length = TL::Length<ResultTypeList>::value;
    //then
    ASSERT_EQ(expectedTypeListLength, length);
}

TEST(TypeListTest, testNoDuplicatesOnNullTypeShuldReturnNullType)
{
    //given
    using InitialTypeList = NullType; 
    constexpr auto lengthOfNullType = TL::Length<NullType>::value; 
    //when
    using ResultTypeList = TL::NoDuplicates<InitialTypeList>::Result; 
    constexpr auto length = TL::Length<ResultTypeList>::value;
    //then
    ASSERT_EQ(lengthOfNullType, length);
}

TEST(TypeListTest, testNoDuplicatesOnTypeListShouldReturnTypeListShorterByAmountOfDuplicates)
{
    //given
    using InitialTypeList = TYPELIST_7(int, unsigned, widgets::ConcreteWidget, char, widgets::ConcreteWidget, widgets::ConcreteWidget, char); 
    constexpr auto concreteWidgetDuplicates = 2;
    constexpr auto charDuplicates = 1;
    constexpr auto expectedTypeListLength = TL::Length<InitialTypeList>::value - concreteWidgetDuplicates - charDuplicates; 
    //when
    using ResultTypeList = TL::NoDuplicates<InitialTypeList>::Result; 
    constexpr auto length = TL::Length<ResultTypeList>::value;
    //then
    ASSERT_EQ(expectedTypeListLength, length);
}

TEST(TypeListTest, testNoDuplicatesOnTypeListWithoutDuplicatesShouldReturnTypeListOftheSameLength)
{
    //given
    using InitialTypeList = TYPELIST_4(int, unsigned, widgets::ConcreteWidget, char); 
    constexpr auto expectedTypeListLength = TL::Length<InitialTypeList>::value ; 
    //when
    using ResultTypeList = TL::NoDuplicates<InitialTypeList>::Result; 
    constexpr auto length = TL::Length<ResultTypeList>::value;
    //then
    ASSERT_EQ(expectedTypeListLength, length);
}

TEST(TypeListTest, testReplacingATypeInNullTypeShoulReturnNullType)
{
    //given
    using InitialTypeList = NullType; 
    constexpr auto expectedTypeListLength = TL::Length<NullType>::value;
    //when
    using ResultTypeList = TL::Replace<InitialTypeList, widgets::ConcreteWidget, int>::Result;
    constexpr auto length = TL::Length<ResultTypeList>::value;
    //then
    ASSERT_EQ(expectedTypeListLength, length);
}

TEST(TypeListTest, testReplacingATypeShuoldNotChangeTypeListLength)
{
    //given
    using InitialTypeList = TYPELIST_4(int, unsigned, widgets::ConcreteWidget, char);
    constexpr auto expectedTypeListLength = TL::Length<InitialTypeList>::value;
    //when
    using ResultTypeList = TL::Replace<InitialTypeList, widgets::ConcreteWidget, int>::Result;
    constexpr auto length = TL::Length<ResultTypeList>::value;
    //then
    ASSERT_EQ(expectedTypeListLength, length);
}

TEST(TypeListTest, testReplaceConcreteWidgetWithTwoArgsWidget)
{
    //given
    using InitialTypeList = TYPELIST_4(int, unsigned, widgets::ConcreteWidget, char);
    constexpr auto expectedTypeListLength = TL::Length<InitialTypeList>::value;
    constexpr auto widgetPosition = 2;
    constexpr auto testValueX = 5, testValueY = 10;
    //when
    using ResultTypeList = TL::Replace<InitialTypeList, widgets::ConcreteWidget, widgets::TwoArgsWidget>::Result;
    constexpr auto length = TL::Length<ResultTypeList>::value;
    TL::TypeAt<ResultTypeList, widgetPosition>::Result widget(testValueX, testValueY);
    //then
    ASSERT_EQ(expectedTypeListLength, length);
    ASSERT_EQ(testValueX, widget.getX());
    ASSERT_EQ(testValueY, widget.getY());
}

TEST(TypeListTest, shouldFindMostDerivedTypeAtTheEndOfTypeList)
{
    //given
    using InitialTypeList = TYPELIST_3(widgets::ConcreteWidget, widgets::TwoArgsWidget, widgets::ThreeArgsWidget);
    //when 
    using ResultType = TL::MostDerived<InitialTypeList, widgets::ConcreteWidget>::Result; 
    ResultType widget;
    //then
    ASSERT_EQ(widgets::defaultWidgetZValue, widget.getZ());
}

TEST(TypeListTest, shouldFindMostDerivedTypeInAMiddleOfTypeList)
{
    //given
    using InitialTypeList = TYPELIST_3(widgets::ConcreteWidget, widgets::ThreeArgsWidget, widgets::TwoArgsWidget);
    //when 
    using ResultType = TL::MostDerived<InitialTypeList, widgets::ConcreteWidget>::Result; 
    ResultType widget;
    //then
    ASSERT_EQ(widgets::defaultWidgetZValue, widget.getZ());
}

TEST(TypeListTest, shouldFindMostDerivedTypeInTheBeginningOfTypeList)
{
    //given
    using InitialTypeList = TYPELIST_3(widgets::ThreeArgsWidget, widgets::ConcreteWidget, widgets::TwoArgsWidget);
    //when 
    using ResultType = TL::MostDerived<InitialTypeList, widgets::ConcreteWidget>::Result; 
    ResultType widget;
    //then
    ASSERT_EQ(widgets::defaultWidgetZValue, widget.getZ());
}

TEST(TypeListTest, shouldFindMostDerivedTypeFromTwoArgsWidgetBranch)
{
    //given
    using InitialTypeList = TYPELIST_5(widgets::ConcreteWidget, widgets::CloneableWidget, widgets::TwoArgsWidget, widgets::NonPolimorphicWidget, widgets::ThreeArgsWidget);
    //when
    using ResultType = TL::MostDerived<InitialTypeList, widgets::ConcreteWidget>::Result;
    ResultType widget;
    //then
    ASSERT_EQ(widgets::defaultWidgetZValue, widget.getZ());
}

TEST(TypeListTest, shuoldFindMostDerivedTypeFromCloneableWidgetBranch)
{
    //given
    using InitialTypeList = TYPELIST_5(widgets::ConcreteWidget, widgets::TwoArgsWidget, widgets::NonPolimorphicWidget, widgets::ThreeArgsWidget, widgets::CloneableWidget );
    constexpr auto testValue = 99;
    //when
    using ResultType = TL::MostDerived<InitialTypeList, widgets::ConcreteWidget>::Result;
    ResultType widget(testValue);
    //then
    auto clone = utils::wrap_in_unique<widgets::CloneableWidget>(widget.clone());
    ASSERT_EQ(testValue, widget.getX());
}

TEST(TypeListTest, shouldPutMostDerivedTypeFromTwoArgsWidgetBranchInTheFrontOfTypeList)
{
    //given
    using InitialTypeList = TYPELIST_5(widgets::ConcreteWidget, widgets::CloneableWidget, widgets::TwoArgsWidget, widgets::NonPolimorphicWidget, widgets::ThreeArgsWidget);
    //when
    using ResultTypeList = TL::DerivedToFront<InitialTypeList>::Result;
    using ResultType = TL::TypeAt<ResultTypeList, 0>::Result;
    ResultType widget;
    //then
    ASSERT_EQ(widgets::defaultWidgetZValue, widget.getZ());
}

TEST(TypeListTest, shuoldPutMostDerivedTypeFromCloneableWidgetBranchInTheFrontOfTypeList)
{
    //given
    using InitialTypeList = TYPELIST_5(widgets::ConcreteWidget, widgets::TwoArgsWidget, widgets::NonPolimorphicWidget, widgets::ThreeArgsWidget, widgets::CloneableWidget );
    constexpr auto testValue = 99;
    //when
    using ResultTypeList = TL::DerivedToFront<InitialTypeList>::Result;
    using ResultType = TL::TypeAt<ResultTypeList, 0>::Result;
    ResultType widget(testValue);
    //then
    auto clone = utils::wrap_in_unique<widgets::CloneableWidget>(widget.clone());
    ASSERT_EQ(testValue, widget.getX());
}
