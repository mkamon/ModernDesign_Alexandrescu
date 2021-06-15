#pragma once

#include "WidgetInterfaces.hpp"

namespace widgets
{
    constexpr auto defaultWidgetValue = 0;

    class ConcreteWidget
    {
        int x = defaultWidgetValue;
    public:
        explicit ConcreteWidget(int x = defaultWidgetValue);
        ConcreteWidget( const ConcreteWidget &other);
        ~ConcreteWidget() = default;

        [[nodiscard]] int get() const noexcept;
    };

    class CloneableWidget : public ConcreteWidget, public Cloneable<CloneableWidget>
    {
    public:
        explicit CloneableWidget(int x = defaultWidgetValue);
        [[nodiscard]] CloneableWidget* clone() const override;

    };
}
