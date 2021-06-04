#include <gtest/gtest.h>

#include "chapter_1/CreatorPolicies.hpp"
#include "chapter_1/WidgetManager.hpp"
#include "Widgets/ExampleWidgets.hpp"
#include "Utils/PointerHandler.hpp"

TEST(CreatorPolicyTest, PrototypeCreatorTest)
{
    //given
    const int expectedValue = 5;
    widgets::WidgetManager<policy::PrototypeCreator, widgets::CloneableWidget> creator;
    creator.setPrototype(new widgets::CloneableWidget (expectedValue));
    //when
    auto clone = utils::wrap_in_unique<widgets::CloneableWidget>(creator.create());
    //then
    ASSERT_EQ(expectedValue, clone.get()->get());
}

TEST(WidgetManagerTest, shouldCompileWhenSwitchPrototypeMethodNotUsed)
{
    //given
    widgets::WidgetManager<policy::OpNewCreator, widgets::ConcreteWidget> creator;
    //when
    auto newWidget = utils::wrap_in_unique(creator.create());
    //then
    ASSERT_EQ(widgets::defaultWidgetValue, newWidget->get());
}
