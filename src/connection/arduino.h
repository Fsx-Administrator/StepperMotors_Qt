#pragma once

#include <QObject>


class ArduinoException : public std::runtime_error
{
public:
    ArduinoException(const QString &message) : std::runtime_error(message.toStdString()) {}
};


class ArduinoSerialPort;

class Arduino : public QObject
{
    Q_OBJECT

public:
    void connect(const QString &portName, const quint32 baudRate = 9600);
    void disconnect();
    [[nodiscard]] bool isConnected() const noexcept;
    static Arduino &instance()
    {
        static Arduino instance_;
        return instance_;
    }
    void sendMessage(const QString &message);
    void setErrorHandling(const bool on) noexcept;
    void setReadyRecieved(const bool ready) noexcept;

signals:
    void connected(bool successfully);
    void messageRecieved(const QByteArray &message);

protected:
    Arduino() noexcept;
    virtual ~Arduino() noexcept;

    Arduino(const Arduino &) = delete;
    Arduino(Arduino &&) = delete;
    Arduino &operator=(const Arduino &) = delete;
    Arduino &operator=(Arduino &&) = delete;

    virtual void errorHandler(const QString &error);

    std::unique_ptr<ArduinoSerialPort> serialPort_;

};
