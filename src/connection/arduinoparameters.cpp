#include "arduinoparameters.h"

#include "inifilestorage.h"


void ArduinoParameters::load()
{
    auto sectionsMap = IniFileStorage::load(_FILE_NAME_);

    positions_[Qt::XAxis] = sectionsMap.get<Position>("Positions", "x");
    positions_[Qt::YAxis] = sectionsMap.get<Position>("Positions", "y");
    positions_[Qt::ZAxis] = sectionsMap.get<Position>("Positions", "z");
    coefficients_[Qt::XAxis] = sectionsMap.get<Coefficient>("Coefficients", "x_nm_dsc");
    coefficients_[Qt::YAxis] = sectionsMap.get<Coefficient>("Coefficients", "y_nm_dsc");
    coefficients_[Qt::ZAxis] = sectionsMap.get<Coefficient>("Coefficients", "z_nm_dsc");
}

void ArduinoParameters::save()
{
    SectionsMap sectionsMap;

    sectionsMap.set("Positions", "x", positions_[Qt::XAxis]);
    sectionsMap.set("Positions", "y", positions_[Qt::YAxis]);
    sectionsMap.set("Positions", "z", positions_[Qt::ZAxis]);

    IniFileStorage::save(_FILE_NAME_, sectionsMap);
}

ArduinoParameters::Position ArduinoParameters::distanceInDsc(const Qt::Axis axis) const noexcept
{
    return positions_[axis];
}

double ArduinoParameters::distanceInUm(const Qt::Axis axis) const noexcept
{
    return positions_[axis] * coefficients_[axis];
}

double ArduinoParameters::distanceStep() const noexcept
{
    return *std::ranges::min_element(coefficients_);
}

void ArduinoParameters::setDistanceInDsc(const Qt::Axis axis, const Position dsc) noexcept
{
    positions_[axis] = dsc;
}

void ArduinoParameters::setDistanceInUm(const Qt::Axis axis, const double um) noexcept
{
    positions_[axis] = static_cast<Position>(std::round(um / coefficients_[axis]));
}
