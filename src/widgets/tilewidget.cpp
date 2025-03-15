#include "tilewidget.h"

#include <QGridLayout>
#include <QPushButton>


TileWidget::TileWidget(QWidget *parent) noexcept
    : QWidget(parent)
{
    QGridLayout *layout = new QGridLayout(this);
    setLayout(layout);

    setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
}

QPushButton *TileWidget::button(const Place place) const noexcept
{
    auto [row, column] = buttonPlace(place);
    auto layoutItem = static_cast<QGridLayout *>(layout())->itemAtPosition(row, column);

    if (layoutItem)
        return static_cast<QPushButton *>(layoutItem->widget());

    return nullptr;
}

void TileWidget::setButton(const Place place, const QString &name, Slot slot) noexcept
{
    auto b = button(place);

    if (!b)
    {
        b = new QPushButton(this);
        b->setToolTip(name);
        auto [row, column] = buttonPlace(place);
        static_cast<QGridLayout *>(layout())->addWidget(b, row, column);
    }

    disconnect(b, &QPushButton::clicked, nullptr, nullptr);
    connect(b, &QPushButton::clicked, this, [this, slot]() -> void { slot(); });
}

QPair<unsigned, unsigned> TileWidget::buttonPlace(const Place place) const
{
    return qMakePair(std::to_underlying(place) / 3, std::to_underlying(place) % 3);
}
