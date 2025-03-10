#pragma once

#include "common.h"

#include <QMap>
#include <QString>
#include <QVariant>


class SettingsMap final : public QMap<QString, QVariant>
{

public:
    template<std::floating_point T>
    [[nodiscard]] inline T get(const QString &valueName) const
    {
        if constexpr (std::is_same_v<T, double>)
            return value(valueName).toDouble();
        else if constexpr (std::is_same_v<T, float>)
            return value(valueName).toFloat();
    }

    template<std::integral T>
    [[nodiscard]] inline T get(const QString &valueName) const
    {
        if constexpr (std::is_same_v<T, bool>)
            return value(valueName).toBool();
        else if constexpr (std::is_unsigned_v<T>)
            return value(valueName).toUInt();
        else if constexpr (std::is_integral_v<T>)
            return value(valueName).toInt();
    }

    template<EnumOrUnion T>
    [[nodiscard]] inline T get(const QString &valueName) const
    {
        return static_cast<T>(value(valueName).toInt());
    }

    inline void set(const QString &valueName, const QVariant &value)
    {
        this->operator[](valueName) = value;
    }

};


class SectionsMap final : public QMap<QString, SettingsMap>
{

public:
    template<class T>
    [[nodiscard]] inline T get(const QString &sectionName, const QString &valueName) const
    {
        return value(sectionName).get<T>(valueName);
    }

    inline void set(const QString &sectionName, const QString &valueName, const QVariant &value)
    {
        this->operator[](sectionName).set(valueName, value);
    }

};
