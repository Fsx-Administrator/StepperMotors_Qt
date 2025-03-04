#pragma once


#include <concepts>
#include <functional>
#include <limits>


template<class T>
concept Pointer = requires(T t) { *t; };
template<class T>
concept BuiltInType = std::integral<T> || std::floating_point<T>;
template<class T>
concept Enum = std::is_enum_v<T>;
template<class T>
concept Union = std::is_union_v<T>;
template<class T>
concept EnumOrUnion = Enum<T> || Union<T>;
template<class T>
concept Functor = requires(T t) { t(); };

using Slot = std::function<void()>;

[[nodiscard]] constexpr bool isEqualToZero(const std::floating_point auto value)
{
    return (std::numeric_limits<double>::epsilon() >= value);
}
