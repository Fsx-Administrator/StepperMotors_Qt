#include "serialport.h"

#include <QDebug>


SerialPort::SerialPort(
    const QString &name,
    const qint32 baudRate
)
    : QSerialPort(nullptr)
{
    qDebug() << baudRate;
    qDebug() << name;

    if (name.isEmpty())
        throw SerialPortException("Port name is empty");

    setPortName(name);
    setBaudRate(baudRate, AllDirections);
    setDataBits(Data8);
    setStopBits(OneStop);

    if (!open(ReadWrite))
        throw SerialPortException(errorString());

    connect(this, &QSerialPort::errorOccurred, [this](SerialPortError error) -> void {
        try
        {
            throw SerialPortException(error);
        }
        catch (const SerialPortException &exception)
        {
            qWarning() << exception.what();
            emit errorOccured(exception.what());
        }
    });
}

SerialPort::~SerialPort() noexcept
{
    close();
}
