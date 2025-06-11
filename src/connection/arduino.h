#pragma once

#include <QObject>


class ArduinoException : public std::runtime_error
{
public:
    ArduinoException(const QString &message) : std::runtime_error{message.toStdString()} {}
};


class SerialPort;

class Arduino : public QObject
{
    Q_OBJECT

public:
    virtual void connect(const QString &portName, const quint32 baudRate = 9600);
    void disconnect();
    [[nodiscard]] bool isConnected() const;
    static Arduino &instance()
    {
        static Arduino instance_;
        return instance_;
    }
    void sendMessage(const QString &message);
    void setErrorHandling(bool on);
    void setReadyRecieved(bool ready);

signals:
    void connected(bool successfully);
    void messageRecieved(const QByteArray &message);

protected:
    Arduino();
    virtual ~Arduino();

    Arduino(const Arduino &) = delete;
    Arduino(Arduino &&) = delete;
    Arduino &operator=(const Arduino &) = delete;
    Arduino &operator=(Arduino &&) = delete;

    virtual void errorHandler(const QString &error);

    std::unique_ptr<SerialPort> serialPort_;

};
