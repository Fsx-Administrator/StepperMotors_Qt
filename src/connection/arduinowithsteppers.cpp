#include "arduinowithsteppers.h"

#include <QDebug>
#include <QPointF>


void ArduinoWithSteppers::autoCalibrate()
{
    parameters_->calibrate();

    sendMessage(QString(Calibration) + positionsAsString());
}

void ArduinoWithSteppers::connect(const QString &portName, const quint32 baudRate)
{
    Arduino::connect(portName, baudRate);
    sendMessage(QString(SetPosition) + positionsAsString());
}

void ArduinoWithSteppers::manualCalibrate()
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

void ArduinoWithSteppers::moveToCenter()
{
    parameters_->setDistanceInDsc(ArduinoParameters::xAxisWithSwap(), ArduinoParameters::maxInDsc(Qt::XAxis) / 2);
    parameters_->setDistanceInDsc(ArduinoParameters::yAxisWithSwap(), ArduinoParameters::maxInDsc(Qt::YAxis) / 2);
    parameters_->setDistanceInDsc(Qt::ZAxis, 0);

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
    if (messageString[0] == GetPosition && messageString.size() > 6)
    {
        const auto list = messageString.sliced(2, messageString.size() - 2).split(',');
        parameters_->setDistanceInDsc(Qt::XAxis, ArduinoParameters::inverseFactor(ArduinoParameters::xAxisWithSwap()) * list[Qt::XAxis].toInt());
        parameters_->setDistanceInDsc(Qt::YAxis, ArduinoParameters::inverseFactor(ArduinoParameters::yAxisWithSwap()) * list[Qt::YAxis].toInt());
        parameters_->setDistanceInDsc(Qt::ZAxis, list[Qt::ZAxis].toInt());
    }
    else if (messageString[0] == Calibration)
    {
        parameters_->setDistanceInDsc(Qt::XAxis, 0);
        parameters_->setDistanceInDsc(Qt::YAxis, 0);
        parameters_->setDistanceInDsc(Qt::ZAxis, 0);

        sendMessage(QString(SetPosition) + positionsAsString());
    }

    emit distanceRecieved(QPointF(
        parameters_->distanceInUm(ArduinoParameters::xAxisWithSwap()),
        parameters_->distanceInUm(ArduinoParameters::yAxisWithSwap())
    ));

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
           + parameters_->positionAsString(Qt::XAxis) + _DELIMETER_
           + parameters_->positionAsString(Qt::YAxis) + _DELIMETER_
           + parameters_->positionAsString(Qt::ZAxis) + _TERMINATOR_;
}
