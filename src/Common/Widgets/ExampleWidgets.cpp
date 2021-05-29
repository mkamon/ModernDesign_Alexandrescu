#include "ExampleWidgets.hpp"
#include <iostream>

using namespace widgets;

ConcreteWidget::ConcreteWidget(int x) : x{x}
{
    std::cout << "ConcreteWidget constructor with x=" << x << std::endl;
}

int ConcreteWidget::get() const noexcept
{
    return x;
}

CloneableWidget::CloneableWidget(int x)
    : ConcreteWidget(x)
{
    std::cout << "ConcreteCloneableWidget constructor with x=" << x << std::endl;
}

CloneableWidget* CloneableWidget::clone() const
{
    return new CloneableWidget(get());
}
