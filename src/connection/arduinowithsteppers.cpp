#include "arduinowithsteppers.h"

#include <QPointF>


void ArduinoWithSteppers::calibrate()
{
    parameters_.setDistanceInDsc(Qt::XAxis, 0);
    parameters_.setDistanceInDsc(Qt::YAxis, 0);
    parameters_.setDistanceInDsc(Qt::ZAxis, 0);

    sendMessage(QString(SetPosition) + positionsAsString());
}

void ArduinoWithSteppers::move(const double distance, const Direction direction)
{
    switch (direction)
    {
    case Down:
        parameters_.setDistanceInUm(Qt::YAxis, parameters_.distanceInUm(Qt::YAxis) - distance);
        break;

    case Left:
        parameters_.setDistanceInUm(Qt::XAxis, parameters_.distanceInUm(Qt::XAxis) - distance);
        break;

    case Right:
        parameters_.setDistanceInUm(Qt::XAxis, parameters_.distanceInUm(Qt::XAxis) + distance);
        break;

    case Up:
        parameters_.setDistanceInUm(Qt::YAxis, parameters_.distanceInUm(Qt::YAxis) + distance);
        break;
    }

    sendMessage(QString(Move) + positionsAsString());
}

void ArduinoWithSteppers::stop()
{
    sendMessage(QString(Stop) + _TERMINATOR_);
}

void ArduinoWithSteppers::recieveDistance(const QByteArray &message)
{
    QString messageString = QString(message);

    if (message[0] == GetPosition)
    {
        const auto list = messageString.sliced(1, message.size() - 2).split(',');
        parameters_.setDistanceInDsc(Qt::XAxis, list[Qt::XAxis].toInt());
        parameters_.setDistanceInDsc(Qt::YAxis, list[Qt::YAxis].toInt());
        parameters_.setDistanceInDsc(Qt::ZAxis, list[Qt::ZAxis].toInt());

        emit distanceRecieved(QPointF(
            parameters_.distanceInUm(Qt::XAxis),
            parameters_.distanceInUm(Qt::YAxis)
        ));
    }
}

ArduinoWithSteppers::ArduinoWithSteppers() noexcept
    : Arduino()
{
    parameters_.load();

    QObject::connect(this, &Arduino::messageRecieved, this, &ArduinoWithSteppers::recieveDistance);
}

ArduinoWithSteppers::~ArduinoWithSteppers() noexcept
{
    parameters_.save();
}

QString ArduinoWithSteppers::positionsAsString() const noexcept
{
    return _DELIMETER_
           + QString::number(parameters_.distanceInDsc(Qt::XAxis)) + _DELIMETER_
           + QString::number(parameters_.distanceInDsc(Qt::YAxis)) + _DELIMETER_
           + QString::number(parameters_.distanceInDsc(Qt::ZAxis)) + _TERMINATOR_;
}
