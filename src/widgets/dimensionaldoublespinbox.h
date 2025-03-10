#pragma once

#include "metricprefix.h"

#include <QDoubleSpinBox>


class DimensionalDoubleSpinBox : public QDoubleSpinBox
{
    Q_OBJECT

public:
    explicit DimensionalDoubleSpinBox(QWidget *parent = nullptr) noexcept;
    virtual ~DimensionalDoubleSpinBox() noexcept = default;

    [[nodiscard]] double mainValue() const noexcept;
    [[nodiscard]] double metricValue(const MetricPrefixes metricPrefix) const noexcept;
    inline void setCurrentPrefix(const MetricPrefixes prefix) noexcept
    { currentPrefix_ = (prefix > maxPrefix_) ? maxPrefix_ : prefix; }
    void setMaxMetricValue(const double value) noexcept;
    inline void setMaxPrefix(const MetricPrefixes prefix) noexcept { maxPrefix_ = prefix; }
    inline void setMainPrefix(const MetricPrefixes prefix) noexcept { mainPrefix_ = prefix; }
    void setMainValue(const double value) noexcept;
    inline void setMainValueStep(const double step) noexcept { valueStep_ = step; }
    void setMetricSuffix(const QString &suffix) noexcept;
    void setMetricValue(const double metricValue) noexcept;
    inline void setMinPrefix(const MetricPrefixes prefix) noexcept { minPrefix_ = prefix; }

private:
    [[nodiscard]] double mainStep() const noexcept;
    void setMaxMetricValue() noexcept;
    void setMetricSuffix() noexcept;

    const double _SINGLE_STEP_;
    const int _DECIMALS_;

    QString suffix_;
    MetricPrefixes currentPrefix_;
    MetricPrefixes maxPrefix_;
    MetricPrefixes mainPrefix_;
    MetricPrefixes minPrefix_;
    double maxValue_;
    double valueStep_;

};


