#pragma once

#include "common.h"

#include <QWidget>


class QPushButton;

class TileWidget : public QWidget
{
    Q_OBJECT

public:
    enum class Place : unsigned
    {
        TopLeft,
        Top,
        TopRight,
        Left,
        Central,
        Right,
        BottomLeft,
        Bottom,
        BottomRight
    };

    explicit TileWidget(QWidget *parent = nullptr) noexcept;
    virtual ~TileWidget() noexcept = default;

    virtual void setButton(const Place place, Slot slot) noexcept;
    [[nodiscard]] QPushButton *button(const Place place) const noexcept;

private:
    [[nodiscard]] QPair<unsigned, unsigned> buttonPlace(const Place place) const;

};
