#include "positionlabel.h"

#include "widgetsettings.h"

#include <QLabel>
#include <QVBoxLayout>


PositionLabel::PositionLabel(QWidget *parent) noexcept
    : QWidget(parent)
    , xPositionLabel_(new QLabel(this))
    , yPositionLabel_(new QLabel(this))
    , settings_(std::make_unique<WidgetSettings>(this))
{
    auto layout = new QVBoxLayout(this);
    layout->addWidget(new QLabel("Position:", this));
    layout->addWidget(xPositionLabel_);
    layout->addWidget(yPositionLabel_);
    setLayout(layout);

    if (settings_ != nullptr)
        setPosition(QPointF(settings_->get<double>("x_origin"), settings_->get<double>("y_origin")));
}

PositionLabel::~PositionLabel() noexcept {}

void PositionLabel::setPosition(const QPointF &position) noexcept
{
    xPositionLabel_->setText(_X_POSITION_LABEL_PATTERN_.arg(QString::number(position.x())));
    yPositionLabel_->setText(_Y_POSITION_LABEL_PATTERN_.arg(QString::number(position.y())));
}
