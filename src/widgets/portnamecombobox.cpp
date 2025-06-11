#include "portnamecombobox.h"

#include <QAbstractItemView>
#include <QApplication>
#include <QSerialPortInfo>
#include <QTimerEvent>


PortNameComboBox::PortNameComboBox(QWidget *parent)
    : QComboBox(parent)
    , _REFRESH_TIMEOUT_(2000)
    , refreshTimerId_(startTimer(_REFRESH_TIMEOUT_))
{}

PortNameComboBox::~PortNameComboBox()
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

void PortNameComboBox::refresh()
{
    const auto lastIndex = currentIndex();
    int maxLength = 0;

    clear();
    const auto ports = QSerialPortInfo::availablePorts();
    for (const auto &portInfo : ports)
    {
        const auto item = portInfo.portName() + " : " + portInfo.description();
        addItem(item);
        maxLength = std::max(maxLength, QFontMetrics(QApplication::font()).horizontalAdvance(item));
    }

    if (lastIndex > 0 && lastIndex < count())
        setCurrentIndex(lastIndex);
    else
        setCurrentIndex(0);

    view()->setMinimumWidth(maxLength + 20);
}
