#pragma once

#include <QSerialPort>

#include <concepts>


template<class T>
concept Pointer = requires(T t) { *t; };
template<class T>
concept BuiltInType = std::integral<T> || std::floating_point<T>;


class SerialPortException : public std::runtime_error
{
public:
    SerialPortException(const QString &message) : std::runtime_error(message.toStdString()) {};
};


class SerialPort : public QSerialPort
{

public:
    explicit SerialPort(
        const QString &name,
        const qint32 baudRate = 9600
    );
    virtual ~SerialPort() noexcept;

    SerialPort(const SerialPort &) = delete;
    SerialPort(SerialPort &&) = delete;
    SerialPort &operator=(const SerialPort &) = delete;
    SerialPort &operator=(SerialPort &&) = delete;

    [[nodiscard]] QByteArray recieve(const std::size_t size) noexcept
    {
        return read(size);
    }

    template<Pointer T>
    [[nodiscard]] T recieve(const std::size_t size) noexcept
    {
        const auto byteArray = recieve(size);
        return reinterpret_cast<T>(byteArray.data());
    }

    template<BuiltInType T>
    [[nodiscard]] T recieve() noexcept
    {
        return *recieve<T*>(sizeof(T));
    }

    void send(const QByteArray data) noexcept
    {
        write(data);
    }

    void send(const Pointer auto data, const std::size_t size) noexcept
    {
        send(QByteArray(reinterpret_cast<const char *>(data), size));
    }

    void send(const BuiltInType auto data) noexcept
    {
        send(&data, sizeof(data));
    }

};
