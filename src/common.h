#pragma once


#include <concepts>
#include <functional>


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
