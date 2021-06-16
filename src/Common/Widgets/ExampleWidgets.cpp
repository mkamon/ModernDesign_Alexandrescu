#include "ExampleWidgets.hpp"
#include <iostream>

using namespace widgets;

ConcreteWidget::ConcreteWidget(int x) : x{x}
{
    std::cout << "ConcreteWidget constructor with x=" << x << std::endl;
}

ConcreteWidget::ConcreteWidget( const ConcreteWidget &other)
{
    x = other.x;
}

int ConcreteWidget::getX() const noexcept
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
    return new CloneableWidget(getX());
}

TwoArgsWidget::TwoArgsWidget(int x, int y)
    : ConcreteWidget(x), y{y}
{

}  

int TwoArgsWidget::getY() const noexcept 
{
    return y;
} 
