#pragma once

#include "serialport.h"


class ArduinoSerialPort : public SerialPort
{
    Q_OBJECT

public:
    explicit ArduinoSerialPort(
        const QString &name,
        const quint32 baudRate = 9600
    );
    ~ArduinoSerialPort() noexcept = default;

    ArduinoSerialPort(const ArduinoSerialPort &) = delete;
    ArduinoSerialPort(ArduinoSerialPort &&) = delete;
    ArduinoSerialPort &operator=(const ArduinoSerialPort &) = delete;
    ArduinoSerialPort &operator=(ArduinoSerialPort &&) = delete;

private:
    [[nodiscard]] static QString arduinoPortName(const QString &name) noexcept;
    [[nodiscard]] static bool isArduinoPort(const QSerialPortInfo &info) noexcept;

};
