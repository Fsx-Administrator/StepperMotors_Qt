#pragma once

#include "tilewidget.h"
#include <qglobal.h>

class KnobWidget final : public TileWidget
{
    Q_OBJECT

public:
    explicit KnobWidget(QWidget *parent = nullptr);
    ~KnobWidget() = default;

    void setButton(const Place place, const QString &name, Slot slot) override;

private:
    [[nodiscard]] QIcon knobIcon(const Place place) const noexcept;

    QMap<Place, QString> icons_;

};
