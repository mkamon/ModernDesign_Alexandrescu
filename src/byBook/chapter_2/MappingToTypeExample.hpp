#pragma once

#include "MapToType.hpp"
#include "Widgets/ExampleWidgets.hpp"

namespace typeSpecialization
{
    template <typename T, typename U>
    T *create(const U& arg, TypeToType<T>)
    {
        return new T(arg);
    }

    constexpr auto secondArgValue = 10;
    template <typename U>
    widgets::TwoArgsWidget *create(const U& arg, TypeToType<widgets::TwoArgsWidget>)
    {
        return new widgets::TwoArgsWidget(arg, secondArgValue);
    }
}