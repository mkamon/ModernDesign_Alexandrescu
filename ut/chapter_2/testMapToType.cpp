#include <gtest/gtest.h>

#include "chapter_2/MapToType.hpp"
#include "chapter_2/NiftyContainer.hpp"
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
    ASSERT_EQ(clone->get(), widget.get()); 
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