#include "knobwidget.h"

#include <QGridLayout>
#include <QPushButton>


KnobWidget::KnobWidget(QWidget *parent) noexcept
    : QWidget(parent)
    , knobPushButtons_()
{
    std::ranges::generate(knobPushButtons_, [this, i = 0]() mutable -> auto {
        return new KnobPushButton(static_cast<KnobPushButton::Type>(i++), this);
    });

    QGridLayout *layout = new QGridLayout(this);
    layout->addWidget(knobPushButtons_[std::to_underlying(KnobPushButton::Type::Up)], 0, 1);
    layout->addWidget(knobPushButtons_[std::to_underlying(KnobPushButton::Type::Left)], 1, 0);
    layout->addWidget(knobPushButtons_[std::to_underlying(KnobPushButton::Type::Central)], 1, 1);
    layout->addWidget(knobPushButtons_[std::to_underlying(KnobPushButton::Type::Right)], 1, 2);
    layout->addWidget(knobPushButtons_[std::to_underlying(KnobPushButton::Type::Down)], 2, 1);
    setLayout(layout);

    setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
}

void KnobWidget::registerSlot(const KnobPushButton::Type type, Slot slot) noexcept
{
    auto button = knobPushButtons_[std::to_underlying(type)];
    disconnect(button, &QPushButton::clicked, nullptr, nullptr);
    connect(button, &QPushButton::clicked, this, [slot]() -> void { slot(); });
}
