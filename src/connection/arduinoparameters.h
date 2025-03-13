#pragma once

#include <QString>


struct ArduinoParameters
{

public:
    using Position = int;
    using Coefficient = double;

    void load();
    void save();

    [[nodiscard]] Position distanceInDsc(const Qt::Axis axis) const noexcept;
    [[nodiscard]] double distanceInUm(const Qt::Axis axis) const noexcept;
    [[nodiscard]] double distanceStep() const noexcept;
    [[nodiscard]] static inline Position maxInDsc(const Qt::Axis axis) noexcept { return maxes_[axis]; }
    [[nodiscard]] static inline Position maxInUm(const Qt::Axis axis) noexcept { return maxInDsc(axis) * coefficients_[axis]; }
    void setDistanceInDsc(const Qt::Axis axis, const Position dsc) noexcept;
    void setDistanceInUm(const Qt::Axis axis, const double um) noexcept;

private:
    static inline std::array<Position, 3> maxes_ = {};
    static inline std::array<Coefficient, 3> coefficients_ = {};
    static inline const QString _FILE_NAME_ = "parameters.ini";

    std::array<Position, 3> positions_;

};
