#include "arduinowithsteppers.h"

#include <QDebug>
#include <QPointF>


void ArduinoWithSteppers::autoCalibrate()
{
    parameters_->calibrate();

    sendMessage(QString{QChar{std::to_underlying(Calibration)}} + positionsAsString());
}

void ArduinoWithSteppers::connect(const QString &portName, const quint32 baudRate)
{
    Arduino::connect(portName, baudRate);
    sendMessage(QString{QChar{std::to_underlying(SetPosition)}} + positionsAsString());
}

QPointF ArduinoWithSteppers::currentPosition() const
{
    return QPointF{
        parameters_->distanceInUm(Qt::XAxis),
        parameters_->distanceInUm(Qt::YAxis)
    };
}

void ArduinoWithSteppers::manualCalibrate()
{
    parameters_->setDistanceInDsc(Qt::XAxis, 0);
    parameters_->setDistanceInDsc(Qt::YAxis, 0);
    parameters_->setDistanceInDsc(Qt::ZAxis, 0);

    sendMessage(QString{QChar{std::to_underlying(SetPosition)}} + positionsAsString());
    emit distanceRecieved(currentPosition());
}

void ArduinoWithSteppers::move(const double distance, const Direction direction)
{
    switch (direction)
    {
    case Down:
        parameters_->setDistanceInUm(Qt::YAxis, parameters_->distanceInUm(Qt::YAxis) - distance);
        break;

    case Left:
        parameters_->setDistanceInUm(Qt::XAxis, parameters_->distanceInUm(Qt::XAxis) - distance);
        break;

    case Right:
        parameters_->setDistanceInUm(Qt::XAxis, parameters_->distanceInUm(Qt::XAxis) + distance);
        break;

    case Up:
        parameters_->setDistanceInUm(Qt::YAxis, parameters_->distanceInUm(Qt::YAxis) + distance);
        break;
    }

    sendMessage(QString{QChar{std::to_underlying(Move)}} + positionsAsString());
}

void ArduinoWithSteppers::moveToCenter()
{
    parameters_->setPositionToCenter();

    sendMessage(QString{QChar{std::to_underlying(Move)}} + positionsAsString());
}

void ArduinoWithSteppers::stop()
{
    sendMessage(QString{QChar{std::to_underlying(Stop)}} + _TERMINATOR_);
}

void ArduinoWithSteppers::recieveDistance(const QByteArray &message)
{
    static QString messageString = QString{};
    messageString += QString{message};
    if (!messageString.endsWith(';'))
        return;

    const auto messageList = messageString.split(';');
    messageString = messageList[messageList.size() - 2];
    if (messageString[0].toLatin1() == GetPosition && messageString.size() > 6)
    {
        const auto list = messageString.sliced(2, messageString.size() - 2).split(',');
        parameters_->setDistanceInDsc(Qt::XAxis, list[Qt::XAxis].toInt());
        parameters_->setDistanceInDsc(Qt::YAxis, list[Qt::YAxis].toInt());
        parameters_->setDistanceInDsc(Qt::ZAxis, list[Qt::ZAxis].toInt());
    }
    else if (messageString[0].toLatin1() == Calibration)
    {
        parameters_->setDistanceInDsc(Qt::XAxis, 0);
        parameters_->setDistanceInDsc(Qt::YAxis, 0);
        parameters_->setDistanceInDsc(Qt::ZAxis, 0);

        sendMessage(QString{QChar{std::to_underlying(SetPosition)}} + positionsAsString());
    }

    emit distanceRecieved(currentPosition());

    messageString.clear();
}

ArduinoWithSteppers::ArduinoWithSteppers()
    : Arduino()
    , parameters_(std::make_unique<ArduinoParameters>())
{
    QObject::connect(this, &Arduino::messageRecieved, this, &ArduinoWithSteppers::recieveDistance);
}

ArduinoWithSteppers::~ArduinoWithSteppers() {}

QString ArduinoWithSteppers::positionsAsString() const noexcept
{
    return _DELIMETER_
           + parameters_->positionAsString(Qt::XAxis) + _DELIMETER_
           + parameters_->positionAsString(Qt::YAxis) + _DELIMETER_
           + parameters_->positionAsString(Qt::ZAxis) + _TERMINATOR_;
}
