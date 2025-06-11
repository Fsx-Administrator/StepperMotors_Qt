#include "arduino.h"

#include "serialport.h"

#include <QDebug>


void Arduino::connect(const QString &portName, const quint32 baudRate)
{
    try
    {
        if (isConnected())
            throw ArduinoException("Arduino has already connected");

        serialPort_ = std::make_unique<SerialPort>(portName, baudRate);
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

bool Arduino::isConnected() const
{
    return (serialPort_ != nullptr);
}

void Arduino::sendMessage(const QString &message)
{
    try
    {
        if (!isConnected())
            throw ArduinoException("Arduino is not connected");

        // qDebug() << message;
        serialPort_->send(message.toStdString().c_str(), message.size());
    }
    catch (const ArduinoException &exception)
    {
        qWarning() << exception.what();
    }
}

void Arduino::setErrorHandling(bool on)
{
    (on)
        ? QObject::connect(serialPort_.get(), &SerialPort::errorOccured, this, &Arduino::errorHandler)
        : QObject::disconnect(serialPort_.get(), &SerialPort::errorOccured, nullptr, nullptr);
}

void Arduino::setReadyRecieved(bool ready)
{
    (ready)
        ? QObject::connect(serialPort_.get(), &QSerialPort::readyRead, this, [this]() -> void {
            emit messageRecieved(serialPort_->recieve(serialPort_->bytesAvailable()));
        })
        : QObject::disconnect(serialPort_.get(), &QSerialPort::readyRead, nullptr, nullptr);
}

Arduino::Arduino()
    : QObject{nullptr}
    , serialPort_{nullptr}
{}

Arduino::~Arduino() {}

void Arduino::errorHandler(const QString &error)
{
    if (error == "ResourceError")
        disconnect();
}
