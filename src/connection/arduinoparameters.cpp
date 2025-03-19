#include "arduinoparameters.h"

#include "inifile.h"
#include "inifilestorage.h"
#include "limiter.h"

#include <QDebug>


ArduinoParameters::ArduinoParameters() noexcept
    : positions_()
{
    load();
}

ArduinoParameters::~ArduinoParameters() noexcept
{
    save();
}

ArduinoParameters::ArduinoParameters(const ArduinoParameters &other) noexcept
{
    positions_ = other.positions_;
}

ArduinoParameters::ArduinoParameters(ArduinoParameters &&other) noexcept
{
    positions_ = std::move(other.positions_);
}

ArduinoParameters &ArduinoParameters::operator=(const ArduinoParameters &other) noexcept
{
    if (&other != this)
        positions_ = other.positions_;

    return *this;
}

void ArduinoParameters::calibrate()
{
    for (int axis = Qt::XAxis; axis < Qt::ZAxis; ++axis)
       positions_[axis] = -inverseFactor_[axis] * maxes_[axis];
}

ArduinoParameters &ArduinoParameters::operator=(ArduinoParameters &&other) noexcept
{
    if (&other != this)
        positions_ = std::move(other.positions_);

    return *this;
}

ArduinoParameters::Position ArduinoParameters::distanceInDsc(const Qt::Axis axis) const noexcept
{
    return inverseFactor_[axis] * positions_[axis];
}

double ArduinoParameters::distanceInUm(const Qt::Axis axis) const noexcept
{
    return distanceInDsc(axis) * coefficients_[axis];
}

double ArduinoParameters::distanceStep() const noexcept
{
    return std::min(coefficients_[Qt::XAxis], coefficients_[Qt::YAxis]);
}

QString ArduinoParameters::positionAsString(const Qt::Axis axis) const noexcept
{
    return QString::number(positions_[axis]);
}

void ArduinoParameters::setDistanceInDsc(const Qt::Axis axis, const Position dsc) noexcept
{
    positions_[axis] = inverseFactor_[axis] * Limiter::limitedValue(dsc, 0, maxes_[axis]);
}

void ArduinoParameters::setDistanceInUm(const Qt::Axis axis, const double um) noexcept
{
    setDistanceInDsc(axis, static_cast<Position>(std::round(um / coefficients_[axis])));
}

Qt::Axis ArduinoParameters::xAxisWithSwap()
{
    return (swapXy) ? (Qt::YAxis) : (Qt::XAxis);
}

Qt::Axis ArduinoParameters::yAxisWithSwap()
{
    return (swapXy) ? (Qt::XAxis) : (Qt::YAxis);
}

void ArduinoParameters::load()
{
    try
    {
        auto sectionsMap = IniFileStorage::load(_FILE_NAME_);

        positions_[Qt::XAxis] = sectionsMap.get<Position>("Positions", "x_dsc");
        positions_[Qt::YAxis] = sectionsMap.get<Position>("Positions", "y_dsc");
        positions_[Qt::ZAxis] = sectionsMap.get<Position>("Positions", "z_dsc");
        coefficients_[Qt::XAxis] = sectionsMap.get<Coefficient>("Coefficients", "x_um_dsc");
        coefficients_[Qt::YAxis] = sectionsMap.get<Coefficient>("Coefficients", "y_um_dsc");
        coefficients_[Qt::ZAxis] = sectionsMap.get<Coefficient>("Coefficients", "z_um_dsc");
        maxes_[Qt::XAxis] = sectionsMap.get<Position>("Max", "x_dsc");
        maxes_[Qt::YAxis] = sectionsMap.get<Position>("Max", "y_dsc");
        maxes_[Qt::ZAxis] = sectionsMap.get<Position>("Max", "z_dsc");
        inverseFactor_[Qt::XAxis] = sectionsMap.get<Position>("InverseFactor", "x");
        inverseFactor_[Qt::YAxis] = sectionsMap.get<Position>("InverseFactor", "y");
        inverseFactor_[Qt::ZAxis] = sectionsMap.get<Position>("InverseFactor", "z");
        swapXy = sectionsMap.get<bool>("Additional", "swap_xy");

        qDebug() << positions_[Qt::XAxis] << positions_[Qt::YAxis] << positions_[Qt::ZAxis];
        qDebug() << coefficients_[Qt::XAxis] << coefficients_[Qt::YAxis] << coefficients_[Qt::ZAxis];
        qDebug() << maxes_[Qt::XAxis] << maxes_[Qt::YAxis] << maxes_[Qt::ZAxis];
        qDebug() << inverseFactor_[Qt::XAxis] << inverseFactor_[Qt::YAxis] << inverseFactor_[Qt::ZAxis];
    }
    catch (const IniFileException &exception)
    {
        qWarning() << exception.what();
    }
}

void ArduinoParameters::save()
{
    SectionsMap sectionsMap;

    sectionsMap.set("Positions", "x", positions_[Qt::XAxis]);
    sectionsMap.set("Positions", "y", positions_[Qt::YAxis]);
    sectionsMap.set("Positions", "z", positions_[Qt::ZAxis]);

    try
    {
        IniFileStorage::save(_FILE_NAME_, sectionsMap);
    }
    catch (const IniFileException &exception)
    {
        qWarning() << exception.what();
    }
}
