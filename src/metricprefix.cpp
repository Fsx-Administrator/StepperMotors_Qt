#include "metricprefix.h"


MetricPrefixes &operator++(MetricPrefixes &metricPrefix)
{
    switch (metricPrefix)
    {
    case MetricPrefixes::Femto:
        metricPrefix = MetricPrefixes::Pico;
        break;

    case MetricPrefixes::Pico:
        metricPrefix = MetricPrefixes::Nano;
        break;

    case MetricPrefixes::Nano:
        metricPrefix = MetricPrefixes::Micro;
        break;

    case MetricPrefixes::Micro:
        metricPrefix = MetricPrefixes::Milli;
        break;

    case MetricPrefixes::Milli:
        metricPrefix = MetricPrefixes::Empty;
        break;

    case MetricPrefixes::Empty:
        metricPrefix = MetricPrefixes::Kilo;
        break;

    case MetricPrefixes::Kilo:
        metricPrefix = MetricPrefixes::Mega;
        break;

    case MetricPrefixes::Mega:
        metricPrefix = MetricPrefixes::Giga;
        break;

    case MetricPrefixes::Giga:
        metricPrefix = MetricPrefixes::Tera;
        break;

    case MetricPrefixes::Tera:
        metricPrefix = MetricPrefixes::Peta;
        break;

    case MetricPrefixes::Peta:
        metricPrefix = MetricPrefixes::Femto;
        break;
    }

    return metricPrefix;
}

MetricPrefixes operator++(MetricPrefixes &metricPrefix, int)
{
    MetricPrefixes previousPrefix = metricPrefix;
    ++metricPrefix;

    return previousPrefix;
}

MetricPrefixes &operator--(MetricPrefixes &metricPrefix)
{
    switch (metricPrefix)
    {
    case MetricPrefixes::Femto:
        metricPrefix = MetricPrefixes::Peta;
        break;

    case MetricPrefixes::Pico:
        metricPrefix = MetricPrefixes::Femto;
        break;

    case MetricPrefixes::Nano:
        metricPrefix = MetricPrefixes::Pico;
        break;

    case MetricPrefixes::Micro:
        metricPrefix = MetricPrefixes::Nano;
        break;

    case MetricPrefixes::Milli:
        metricPrefix = MetricPrefixes::Micro;
        break;

    case MetricPrefixes::Empty:
        metricPrefix = MetricPrefixes::Milli;
        break;

    case MetricPrefixes::Kilo:
        metricPrefix = MetricPrefixes::Empty;
        break;

    case MetricPrefixes::Mega:
        metricPrefix = MetricPrefixes::Kilo;
        break;

    case MetricPrefixes::Giga:
        metricPrefix = MetricPrefixes::Mega;
        break;

    case MetricPrefixes::Tera:
        metricPrefix = MetricPrefixes::Giga;
        break;

    case MetricPrefixes::Peta:
        metricPrefix = MetricPrefixes::Tera;
        break;
    }

    return metricPrefix;
}

MetricPrefixes operator--(MetricPrefixes &metricPrefix, int)
{
    MetricPrefixes previousPrefix = metricPrefix;
    --metricPrefix;

    return previousPrefix;
}


MetricPrefixesMap MetricPrefix::prefixes_ = MetricPrefixesMap();

constexpr double MetricPrefix::multiplier(const MetricPrefixes metricPrefix) noexcept
{
    return std::pow(10, std::to_underlying(metricPrefix));
}

QString MetricPrefix::toString(const MetricPrefixes metricPrefix)
{
    if (prefixes_.isEmpty())
    {
        prefixes_[MetricPrefixes::Femto] = "f";
        prefixes_[MetricPrefixes::Pico] = "p";
        prefixes_[MetricPrefixes::Nano] = "n";
        prefixes_[MetricPrefixes::Micro] = "u";
        prefixes_[MetricPrefixes::Milli] = "m";
        prefixes_[MetricPrefixes::Empty] = "";
        prefixes_[MetricPrefixes::Kilo] = "k";
        prefixes_[MetricPrefixes::Mega] = "M";
        prefixes_[MetricPrefixes::Giga] = "G";
        prefixes_[MetricPrefixes::Tera] = "T";
        prefixes_[MetricPrefixes::Peta] = "P";
    }

    return prefixes_[metricPrefix];
}
