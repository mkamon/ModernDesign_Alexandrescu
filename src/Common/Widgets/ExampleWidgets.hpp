#pragma once

#include "WidgetInterfaces.hpp"

namespace widgets
{
    class ConcreteWidget
    {
        int x = 0;
    public:
        ConcreteWidget(int x = 0);
        ~ConcreteWidget() = default;

        [[nodiscard]] int get() const noexcept;
    };

    class CloneableWidget : public ConcreteWidget, public Cloneable<CloneableWidget>
    {
    public:
        CloneableWidget(int x=0);
        [[nodiscard]] CloneableWidget* clone() const override;

    };
}
