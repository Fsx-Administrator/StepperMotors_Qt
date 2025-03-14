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
    return *std::ranges::min_element(coefficients_);
}

void ArduinoParameters::setDistanceInDsc(const Qt::Axis axis, const Position dsc) noexcept
{
    positions_[axis] = Limiter::limitedValue(dsc, 0, maxes_[axis]);
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

        positions_[Qt::XAxis] = sectionsMap.get<Position>("Positions", "x");
        positions_[Qt::YAxis] = sectionsMap.get<Position>("Positions", "y");
        positions_[Qt::ZAxis] = sectionsMap.get<Position>("Positions", "z");
        coefficients_[Qt::XAxis] = sectionsMap.get<Coefficient>("Coefficients", "x_nm_dsc");
        coefficients_[Qt::YAxis] = sectionsMap.get<Coefficient>("Coefficients", "y_nm_dsc");
        coefficients_[Qt::ZAxis] = sectionsMap.get<Coefficient>("Coefficients", "z_nm_dsc");
        maxes_[Qt::XAxis] = sectionsMap.get<Position>("Max", "x");
        maxes_[Qt::YAxis] = sectionsMap.get<Position>("Max", "y");
        maxes_[Qt::ZAxis] = sectionsMap.get<Position>("Max", "z");
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
