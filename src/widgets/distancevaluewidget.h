#pragma once

#include <QButtonGroup>
#include <QWidget>


class ArduinoMeterDoubleSpinBox;

class DistanceValueWidget final : public QWidget
{
    Q_OBJECT

public:
    explicit DistanceValueWidget(QWidget *parent = nullptr);
    ~DistanceValueWidget() = default;

    [[nodiscard]] double distance() const noexcept;
    void setDistance(const double value);

private:
    [[nodiscard]] double buttonDistance(const int id) const;
    [[nodiscard]] double buttonDistance(QAbstractButton *button) const;

    QButtonGroup buttons_;
    ArduinoMeterDoubleSpinBox *arduinoMeterDoubleSpinBox_;

};
