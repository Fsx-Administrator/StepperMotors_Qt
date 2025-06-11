#pragma once

#include <QWidget>


class QLabel;
class WidgetSettings;

class PositionLabel : public QWidget
{
    Q_OBJECT

public:
    explicit PositionLabel(QWidget *parent = nullptr);
    ~PositionLabel();

public slots:
    void setPosition(const QPointF &position);

private:
    QLabel *xPositionLabel_;
    QLabel *yPositionLabel_;
    QPointF position_;

    const QString _X_POSITION_LABEL_PATTERN_ = "x = %1/%2 um";
    const QString _Y_POSITION_LABEL_PATTERN_ = "y = %1/%2 um";

};
