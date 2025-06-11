#pragma once

#include <QMap>


enum class MetricPrefixes : int
{
    Femto   = -15,
    Pico    = -12,
    Nano    = -9,
    Micro   = -6,
    Milli   = -3,
    Empty   = 0,
    Kilo    = 3,
    Mega    = 6,
    Giga    = 9,
    Tera    = 12,
    Peta    = 15
};

MetricPrefixes &operator++(MetricPrefixes &metricPrefix);
MetricPrefixes operator++(MetricPrefixes &metricPrefix, int);
MetricPrefixes &operator--(MetricPrefixes &metricPrefix);
MetricPrefixes operator--(MetricPrefixes &metricPrefix, int);


using MetricPrefixesMap = QMap<MetricPrefixes, QString>;

class MetricPrefix
{

public:
    MetricPrefix() = delete;
    ~MetricPrefix() = delete;

    MetricPrefix(const MetricPrefix &) = delete;
    MetricPrefix(MetricPrefix &&) = delete;
    MetricPrefix &operator=(const MetricPrefix &) = delete;
    MetricPrefix &operator=(MetricPrefix &&) = delete;

    [[nodiscard]] static constexpr double multiplier(const MetricPrefixes metricPrefix);
    [[nodiscard]] static QString toString(const MetricPrefixes metricPrefix);

private:
    static MetricPrefixesMap prefixes_;

};
