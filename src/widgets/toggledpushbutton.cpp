#include "toggledpushbutton.h"


ToggledPushButton::ToggledPushButton(
    QWidget *parent,
    const QString &onTitle,
    const QString &offTitle,
    Slot onSlot,
    Slot offSlot
) noexcept
    : QPushButton(parent)
{
    setCheckable(true);
    setChecked(false);
    setText(offTitle);
    connect(this, &QPushButton::toggled, [this, onTitle, offTitle, onSlot, offSlot](bool clicked) -> void {
        if (clicked)
        {
            setText(onTitle);
            onSlot();
        }
        else
        {
            setText(offTitle);
            offSlot();
        }
    });
}
