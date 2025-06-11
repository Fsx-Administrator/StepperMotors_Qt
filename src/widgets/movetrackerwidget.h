#pragma once

#include <QwtPlot>


class QwtPlotShapeItem;
class WidgetSettings;

class MoveTrackerWidget : public QwtPlot
{
    Q_OBJECT

public:
    enum class Direction : qint8
    {
        Down,
        Left,
        Right,
        Up
    };

    explicit MoveTrackerWidget(QWidget *parent = nullptr);
    ~MoveTrackerWidget();

    // void move(const double step, const Direction dir);
    void setAspectRatio(double aspectRatio);
    void setPosition(const QPointF &destination);
    void setRange(const QSizeF &size);

private:
    const QSize _MINIMUM_SIZE_;

    QRectF squareRect_;
    QRectF borderRect_;
    QwtPlotShapeItem *squarePlotShapeItem_;
    QwtPlotShapeItem *borderPlotShapeItem_;
    std::unique_ptr<WidgetSettings> settings_;
    double aspectRatio_;

};
