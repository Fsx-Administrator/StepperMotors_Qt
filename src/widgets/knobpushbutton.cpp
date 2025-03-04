#include "knobpushbutton.h"


KnobPushButton::KnobPushButton(const Type type, QWidget *parent) noexcept
    : QPushButton(parent)
{
    setFixedSize(32, 32);
    setType(type);
}

void KnobPushButton::setType(const Type type) noexcept
{
    setIcon(knobIcon(type));
    setToolTip(knobText(type));
}

QIcon KnobPushButton::knobIcon(const Type type) const noexcept
{
    if (type == Type::Central)
        return QIcon(":/icons/central.png");
    else
        return QIcon(
            QIcon(":/icons/arrow.png")
            .pixmap(QSize(32, 32))
            .transformed(QTransform().rotate(
                (static_cast<quint32>(type) - 1) * 90.0,
                Qt::ZAxis
            ))
        );
}

QString KnobPushButton::knobText(const Type type) const noexcept
{
    switch (type)
    {
    case Type::Central:
        return "Central";

    case Type::Down:
        return "Down";

    case Type::Left:
        return "Left";

    case Type::Right:
        return "Right";

    case Type::Up:
        return "Up";
    }

    return QString();
}
