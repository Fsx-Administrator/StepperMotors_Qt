#include "arduinowithsteppers.h"

#include <QDebug>
#include <QPointF>


void ArduinoWithSteppers::calibrate()
{
    parameters_->setDistanceInDsc(Qt::XAxis, 0);
    parameters_->setDistanceInDsc(Qt::YAxis, 0);
    parameters_->setDistanceInDsc(Qt::ZAxis, 0);

    sendMessage(QString(SetPosition) + positionsAsString());
}

void ArduinoWithSteppers::move(const double distance, const Direction direction)
{
    switch (direction)
    {
    case Down:
        parameters_->setDistanceInUm(ArduinoParameters::yAxisWithSwap(), parameters_->distanceInUm(ArduinoParameters::yAxisWithSwap()) - distance);
        break;

    case Left:
        parameters_->setDistanceInUm(ArduinoParameters::xAxisWithSwap(), parameters_->distanceInUm(ArduinoParameters::xAxisWithSwap()) - distance);
        break;

    case Right:
        parameters_->setDistanceInUm(ArduinoParameters::xAxisWithSwap(), parameters_->distanceInUm(ArduinoParameters::xAxisWithSwap()) + distance);
        break;

    case Up:
        parameters_->setDistanceInUm(ArduinoParameters::yAxisWithSwap(), parameters_->distanceInUm(ArduinoParameters::yAxisWithSwap()) + distance);
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
    static QString messageString = QString();
    messageString += QString(message);
    if (!messageString.endsWith(';'))
        return;

    messageString = messageString.section(";", -2);
    if (message[0] == GetPosition && message.size() > 6)
    {
        const auto list = messageString.sliced(1, message.size() - 2).split(',');
        parameters_->setDistanceInDsc(Qt::XAxis, list[Qt::XAxis].toInt());
        parameters_->setDistanceInDsc(Qt::YAxis, list[Qt::YAxis].toInt());
        parameters_->setDistanceInDsc(Qt::ZAxis, list[Qt::ZAxis].toInt());

        emit distanceRecieved(QPointF(
            parameters_->distanceInUm(Qt::XAxis),
            parameters_->distanceInUm(Qt::YAxis)
        ));
    }

    messageString.clear();
}

ArduinoWithSteppers::ArduinoWithSteppers() noexcept
    : Arduino()
    , parameters_(std::make_unique<ArduinoParameters>())
{
    QObject::connect(this, &Arduino::messageRecieved, this, &ArduinoWithSteppers::recieveDistance);
}

ArduinoWithSteppers::~ArduinoWithSteppers() noexcept {}

QString ArduinoWithSteppers::positionsAsString() const noexcept
{
    return _DELIMETER_
           + QString::number(parameters_->distanceInDsc(Qt::XAxis)) + _DELIMETER_
           + QString::number(parameters_->distanceInDsc(Qt::YAxis)) + _DELIMETER_
           + QString::number(parameters_->distanceInDsc(Qt::ZAxis)) + _TERMINATOR_;
}
