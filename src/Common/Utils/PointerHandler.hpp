#pragma once

#include <memory>

namespace utils
{
    template <typename T>
    std::unique_ptr<T> wrap_in_unique(T *t)
    {
        return std::unique_ptr<T>(t);
    }
}