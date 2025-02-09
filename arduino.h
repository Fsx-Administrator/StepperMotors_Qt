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
    static Arduino &instance()
    {
        static Arduino instance_;
        return instance_;
    }

signals:
    void connected();
    void disconnected();

private:
    Arduino();
    ~Arduino();

    Arduino(const Arduino &) = delete;
    Arduino(Arduino &&) = delete;
    Arduino &operator=(const Arduino &) = delete;
    Arduino &operator=(Arduino &&) = delete;

    std::unique_ptr<ArduinoSerialPort> serialPort_;


};
