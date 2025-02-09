#include "baudratecombobox.h"

#include <QSerialPort>


BaudRateComboBox::BaudRateComboBox(QWidget *parent) noexcept
    : QComboBox(parent)
{
    addItem(QString::number(QSerialPort::Baud1200));
    addItem(QString::number(QSerialPort::Baud2400));
    addItem(QString::number(QSerialPort::Baud4800));
    addItem(QString::number(QSerialPort::Baud9600));
    addItem(QString::number(QSerialPort::Baud19200));
    addItem(QString::number(QSerialPort::Baud38400));
    addItem(QString::number(QSerialPort::Baud57600));
    addItem(QString::number(QSerialPort::Baud115200));

    connect(this, &QComboBox::currentTextChanged, [this](const QString &text) -> void {
        emit baudRateChanged(text.toUInt());
    });
}

quint32 BaudRateComboBox::currentBaudRate() const noexcept
{
    return currentText().toInt();
}

void BaudRateComboBox::setCurrentBaudRate(const quint32 baudRate) noexcept
{
    setCurrentText(QString::number(baudRate));
}
