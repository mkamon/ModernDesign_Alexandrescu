#pragma once

template <int v>
struct IntToType
{
    enum {value = v};
};

template <typename T>
struct TypeToType
{
    using OriginalType = T;
};


