#include "mainwindow_ui.h"

#include <QGridLayout>


MainWindow_Ui::MainWindow_Ui(MainWindow *parent) noexcept
    : mainToolBar(new MainToolBar(parent))
    , distanceValueWidget(new DistanceValueWidget(parent))
    , knobWidget(new KnobWidget(parent))
    , moveTrackerWidget(new MoveTrackerWidget(parent))
    , positionLabel(new PositionLabel(parent))
{
    parent->addToolBar(mainToolBar);
    auto *widget = new QWidget(parent);
    auto *layout = new QGridLayout(widget);
    layout->addWidget(distanceValueWidget, 0, 0, 1, 2, Qt::AlignRight);
    layout->addWidget(knobWidget, 1, 0, 1, 1, Qt::AlignHCenter);
    layout->addWidget(positionLabel, 1, 1, 1, 1, Qt::AlignHCenter);
    layout->addWidget(moveTrackerWidget, 0, 2, 2, 1, Qt::AlignHCenter);
    widget->setLayout(layout);
    parent->setCentralWidget(widget);

    parent->setWindowFlag(Qt::MSWindowsFixedSizeDialogHint);
}
