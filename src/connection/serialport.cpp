#include "serialport.h"

#include <QDebug>


SerialPort::SerialPort(
    const QString &name,
    const qint32 baudRate
)
    : QSerialPort{nullptr}
{
    if (name.isEmpty())
        throw SerialPortException{"Port name is empty"};

    setPortName(name);
    setBaudRate(baudRate, AllDirections);
    setDataBits(Data8);
    setStopBits(OneStop);
    setParity(NoParity);
    setFlowControl(NoFlowControl);
    setReadBufferSize(30ll);

    if (!open(ReadWrite))
        throw SerialPortException{errorString()};

    connect(this, &QSerialPort::errorOccurred, [this](SerialPortError error) -> void {
        try
        {
            throw SerialPortException{error};
        }
        catch (const SerialPortException &exception)
        {
            qWarning() << exception.what();
            emit errorOccured(exception.what());
        }
    });
}

SerialPort::~SerialPort()
{
    close();
}
