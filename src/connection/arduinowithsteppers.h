#pragma once

#include "arduino.h"
#include "arduinoparameters.h"


class ArduinoWithSteppers final : public Arduino
{
    Q_OBJECT

public:
    enum Direction
    {
        Down,
        Left,
        Right,
        Up
    };

    void calibrate();
    static ArduinoWithSteppers &instance()
    {
        static ArduinoWithSteppers instance_;
        return instance_;
    }
    void move(const double distance, const Direction direction);
    void stop();

signals:
    void distanceRecieved(const QPointF &position);

private slots:
    void recieveDistance(const QByteArray &message);

private:
    enum MessageType : char
    {
        GetPosition = 'g',
        Move        = 'm',
        SetPosition = 'p',
        Stop        = 's'
    };

    ArduinoWithSteppers() noexcept;
    ~ArduinoWithSteppers() noexcept;

    [[nodiscard]] QString positionsAsString() const noexcept;

    ArduinoParameters parameters_;

    const QString _DELIMETER_ = ",";
    const QString _TERMINATOR_ = ";";

};
