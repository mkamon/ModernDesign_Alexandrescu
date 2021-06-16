#include <gtest/gtest.h>

#include "chapter_2/MapToType.hpp"
#include "chapter_2/NiftyContainer.hpp"
#include "chapter_2/MappingToTypeExample.hpp"
#include "Common/Widgets/ExampleWidgets.hpp"
#include "Utils/PointerHandler.hpp"

TEST(IntToTypeTest, shouldCompilePolimorphicWidgetWithCloneableInterface)
{
    //given 
    int testValue = 5;
    widgets::CloneableWidget widget(testValue);
    typeSpecialization::NiftyContainer<widgets::CloneableWidget, true> container;
    //when 
    auto clone = utils::wrap_in_unique<widgets::CloneableWidget>(container.create(&widget));
    //then
    ASSERT_EQ(clone->getX(), widget.getX()); 
}

// TEST(IntToTypeTest, shouldNotCompileNonPolimorphicWidgetWithCloneableInterface)
// {
//     //given 
//     int testValue = 5;
//     widgets::ConcreteWidget widget(testValue);
//     typeSpecialization::NiftyContainer<widgets::ConcreteWidget, true> container;
//     //when 
//     auto clone = utils::wrap_in_unique<widgets::ConcreteWidget>(container.create(&widget));
//     //then
//     FAIL() << "Compilation should not succeed";
// }

TEST(TypeToTypeTest, wrapperShouldCreateTwoArgWidgetWithOnlySingleArgument)
{
    //given
    int testXValue = 10;
    //when
    auto widget = utils::wrap_in_unique<widgets::TwoArgsWidget>(typeSpecialization::create(testXValue, TypeToType<widgets::TwoArgsWidget>()));
    //then
    ASSERT_EQ(testXValue, widget->getX());
    ASSERT_EQ(typeSpecialization::secondArgValue, widget->getY());
}

TEST(TypeToTypeTestm, wrapperShouldCreateSimpleStringPointer)
{
    //given
    std::string someTestText = "Meaningless text";
    //when
    auto widget = utils::wrap_in_unique<std::string>(typeSpecialization::create(someTestText, TypeToType<std::string>()));
    //then
    ASSERT_EQ(someTestText, *widget);
}

