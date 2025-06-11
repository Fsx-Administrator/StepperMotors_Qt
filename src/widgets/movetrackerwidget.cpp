#include "movetrackerwidget.h"

#include "widgetsettings.h"

#include <QPen>
#include <QwtPlotShapeItem>
#include <QwtScaleWidget>


MoveTrackerWidget::MoveTrackerWidget(QWidget *parent)
    : QwtPlot{parent}
    , _MINIMUM_SIZE_{200, 200}
    , squareRect_{QPointF{}, QSizeF{10, 10}}
    , borderRect_{QPointF{}, _MINIMUM_SIZE_}
    , squarePlotShapeItem_{new QwtPlotShapeItem}
    , borderPlotShapeItem_{new QwtPlotShapeItem}
    , settings_{std::make_unique<WidgetSettings>(this)}
{
    setAxisVisible(QwtPlot::yLeft, false);
    setAxisVisible(QwtPlot::xBottom, false);

    borderPlotShapeItem_->setRect(borderRect_);
    borderPlotShapeItem_->setBrush(QBrush{Qt::gray});
    borderPlotShapeItem_->setPen(QPen{Qt::red, 1});
    borderPlotShapeItem_->attach(this);

    squarePlotShapeItem_->setRect(squareRect_);
    squarePlotShapeItem_->setBrush(QBrush{Qt::white});
    squarePlotShapeItem_->setPen(QPen{Qt::black, 1});
    squarePlotShapeItem_->attach(this);

    setFixedSize(_MINIMUM_SIZE_);

    if (settings_ != nullptr)
    {
        setRange(QSizeF{settings_->get<double>("x_range"), settings_->get<double>("y_range")});
        setAspectRatio(settings_->get<double>("aspect_ratio"));
    }
}

MoveTrackerWidget::~MoveTrackerWidget() {}

void MoveTrackerWidget::setAspectRatio(double aspectRatio)
{
    if (aspectRatio > 1.0)
        return;

    aspectRatio_ = aspectRatio;
    squareRect_.setSize(borderRect_.size() * aspectRatio);
    squarePlotShapeItem_->setRect(squareRect_);
    replot();
}

void MoveTrackerWidget::setPosition(const QPointF &destination)
{
    squareRect_.moveTopRight(QPointF{borderRect_.right() - destination.x(), borderRect_.top() + destination.y()});

    squarePlotShapeItem_->setRect(squareRect_);
    replot();
}

void MoveTrackerWidget::setRange(const QSizeF &size)
{
    setAxisScale(Qt::XAxis, 0, size.width());
    setAxisScale(Qt::YAxis, 0, size.height());
    borderRect_.setSize(size);
    borderPlotShapeItem_->setRect(borderRect_);
}
