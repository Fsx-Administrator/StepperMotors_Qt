#include "portnamecombobox.h"

#include <QSerialPortInfo>
#include <QTimerEvent>


PortNameComboBox::PortNameComboBox(QWidget *parent) noexcept
    : QComboBox(parent)
    , _REFRESH_TIMEOUT_(2000)
    , refreshTimerId_(startTimer(_REFRESH_TIMEOUT_))
{}

PortNameComboBox::~PortNameComboBox() noexcept
{
    killTimer(refreshTimerId_);
}

QString PortNameComboBox::currentPortName() const noexcept
{
    return currentText().section(" ", 0, 0);
}

void PortNameComboBox::timerEvent(QTimerEvent *event)
{
    if (event->timerId() == refreshTimerId_)
        refresh();
}

void PortNameComboBox::refresh() noexcept
{
    const auto lastIndex = currentIndex();

    clear();
    for (const auto &portInfo : QSerialPortInfo::availablePorts())
        addItem(portInfo.portName() + " : " + portInfo.description());

    if (lastIndex > 0 && lastIndex < count())
        setCurrentIndex(lastIndex);
    else
        setCurrentIndex(0);
}
