#pragma once

#include <cmath>


class Arithmetic
{

public:
    Arithmetic() = delete;
    ~Arithmetic() = delete;

    Arithmetic(const Arithmetic &) = delete;
    Arithmetic(Arithmetic &&) = delete;
    Arithmetic &operator=(const Arithmetic &) = delete;
    Arithmetic &operator=(Arithmetic &&) = delete;

    [[nodiscard]] static constexpr bool isEqualToZero(const std::floating_point auto value)
    {
        return (std::numeric_limits<double>::epsilon() >= value);
    }

    [[nodiscard]] static constexpr double nearestFloating(const std::floating_point auto value, const std::floating_point auto step)
    {
        return std::round(value / step) * step;
    }

};
