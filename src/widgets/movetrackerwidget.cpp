#include "movetrackerwidget.h"

#include "widgetsettings.h"

#include <QPen>
#include <QwtPlotShapeItem>
#include <QwtScaleWidget>


MoveTrackerWidget::MoveTrackerWidget(QWidget *parent) noexcept
    : QwtPlot(parent)
    , _MINIMUM_SIZE_(250, 250)
    , squareRect_(0, 0, 10, 10)
    , borderRect_(QPointF(), _MINIMUM_SIZE_)
    , squarePlotShapeItem_(new QwtPlotShapeItem)
    , borderPlotShapeItem_(new QwtPlotShapeItem)
    , settings_(std::make_unique<WidgetSettings>("MoveTrackerWidget"))
{
    setAxisVisible(QwtPlot::yLeft, false);
    setAxisVisible(QwtPlot::xBottom, false);

    borderPlotShapeItem_->setRect(borderRect_);
    borderPlotShapeItem_->setBrush(QBrush(Qt::gray));
    borderPlotShapeItem_->setPen(QPen(Qt::red, 1));
    borderPlotShapeItem_->attach(this);

    squarePlotShapeItem_->setRect(squareRect_);
    squarePlotShapeItem_->setBrush(QBrush(Qt::white));
    squarePlotShapeItem_->setPen(QPen(Qt::black, 1));
    squarePlotShapeItem_->attach(this);

    setFixedSize(_MINIMUM_SIZE_);

    if (settings_ != nullptr)
        setAspectRatio(settings_->get<double>("aspect_ratio"));
}

MoveTrackerWidget::~MoveTrackerWidget() noexcept
{
    if (settings_ != nullptr)
        settings_->set("aspect_ratio", aspectRatio_);
}

void MoveTrackerWidget::move(const double step, const Direction dir) noexcept
{
    auto destination = squareRect_.center();

    switch (dir)
    {
    case Direction::Down:
        destination.ry() -= step;
        break;

    case Direction::Left:
        destination.rx() -= step;
        break;

    case Direction::Right:
        destination.rx() += step;
        break;

    case Direction::Up:
        destination.ry() += step;
        break;
    }

    squareRect_.moveCenter(destination);
    squarePlotShapeItem_->setRect(squareRect_);
    replot();
}

void MoveTrackerWidget::setAspectRatio(const double aspectRatio) noexcept
{
    if (aspectRatio > 1.0)
        return;

    aspectRatio_ = aspectRatio;
    squareRect_.setSize(borderRect_.size() * aspectRatio);
    squarePlotShapeItem_->setRect(squareRect_);
    replot();
}

void MoveTrackerWidget::setPosition(const QPointF &destination) noexcept
{
    squareRect_.moveTopLeft(destination);
    squarePlotShapeItem_->setRect(squareRect_);
    replot();
}
