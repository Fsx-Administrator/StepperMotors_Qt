#pragma once

#include <QString>


class ArduinoParameters
{

public:
    using Position = int;
    using Coefficient = double;

    ArduinoParameters();
    ~ArduinoParameters();

    ArduinoParameters(const ArduinoParameters &other);
    ArduinoParameters(ArduinoParameters &&other);
    ArduinoParameters &operator=(const ArduinoParameters &other);
    ArduinoParameters &operator=(ArduinoParameters &&other);

    void calibrate();
    void setPositionToCenter();
    [[nodiscard]] Position distanceInDsc(Qt::Axis axis) const noexcept;
    [[nodiscard]] double distanceInUm(Qt::Axis axis) const noexcept;
    [[nodiscard]] double distanceStep() const noexcept;
    [[nodiscard]] static inline Position maxInDsc(Qt::Axis axis) { return maxes_[axis]; }
    [[nodiscard]] static inline double maxInUm(Qt::Axis axis) { return maxInDsc(axis) * coefficients_[axis]; }
    [[nodiscard]] QString positionAsString(Qt::Axis axis) const noexcept;
    void setDistanceInDsc(Qt::Axis axis, Position dsc);
    void setDistanceInUm(Qt::Axis axis, double um);

private:
    static inline std::array<Position, 3> maxes_ = {};
    static inline std::array<Coefficient, 3> coefficients_ = {};
    static inline const QString _FILE_NAME_ = "parameters.ini";

    void load();
    void save();

    std::array<Position, 3> positions_;

};
