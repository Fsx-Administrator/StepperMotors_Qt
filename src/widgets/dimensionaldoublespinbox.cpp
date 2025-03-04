#include "dimensionaldoublespinbox.h"

#include "common.h"


DimensionalDoubleSpinBox::DimensionalDoubleSpinBox(QWidget *parent) noexcept
    : QDoubleSpinBox(parent)
    , _SINGLE_STEP_(0.01)
    , _DECIMALS_(2)
    , maxValue_(10000.0)
{
    setMinPrefix(MetricPrefixes::Femto);
    setMaxPrefix(MetricPrefixes::Peta);
    setCurrentPrefix(MetricPrefixes::Empty);
    setMaxMetricValue();

    setAccelerated(true);
    setButtonSymbols(PlusMinus);
    setCorrectionMode(CorrectToNearestValue);
    setDecimals(_DECIMALS_);
    setSingleStep(_SINGLE_STEP_);

    connect(this, &QDoubleSpinBox::valueChanged, this, &DimensionalDoubleSpinBox::setMetricValue);
}

double DimensionalDoubleSpinBox::mainValue() const noexcept
{
    return value() * std::pow(10, std::to_underlying(currentPrefix_) - std::to_underlying(mainPrefix_));
}

double DimensionalDoubleSpinBox::metricValue(const MetricPrefixes metricPrefix) const noexcept
{
    return value() * std::pow(10, std::to_underlying(currentPrefix_) - std::to_underlying(metricPrefix));
}

void DimensionalDoubleSpinBox::setMaxMetricValue(const double value) noexcept
{
    maxValue_ = value;
    setMaxMetricValue();
}

void DimensionalDoubleSpinBox::setMainValue(const double value) noexcept
{
    currentPrefix_ = mainPrefix_;
    setMetricValue(value);
}

void DimensionalDoubleSpinBox::setMetricSuffix(const QString &suffix) noexcept
{
    suffix_ = suffix;
    setMetricSuffix();
}

void DimensionalDoubleSpinBox::setMetricValue(const double metricValue) noexcept
{
    const double ABS_VALUE = std::abs(metricValue);

    if (isEqualToZero(ABS_VALUE))
        return;

    if (ABS_VALUE >= std::kilo::num / std::kilo::den && currentPrefix_ != maxPrefix_)
    {
        ++currentPrefix_;
        setMaxMetricValue();
        setMetricValue(metricValue * std::milli::num / std::milli::den);
    }
    else if (ABS_VALUE < 1.0 && currentPrefix_ != minPrefix_)
    {
        --currentPrefix_;
        setMetricValue(metricValue * std::kilo::num / std::kilo::den);
    }
    else
    {
        setValue(metricValue);
    }

    setMetricSuffix();
}

void DimensionalDoubleSpinBox::setMaxMetricValue() noexcept
{
    if (currentPrefix_ == maxPrefix_)
        setMaximum(maxValue_);
    else
        setMaximum(10000.0);
}

void DimensionalDoubleSpinBox::setMetricSuffix() noexcept
{
    setSuffix(" " + MetricPrefix::toString(currentPrefix_) + suffix_);
}
