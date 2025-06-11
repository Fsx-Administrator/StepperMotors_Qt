#pragma once

#include "distancevaluewidget.h"
#include "knobwidget.h"
#include "maintoolbar.h"
#include "mainwindow.h"
#include "movetrackerwidget.h"
#include "positionlabel.h"

#include <QPointer>
#include <QPushButton>


class MainWindow_Ui
{

public:
    explicit MainWindow_Ui(MainWindow *parent);
    ~MainWindow_Ui() = default;

    MainWindow_Ui(const MainWindow_Ui &) = delete;
    MainWindow_Ui(MainWindow_Ui &&) = delete;
    MainWindow_Ui &operator=(const MainWindow_Ui &) = delete;
    MainWindow_Ui &operator=(MainWindow_Ui &&) = delete;

    QPointer<MainToolBar> mainToolBar;
    QPointer<DistanceValueWidget> distanceValueWidget;
    QPointer<KnobWidget> knobWidget;
    QPointer<MoveTrackerWidget> moveTrackerWidget;
    QPointer<PositionLabel> positionLabel;

    QMap<TileWidget::Place, QString> tileWidgetButtonNames;

};
