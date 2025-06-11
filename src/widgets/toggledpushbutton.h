#pragma once

#include "common.h"

#include <QPushButton>


class ToggledPushButton : public QPushButton
{
    Q_OBJECT

public:
    explicit ToggledPushButton(
        QWidget *parent = nullptr,
        const QString &onTitle = QString(),
        const QString &offTitle = QString(),
        Slot onSlot = []() -> void {},
        Slot offSlot = []() -> void {}
    );
    ~ToggledPushButton() = default;

};
