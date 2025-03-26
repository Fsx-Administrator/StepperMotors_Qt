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
    positions_[Qt::XAxis] = -(maxes_[Qt::XAxis] + 800.0 / coefficients_[Qt::XAxis]);
    positions_[Qt::YAxis] = maxes_[Qt::YAxis] + 800.0 / coefficients_[Qt::YAxis];
}

void ArduinoParameters::setPositionToCenter()
{
    positions_[Qt::XAxis] = maxes_[Qt::XAxis] / 2;
    positions_[Qt::YAxis] = -maxes_[Qt::YAxis] / 2;
}

ArduinoParameters &ArduinoParameters::operator=(ArduinoParameters &&other) noexcept
{
    if (&other != this)
        positions_ = std::move(other.positions_);

    return *this;
}

ArduinoParameters::Position ArduinoParameters::distanceInDsc(const Qt::Axis axis) const noexcept
{
    return positions_[axis];
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
    if (axis == Qt::XAxis)
        positions_[axis] = Limiter::limitedValue(dsc, 0, maxes_[axis]);
    else
        positions_[axis] = Limiter::limitedValue(dsc, -maxes_[axis], 0);
}

void ArduinoParameters::setDistanceInUm(const Qt::Axis axis, const double um) noexcept
{
    setDistanceInDsc(axis, static_cast<Position>(std::round(um / coefficients_[axis])));
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
        swapXy = sectionsMap.get<bool>("Additional", "swap_xy");
    }
    catch (const IniFileException &exception)
    {
        qWarning() << exception.what();
    }
}

void ArduinoParameters::save()
{
    SectionsMap sectionsMap;

    sectionsMap.set("Positions", "x_dsc", positions_[Qt::XAxis]);
    sectionsMap.set("Positions", "y_dsc", positions_[Qt::YAxis]);
    sectionsMap.set("Positions", "z_dsc", positions_[Qt::ZAxis]);

    try
    {
        IniFileStorage::save(_FILE_NAME_, sectionsMap);
    }
    catch (const IniFileException &exception)
    {
        qWarning() << exception.what();
    }
}
