#pragma once

#include "common.h"

#include <QSerialPort>
#include <QVariant>


class SerialPortException : public std::runtime_error
{

public:
    SerialPortException(const QString &message)
        : std::runtime_error(message.toStdString())
    {};
    SerialPortException(const QSerialPort::SerialPortError error)
        : std::runtime_error(QVariant::fromValue(error).toString().toStdString())
    {};

};


class SerialPort : public QSerialPort
{
    Q_OBJECT

public:
    explicit SerialPort(
        const QString &name,
        const qint32 baudRate
    );
    virtual ~SerialPort();

    SerialPort(const SerialPort &) = delete;
    SerialPort(SerialPort &&) = delete;
    SerialPort &operator=(const SerialPort &) = delete;
    SerialPort &operator=(SerialPort &&) = delete;

    [[nodiscard]] QByteArray recieve(std::size_t size)
    {
        return read(size);
    }

    template<Pointer T>
    [[nodiscard]] T recieve(std::size_t size)
    {
        const auto byteArray = recieve(size);
        return reinterpret_cast<T>(byteArray.data());
    }

    template<BuiltInType T>
    [[nodiscard]] T recieve()
    {
        return *recieve<T *>(sizeof(T));
    }

    void send(const QByteArray &data)
    {
        clear(Output);
        write(data);
        waitForBytesWritten(100);
    }

    void send(const Pointer auto data, std::size_t size)
    {
        send(QByteArray{reinterpret_cast<const char *>(data), static_cast<qsizetype>(size)});
    }

    void send(BuiltInType auto data)
    {
        send(&data, sizeof(data));
    }

signals:
    void errorOccured(const QString &error);

};
