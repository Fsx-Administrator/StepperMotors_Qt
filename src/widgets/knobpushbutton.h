#pragma once

#include <QPushButton>
#include <qglobal.h>

class KnobPushButton : public QPushButton
{
    Q_OBJECT

public:
    enum class Type : quint8
    {
        Central,
        Up,
        Right,
        Down,
        Left
    };

    explicit KnobPushButton(
        const Type type = Type::Central,
        QWidget *parent = nullptr
    ) noexcept;
    ~KnobPushButton() noexcept = default;

    void setType(const Type type) noexcept;

private:
    [[nodiscard]] QIcon knobIcon(const Type type) const noexcept;
    [[nodiscard]] QString knobText(const Type type) const noexcept;

};
