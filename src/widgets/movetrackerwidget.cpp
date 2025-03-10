#include "movetrackerwidget.h"

#include "widgetsettings.h"

#include <QPen>
#include <QwtPlotShapeItem>
#include <QwtScaleWidget>


MoveTrackerWidget::MoveTrackerWidget(QWidget *parent) noexcept
    : QwtPlot(parent)
    , _MINIMUM_SIZE_(200, 200)
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
    {
        setRange(QSizeF(settings_->get<double>("x_range"), settings_->get<double>("y_range")));
        setAspectRatio(settings_->get<double>("aspect_ratio"));
        setPosition(QPointF(settings_->get<double>("x_origin"), settings_->get<double>("y_origin")));
    }
}

MoveTrackerWidget::~MoveTrackerWidget() noexcept
{
    settings_->set("x_origin", squareRect_.left());
    settings_->set("y_origin", squareRect_.top());
}

void MoveTrackerWidget::move(const double step, const Direction dir) noexcept
{
    auto destination = squareRect_.topLeft();

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

    squareRect_.moveTopLeft(destination);
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

void MoveTrackerWidget::setRange(const QSizeF &size) noexcept
{
    setAxisScale(Qt::XAxis, 0, size.width());
    setAxisScale(Qt::YAxis, 0, size.height());
    borderRect_.setSize(size);
    borderPlotShapeItem_->setRect(borderRect_);
}
