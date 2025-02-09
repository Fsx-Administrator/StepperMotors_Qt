#pragma once

#include <QPushButton>
#include <qglobal.h>

class ToggledPushButton : public QPushButton
{
    Q_OBJECT

public:
    using Slot = std::function<void()>;

    explicit ToggledPushButton(
        QWidget *parent = nullptr,
        const QString &onTitle = QString(),
        const QString &offTitle = QString(),
        Slot onSlot = [](){},
        Slot offSlot = [](){}
    );
    ~ToggledPushButton() = default;

};
