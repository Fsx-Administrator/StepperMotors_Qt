#include "knobwidget.h"

#include <QPushButton>


KnobWidget::KnobWidget(QWidget *parent) noexcept
    : TileWidget(parent)
{}

void KnobWidget::setButton(const Place place, Slot slot) noexcept
{
    switch (place)
    {
    case TileWidget::Place::BottomLeft:
    case TileWidget::Place::TopLeft:
    case TileWidget::Place::TopRight:
        return;

    default:
        break;
    }

    TileWidget::setButton(place, slot);
    button(place)->setIcon(knobIcon(place));
}

QIcon KnobWidget::knobIcon(const Place place) const noexcept
{
    switch (place)
    {
    case TileWidget::Place::Top:
        return QIcon(":/icons/arrow_up.png");

    case TileWidget::Place::Left:
        return QIcon(":/icons/arrow_left.png");

    case TileWidget::Place::Central:
        return QIcon(":/icons/central.png");

    case TileWidget::Place::Right:
        return QIcon(":/icons/arrow_right.png");

    case TileWidget::Place::Bottom:
        return QIcon(":/icons/arrow_down.png");

    case TileWidget::Place::BottomRight:
        return QIcon(":/icons/calibrate.png");

    default:
        return QIcon();
    }
}
