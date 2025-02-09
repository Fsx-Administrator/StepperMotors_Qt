#include "mainwindow_ui.h"

#include "arduino.h"
#include "baudratecombobox.h"
#include "mainwindow.h"
#include "portnamecombobox.h"
#include "toggledpushbutton.h"

#include <QHBoxLayout>


MainWindow_Ui::MainWindow_Ui(MainWindow *parent) noexcept
    : baudRateComboBox_(new BaudRateComboBox(parent))
    , portNameComboBox_(new PortNameComboBox(parent))
    , connect_ToggledPushButton_(new ToggledPushButton(
        parent,
        "Disconnect",
        "Connect",
        [this]() -> void {
            Arduino::instance().connect(portNameComboBox_->currentPortName());
        },
        [this]() -> void {
            Arduino::instance().disconnect();
        }
    ))
{
    QWidget *widget = new QWidget(parent);
    QHBoxLayout *layout = new QHBoxLayout(widget);
    layout->addWidget(portNameComboBox_);
    layout->addWidget(baudRateComboBox_);
    layout->addWidget(connect_ToggledPushButton_);
    widget->setLayout(layout);
    parent->setCentralWidget(widget);
}
