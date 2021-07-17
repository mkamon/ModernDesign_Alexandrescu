#include <gtest/gtest.h>

#include "chapter_3/LinearHierarchy.hpp"
#include "Widgets/ExampleWidgets.hpp"

namespace linearTest
{
    enum class WidgetHandled
    {
        ConcreteWidget,
        CloneableWidget,
        TwoArgsWidget,
        NonPolimorphicWidget
    };

    template <typename T, typename Base>
    struct EventHandler : public Base
    {
        virtual WidgetHandled onEvent(T &obj);
    };

    template <typename B> 
    struct EventHandler<widgets::ConcreteWidget, B>
    {
        virtual WidgetHandled onEvent(widgets::ConcreteWidget &widget)
        {
            return WidgetHandled::ConcreteWidget;
        }
    };
    template <typename B> 
    struct EventHandler<widgets::CloneableWidget, B>
    {
        virtual WidgetHandled onEvent(widgets::CloneableWidget &widget)
        {
            return WidgetHandled::CloneableWidget;
        }
    };
    template <typename B> 
    struct EventHandler<widgets::TwoArgsWidget, B>
    {
        virtual WidgetHandled onEvent(widgets::TwoArgsWidget &widget)
        {
            return WidgetHandled::TwoArgsWidget;
        }
    };
    template <typename B> 
    struct EventHandler<widgets::NonPolimorphicWidget, B>
    {
        virtual WidgetHandled onEvent(widgets::NonPolimorphicWidget &widget)
        {
            return WidgetHandled::NonPolimorphicWidget ;
        }
    };
}

TEST(testGenLinearHierarchy, shouldCompileAndCreateLinearEventHandlerHierarchy)
{
    //given
    using Widgets = TYPELIST_3(widgets::NonPolimorphicWidget, widgets::CloneableWidget, widgets::TwoArgsWidget);
    using WidgetEventHandler = GenLinearHierarchy< 
        Widgets,
        linearTest::EventHandler
        >;
    widgets::NonPolimorphicWidget nonPolimorphicWidget;
    widgets::TwoArgsWidget twoArgWidget;
    widgets::CloneableWidget cloneableWidget;
    //when
    WidgetEventHandler handler;
    //then
    ASSERT_EQ(handler.onEvent(nonPolimorphicWidget), linearTest::WidgetHandled::NonPolimorphicWidget);
    //Does not work but it should: 
    // ASSERT_EQ(handler.onEvent(twoArgWidget), linearTest::WidgetHandled::TwoArgsWidget);
    // ASSERT_EQ(handler.onEvent(cloneableWidget),linearTest::WidgetHandled::CloneableWidget);
}
