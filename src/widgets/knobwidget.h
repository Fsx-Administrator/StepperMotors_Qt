#pragma once

#include "common.h"
#include "knobpushbutton.h"

#include <QWidget>


class KnobWidget : public QWidget
{
    Q_OBJECT

public:
    explicit KnobWidget(QWidget *parent = nullptr) noexcept;
    ~KnobWidget() noexcept = default;

    void registerSlot(const KnobPushButton::Type type, Slot slot) noexcept;

private:
    std::array<KnobPushButton *, 5> knobPushButtons_;

};
