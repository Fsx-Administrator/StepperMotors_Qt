#include "distancevaluewidget.h"

#include "arduinoparameters.h"
#include "arduinometerdoublespinbox.h"
#include "limiter.h"

#include <QGridLayout>
#include <QPushButton>


DistanceValueWidget::DistanceValueWidget(QWidget *parent)
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

    const auto buttons = buttons_.buttons();
    for (const auto button : buttons)
        if (buttonDistance(button) > 0.5 * std::max(ArduinoParameters::maxInUm(Qt::XAxis), ArduinoParameters::maxInUm(Qt::YAxis)))
            button->setEnabled(false);

    connect(&buttons_, &QButtonGroup::idClicked, this, [this](int id) -> void {
        arduinoMeterDoubleSpinBox_->setMainValue(
            Limiter{}(
                arduinoMeterDoubleSpinBox_->mainValue() + buttonDistance(id),
                0.0,
                std::max(ArduinoParameters::maxInUm(Qt::XAxis), ArduinoParameters::maxInUm(Qt::YAxis))
            )
        );
    });
    connect(arduinoMeterDoubleSpinBox_, &QDoubleSpinBox::valueChanged, this, [this]() -> void {
        arduinoMeterDoubleSpinBox_->setMainValue(
            Limiter{}(
                arduinoMeterDoubleSpinBox_->mainValue(),
                0.0,
                std::max(ArduinoParameters::maxInUm(Qt::XAxis), ArduinoParameters::maxInUm(Qt::YAxis))
            )
        );
    });
}

double DistanceValueWidget::distance() const noexcept
{
    return arduinoMeterDoubleSpinBox_->mainValue();
}

void DistanceValueWidget::setDistance(const double value)
{
    arduinoMeterDoubleSpinBox_->setMainValue(value);
}

double DistanceValueWidget::buttonDistance(const int id) const
{
    return std::pow(10.0, id);
}

double DistanceValueWidget::buttonDistance(QAbstractButton *button) const
{
    return buttonDistance(buttons_.id(button));
}
