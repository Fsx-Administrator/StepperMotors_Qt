#include "distancevaluewidget.h"

#include "arduinometerdoublespinbox.h"

#include <QGridLayout>
#include <QPushButton>


DistanceValueWidget::DistanceValueWidget(QWidget *parent) noexcept
    : QWidget(parent)
    , arduinoMeterDoubleSpinBox_(new ArduinoMeterDoubleSpinBox(this))
{
    buttons_.addButton(new QPushButton("1 um", this), 0);
    buttons_.addButton(new QPushButton("10 um", this), 1);
    buttons_.addButton(new QPushButton("100 um", this), 2);
    buttons_.addButton(new QPushButton("1 mm", this), 3);
    buttons_.addButton(new QPushButton("10 mm", this), 4);
    buttons_.addButton(new QPushButton("100 mm", this), 5);

    QGridLayout *layout = new QGridLayout(this);
    layout->addWidget(arduinoMeterDoubleSpinBox_, 0, 0, 1, 3);
    layout->addWidget(buttons_.button(0), 1, 0, Qt::AlignCenter);
    layout->addWidget(buttons_.button(1), 1, 1, Qt::AlignCenter);
    layout->addWidget(buttons_.button(2), 1, 2, Qt::AlignCenter);
    layout->addWidget(buttons_.button(3), 2, 0, Qt::AlignCenter);
    layout->addWidget(buttons_.button(4), 2, 1, Qt::AlignCenter);
    layout->addWidget(buttons_.button(5), 2, 2, Qt::AlignCenter);
    setLayout(layout);

    connect(&buttons_, &QButtonGroup::idClicked, this, [this](int id) -> void {
        arduinoMeterDoubleSpinBox_->setMainValue(arduinoMeterDoubleSpinBox_->mainValue() +std::pow(10.0, id));
    });
}

double DistanceValueWidget::distance() const noexcept
{
    return arduinoMeterDoubleSpinBox_->mainValue();
}

void DistanceValueWidget::setDistance(const double value) noexcept
{
    arduinoMeterDoubleSpinBox_->setMainValue(value);
}
