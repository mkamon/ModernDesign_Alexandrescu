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