#include "knobwidget.h"

#include <QPushButton>


KnobWidget::KnobWidget(QWidget *parent) noexcept
    : TileWidget(parent)
    , icons_({
        { Place::TopLeft, ":/icons/manual_calibrate.png" },
        { Place::Top, ":/icons/arrow_up.png" },
        { Place::Left, ":/icons/arrow_left.png" },
        { Place::Central, ":/icons/center.png" },
        { Place::Right, ":/icons/arrow_right.png" },
        { Place::BottomLeft, ":/icons/auto_calibrate.png" },
        { Place::Bottom, ":/icons/arrow_down.png" },
        { Place::BottomRight, ":/icons/stop.png" }
    })
{}

void KnobWidget::setButton(const Place place, const QString &name, Slot slot) noexcept
{
    TileWidget::setButton(place, name, slot);
    button(place)->setIcon(knobIcon(place));
}

QIcon KnobWidget::knobIcon(const Place place) const noexcept
{
    return QIcon(icons_[place]);
}
