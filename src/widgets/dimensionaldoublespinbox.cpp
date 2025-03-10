#include "dimensionaldoublespinbox.h"

#include "arithmetic.h"


DimensionalDoubleSpinBox::DimensionalDoubleSpinBox(QWidget *parent) noexcept
    : QDoubleSpinBox(parent)
    , _SINGLE_STEP_(0.01)
    , _DECIMALS_(2)
    , maxValue_(10000.0)
    , valueStep_(0.001)
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
    return metricValue(mainPrefix_);
}

double DimensionalDoubleSpinBox::metricValue(const MetricPrefixes metricPrefix) const noexcept
{
    return Arithmetic::nearestFloating(value() * std::pow(10, std::to_underlying(currentPrefix_) - std::to_underlying(metricPrefix)), mainStep());
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

    if (Arithmetic::isEqualToZero(ABS_VALUE))
        return;

    if (ABS_VALUE >= 1000.0 && currentPrefix_ != maxPrefix_)
    {
        ++currentPrefix_;
        setMaxMetricValue();
        setMetricValue(metricValue * 0.001);
    }
    else if (ABS_VALUE < 1.0 && currentPrefix_ != minPrefix_)
    {
        --currentPrefix_;
        setMetricValue(metricValue * 1000.0);
    }
    else
    {
        setSingleStep(std::max(_SINGLE_STEP_, mainStep()));
        setValue(Arithmetic::nearestFloating(metricValue, mainStep()));
    }

    setMetricSuffix();
}

double DimensionalDoubleSpinBox::mainStep() const noexcept
{
    return valueStep_ * std::pow(10, std::to_underlying(mainPrefix_) - std::to_underlying(currentPrefix_));
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
