#pragma once

#include "metricprefix.h"

#include <QDoubleSpinBox>


class DimensionalDoubleSpinBox : public QDoubleSpinBox
{
    Q_OBJECT

public:
    explicit DimensionalDoubleSpinBox(QWidget *parent = nullptr);
    virtual ~DimensionalDoubleSpinBox() = default;

    [[nodiscard]] double mainValue() const;
    [[nodiscard]] QString metricSuffix() const;
    [[nodiscard]] double metricValue(MetricPrefixes prefix) const;
    inline void setCurrentPrefix(MetricPrefixes prefix)
    { currentPrefix_ = (prefix > maxPrefix_) ? maxPrefix_ : prefix; setMetricSuffix(); }
    void setMaxMetricValue(double value);
    inline void setMaxPrefix(MetricPrefixes prefix) { maxPrefix_ = prefix; }
    inline void setMainPrefix(MetricPrefixes prefix) { mainPrefix_ = prefix; }
    void setMainValue(double value);
    inline void setMainValueStep(double step) { valueStep_ = step; }
    void setMetricSuffix(const QString &suffix);
    void setMetricValue(double value);
    inline void setMinPrefix(MetricPrefixes prefix) { minPrefix_ = prefix; }
	
protected:
	virtual bool event(QEvent *event) override;
    virtual void translate() {}

private:
    [[nodiscard]] double mainStep() const;
    [[nodiscard]] double metricStep(MetricPrefixes prefix) const;
    void setMaxMetricValue();
    void setMetricSuffix();

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
