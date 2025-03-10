#include "arduino.h"

#include "arduinoserialport.h"

#include <QDebug>


void Arduino::connect(const QString &portName, const quint32 baudRate)
{
    try
    {
        if (isConnected())
            throw ArduinoException("Arduino has already connected");

        serialPort_ = std::make_unique<ArduinoSerialPort>(portName, baudRate);
        setReadyRecieved(true);
        setErrorHandling(true);
    }
    catch (const SerialPortException &exception)
    {
        qWarning() << exception.what();
    }
    catch (const ArduinoException &exception)
    {
        qWarning() << exception.what();
    }

    emit connected(isConnected());
}

void Arduino::disconnect()
{
    try
    {
        if (!isConnected())
            throw ArduinoException("Arduino is not connected");

        serialPort_.reset();
    }
    catch (const SerialPortException &exception)
    {
        qWarning() << exception.what();
    }
    catch (const ArduinoException &exception)
    {
        qWarning() << exception.what();
    }

    emit connected(false);
}

bool Arduino::isConnected() const noexcept
{
    return (serialPort_ != nullptr);
}

void Arduino::sendMessage(const QString &message)
{
    try
    {
        if (!isConnected())
            throw ArduinoException("Arduino is not connected");

        serialPort_->send(message.toStdString().c_str(), message.size());
    }
    catch (const ArduinoException &exception)
    {
        qWarning() << exception.what();
    }
}

void Arduino::setErrorHandling(const bool on) noexcept
{
    if (on)
        QObject::connect(serialPort_.get(), &SerialPort::errorOccured, this, &Arduino::errorHandler);
    else
        QObject::disconnect(serialPort_.get(), &SerialPort::errorOccured, nullptr, nullptr);
}

void Arduino::setReadyRecieved(const bool ready) noexcept
{
    if (ready)
        QObject::connect(serialPort_.get(), &QSerialPort::readyRead, this, [this]() -> void {
            emit messageRecieved(serialPort_->recieve(serialPort_->bytesAvailable()));
        });
    else
        QObject::disconnect(serialPort_.get(), &QSerialPort::readyRead, nullptr, nullptr);
}

Arduino::Arduino() noexcept
    : QObject(nullptr)
    , serialPort_(nullptr)
{}

Arduino::~Arduino() noexcept {}

void Arduino::errorHandler(const QString &error)
{
    if (error == "ResourceError")
        disconnect();
}
