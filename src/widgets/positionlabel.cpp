#include "positionlabel.h"

#include "arduinoparameters.h"
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

PositionLabel::~PositionLabel() noexcept
{
    settings_->set("x_origin", QVariant::fromValue(position_.x()));
    settings_->set("y_origin", QVariant::fromValue(position_.y()));
}

void PositionLabel::setPosition(const QPointF &position) noexcept
{
    position_ = position;
    xPositionLabel_->setText(_X_POSITION_LABEL_PATTERN_.arg(QString::number(position.x()), QString::number(ArduinoParameters::maxInUm(Qt::XAxis))));
    yPositionLabel_->setText(_Y_POSITION_LABEL_PATTERN_.arg(QString::number(position.y()), QString::number(ArduinoParameters::maxInUm(Qt::YAxis))));
}
