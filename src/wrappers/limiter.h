#pragma once

#include "common.h"


class Limiter
{

public:
    Limiter() = delete;
    ~Limiter() = delete;

    Limiter(const Limiter &) = delete;
    Limiter(Limiter &&) = delete;
    Limiter &operator=(const Limiter &) = delete;
    Limiter &operator=(Limiter &&) = delete;

    [[nodiscard]] static inline auto limitedValue(
        const BuiltInType auto value,
        const BuiltInType auto min,
        const BuiltInType auto max
    )
    {
        return std::max(min, std::min(value, max));
    }

};
