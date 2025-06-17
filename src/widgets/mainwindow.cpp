#include "mainwindow.h"

#include "arduinowithsteppers.h"
#include "mainwindow_ui.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow{parent}
    , ui{new MainWindow_Ui{this}}
{
    ui->knobWidget->setButton(TileWidget::Place::TopLeft, ui->tileWidgetButtonNames[TileWidget::Place::TopLeft], [this]() -> void {
        if (ArduinoWithSteppers::instance().isConnected() && ui->distanceValueWidget->distance() > std::numeric_limits<double>::epsilon())
            ArduinoWithSteppers::instance().manualCalibrate();
    });
    ui->knobWidget->setButton(TileWidget::Place::Top, ui->tileWidgetButtonNames[TileWidget::Place::Top], [this]() -> void {
        if (ArduinoWithSteppers::instance().isConnected() && ui->distanceValueWidget->distance() > std::numeric_limits<double>::epsilon())
            ArduinoWithSteppers::instance().move(ui->distanceValueWidget->distance(), ArduinoWithSteppers::Up);
    });
    ui->knobWidget->setButton(TileWidget::Place::Left, ui->tileWidgetButtonNames[TileWidget::Place::Left], [this]() -> void {
        if (ArduinoWithSteppers::instance().isConnected() && ui->distanceValueWidget->distance() > std::numeric_limits<double>::epsilon())
            ArduinoWithSteppers::instance().move(ui->distanceValueWidget->distance(), ArduinoWithSteppers::Right);
    });
    ui->knobWidget->setButton(TileWidget::Place::Central, ui->tileWidgetButtonNames[TileWidget::Place::Central], [this]() -> void {
        if (ArduinoWithSteppers::instance().isConnected())
            ArduinoWithSteppers::instance().moveToCenter();
    });
    ui->knobWidget->setButton(TileWidget::Place::Right, ui->tileWidgetButtonNames[TileWidget::Place::Right], [this]() -> void {
        if (ArduinoWithSteppers::instance().isConnected() && ui->distanceValueWidget->distance() > std::numeric_limits<double>::epsilon())
            ArduinoWithSteppers::instance().move(ui->distanceValueWidget->distance(), ArduinoWithSteppers::Left);
    });
    ui->knobWidget->setButton(TileWidget::Place::BottomLeft, ui->tileWidgetButtonNames[TileWidget::Place::BottomLeft], [this]() -> void {
        if (ArduinoWithSteppers::instance().isConnected() && ui->distanceValueWidget->distance() > std::numeric_limits<double>::epsilon())
            ArduinoWithSteppers::instance().autoCalibrate();
    });
    ui->knobWidget->setButton(TileWidget::Place::Bottom, ui->tileWidgetButtonNames[TileWidget::Place::Bottom], [this]() -> void {
        if (ArduinoWithSteppers::instance().isConnected() && ui->distanceValueWidget->distance() > std::numeric_limits<double>::epsilon())
            ArduinoWithSteppers::instance().move(ui->distanceValueWidget->distance(), ArduinoWithSteppers::Down);
    });
    ui->knobWidget->setButton(TileWidget::Place::BottomRight, ui->tileWidgetButtonNames[TileWidget::Place::BottomRight], [this]() -> void {
        if (ArduinoWithSteppers::instance().isConnected())
            ArduinoWithSteppers::instance().stop();
    });

    connect(
        &ArduinoWithSteppers::instance(), &ArduinoWithSteppers::distanceRecieved,
        this, [this](const QPointF &position) -> void {
            ui->moveTrackerWidget->setPosition(position);
            ui->positionLabel->setPosition(position);
        }
    );

    ui->positionLabel->setPosition(ArduinoWithSteppers::instance().currentPosition());
    ui->moveTrackerWidget->setPosition(ArduinoWithSteppers::instance().currentPosition());
}

MainWindow::~MainWindow() {}
