#pragma once

namespace ctassert
{
    template<typename To, typename From>
    To safe_reinterpret_cast(From from) {
        static_assert(sizeof(From) <= sizeof(To));
        return reinterpret_cast<To>(from);
    }
}