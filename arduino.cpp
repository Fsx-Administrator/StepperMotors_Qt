#include "arduino.h"

#include "arduinoserialport.h"

#include <QDebug>


void Arduino::connect(const QString &portName, const quint32 baudRate)
{
    try
    {
        if (serialPort_ != nullptr)
            throw ArduinoException("Arduino has already connected");

        serialPort_ = std::make_unique<ArduinoSerialPort>(portName, baudRate);
        emit connected();
    }
    catch (const std::runtime_error &exception)
    {
        qWarning() << exception.what();
    }
}

void Arduino::disconnect()
{
    try
    {
        if (serialPort_ == nullptr)
            throw ArduinoException("Arduino is not connected");

        serialPort_.reset();
        emit disconnected();
    }
    catch (const ArduinoException &exception)
    {
        qWarning() << exception.what();
    }
}

Arduino::Arduino()
    : QObject(nullptr)
    , serialPort_(nullptr)
{}

Arduino::~Arduino() {}
