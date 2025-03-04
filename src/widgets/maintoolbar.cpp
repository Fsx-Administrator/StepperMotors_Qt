#include "maintoolbar.h"

#include "arduinowithsteppers.h"
#include "baudratecombobox.h"
#include "portnamecombobox.h"
#include "toggledpushbutton.h"


MainToolBar::MainToolBar(QWidget *parent) noexcept
    : baudRateComboBox_(new BaudRateComboBox(parent))
    , portNameComboBox_(new PortNameComboBox(parent))
    , connectToggledPushButton_(new ToggledPushButton(
        parent,
        "Disconnect",
        "Connect",
        [this]() -> void {
            ArduinoWithSteppers::instance().connect(portNameComboBox_->currentPortName());
        },
        [this]() -> void {
            ArduinoWithSteppers::instance().disconnect();
        }
    ))
{
    setAllowedAreas(Qt::TopToolBarArea);
    setMovable(false);
    setFloatable(false);

    addWidget(portNameComboBox_);
    addWidget(baudRateComboBox_);
    addWidget(connectToggledPushButton_);

    connect(&ArduinoWithSteppers::instance(), &Arduino::connected, this, [this](bool successfully) -> void {
        baudRateComboBox_->setEnabled(!successfully);
        portNameComboBox_->setEnabled(!successfully);
        connectToggledPushButton_->setChecked(successfully);
    });
}
