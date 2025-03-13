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

    explicit MoveTrackerWidget(QWidget *parent = nullptr) noexcept;
    ~MoveTrackerWidget() noexcept;

    // void move(const double step, const Direction dir) noexcept;
    void setAspectRatio(const double aspectRatio) noexcept;
    void setPosition(const QPointF &destination) noexcept;
    void setRange(const QSizeF &size) noexcept;

private:
    const QSize _MINIMUM_SIZE_;

    QRectF squareRect_;
    QRectF borderRect_;
    QwtPlotShapeItem *squarePlotShapeItem_;
    QwtPlotShapeItem *borderPlotShapeItem_;
    std::unique_ptr<WidgetSettings> settings_;
    double aspectRatio_;

};
