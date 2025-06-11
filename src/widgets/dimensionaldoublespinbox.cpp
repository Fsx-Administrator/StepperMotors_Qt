#include "dimensionaldoublespinbox.h"

#include "arithmetic.h"

#include <QEvent>


DimensionalDoubleSpinBox::DimensionalDoubleSpinBox(QWidget *parent)
    : QDoubleSpinBox{parent}
    , _SINGLE_STEP_{0.01}
    , _DECIMALS_{2}
    , maxValue_{10000.0}
    , valueStep_{0.001}
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

double DimensionalDoubleSpinBox::mainValue() const
{
    return metricValue(mainPrefix_);
}

QString DimensionalDoubleSpinBox::metricSuffix() const
{
    // qDebug() << suffix() << suffix().remove(" ");
    return suffix().remove(" ");
}

double DimensionalDoubleSpinBox::metricValue(MetricPrefixes prefix) const
{
    return Arithmetic::nearestFloating(value() * std::pow(10.0, std::to_underlying(currentPrefix_) - std::to_underlying(prefix)), metricStep(prefix));
}

void DimensionalDoubleSpinBox::setMaxMetricValue(double value)
{
    maxValue_ = value;
    setMaxMetricValue();
}

void DimensionalDoubleSpinBox::setMainValue(double value)
{
    currentPrefix_ = mainPrefix_;
    setMetricValue(value);
}

void DimensionalDoubleSpinBox::setMetricSuffix(const QString &suffix)
{
    suffix_ = suffix;
    setMetricSuffix();
}

void DimensionalDoubleSpinBox::setMetricValue(double value)
{
    const double ABS_VALUE = std::abs(value);

    if (Arithmetic::isEqualToZero(ABS_VALUE))
    {
        setValue(0.0);
        return;
    }

    if (ABS_VALUE >= 1000.0 && currentPrefix_ != maxPrefix_)
    {
        ++currentPrefix_;
        setMaxMetricValue();
        setMetricValue(value * 0.001);
    }
    else if (ABS_VALUE < 1.0 && currentPrefix_ != minPrefix_)
    {
        --currentPrefix_;
        setMaxMetricValue();
        setMetricValue(value * 1000.0);
    }
    else
    {
        setSingleStep(std::max(_SINGLE_STEP_, metricStep(currentPrefix_)));
        setValue(Arithmetic::nearestFloating(value, metricStep(currentPrefix_)));
    }

    setMetricSuffix();
}

bool DimensionalDoubleSpinBox::event(QEvent *event)
{
    if (event->type() == QEvent::LanguageChange)
        translate();

    return QWidget::event(event);
}

double DimensionalDoubleSpinBox::mainStep() const
{
    return metricStep(mainPrefix_);
}

double DimensionalDoubleSpinBox::metricStep(MetricPrefixes prefix) const
{
    return valueStep_ * std::pow(10.0, std::to_underlying(mainPrefix_) - std::to_underlying(prefix));
}

void DimensionalDoubleSpinBox::setMaxMetricValue()
{
    if (currentPrefix_ == maxPrefix_)
        setMaximum(maxValue_);
    else
        setMaximum(10000.0);
}

void DimensionalDoubleSpinBox::setMetricSuffix()
{
    setSuffix(" " + MetricPrefix::toString(currentPrefix_) + suffix_);
}
