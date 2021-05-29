#pragma once

namespace widgets
{
    template<typename T>
    class Cloneable
    {
    public:
        [[nodiscard]] virtual T* clone() const = 0;
        virtual ~Cloneable() = default;
    };
}
