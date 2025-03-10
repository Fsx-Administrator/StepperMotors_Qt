#pragma once

#include "tilewidget.h"
#include <qglobal.h>

class KnobWidget final : public TileWidget
{
    Q_OBJECT

public:
    explicit KnobWidget(QWidget *parent = nullptr) noexcept;
    ~KnobWidget() noexcept = default;

    void setButton(const Place place, Slot slot) noexcept override;

private:
    [[nodiscard]] QIcon knobIcon(const Place place) const noexcept;

};
