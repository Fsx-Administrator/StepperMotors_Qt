#pragma once

#include <QString>


struct ArduinoParameters
{

public:
    using Position = int;
    using Coefficient = double;

    void load();
    void save();

    void setDistanceInDsc(const Qt::Axis axis, const Position dsc) noexcept;
    void setDistanceInUm(const Qt::Axis axis, const double um) noexcept;
    [[nodiscard]] Position distanceInDsc(const Qt::Axis axis) const noexcept;
    [[nodiscard]] double distanceInUm(const Qt::Axis axis) const noexcept;

private:
    static inline std::array<Coefficient, 3> coefficients_ = {};
    static inline const QString _FILE_NAME_ = "parameters.ini";

    std::array<Position, 3> positions_;

};
