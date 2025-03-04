#pragma once

#include "dimensionaldoublespinbox.h"


class MeterDoubleSpinBox : public DimensionalDoubleSpinBox
{

public:
    explicit MeterDoubleSpinBox(QWidget *parent = nullptr) noexcept
        : DimensionalDoubleSpinBox(parent)
    {
        setMetricSuffix("m");
        setMainPrefix(MetricPrefixes::Empty);
    }
    virtual ~MeterDoubleSpinBox() noexcept = default;

};
