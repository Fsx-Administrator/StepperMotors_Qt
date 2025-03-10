#pragma once

#include "arduinowithsteppers.h"
#include "meterdoublespinbox.h"


class ArduinoMeterDoubleSpinBox final : public MeterDoubleSpinBox
{

public:
    explicit ArduinoMeterDoubleSpinBox(QWidget *parent = nullptr) noexcept
        : MeterDoubleSpinBox(parent)
    {
        setMaxPrefix(MetricPrefixes::Milli);
        setMinPrefix(MetricPrefixes::Micro);
        setCurrentPrefix(MetricPrefixes::Milli);
        setMainPrefix(MetricPrefixes::Micro);
        setMainValueStep(ArduinoWithSteppers::instance().step());
    }
    ~ArduinoMeterDoubleSpinBox() noexcept = default;

};
