#pragma once

#include "WidgetInterfaces.hpp"

namespace widgets
{
    constexpr auto defaultWidgetXValue = 3;
    constexpr auto defaultWidgetYValue = 5;

    class ConcreteWidget
    {
        int x = defaultWidgetXValue;
    public:
        explicit ConcreteWidget(int x = defaultWidgetXValue);
        ConcreteWidget( const ConcreteWidget &other);
        ~ConcreteWidget() = default;

        [[nodiscard]] int getX() const noexcept;
    };

    class CloneableWidget : public ConcreteWidget, public Cloneable<CloneableWidget>
    {
    public:
        explicit CloneableWidget(int x = defaultWidgetXValue);
        [[nodiscard]] CloneableWidget* clone() const override;

    };


    class TwoArgsWidget : public ConcreteWidget
    {
        int y = defaultWidgetYValue;
    public:
        TwoArgsWidget(int x, int y);

        [[nodiscard]] int getY() const noexcept;
    };

}
