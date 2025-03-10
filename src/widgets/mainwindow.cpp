#include "mainwindow.h"

#include "arduinowithsteppers.h"
#include "mainwindow_ui.h"


MainWindow::MainWindow(QWidget *parent) noexcept
    : QMainWindow(parent)
    , ui(new MainWindow_Ui(this))
{
    ui->knobWidget->setButton(TileWidget::Place::Bottom, [this]() -> void {
        ArduinoWithSteppers::instance().move(ui->distanceValueWidget->distance(), ArduinoWithSteppers::Down);
        ui->moveTrackerWidget->move(ui->distanceValueWidget->distance(), MoveTrackerWidget::Direction::Down);
    });
    ui->knobWidget->setButton(TileWidget::Place::Left, [this]() -> void {
        ArduinoWithSteppers::instance().move(ui->distanceValueWidget->distance(), ArduinoWithSteppers::Left);
        ui->moveTrackerWidget->move(ui->distanceValueWidget->distance(), MoveTrackerWidget::Direction::Left);
    });
    ui->knobWidget->setButton(TileWidget::Place::Right, [this]() -> void {
        ArduinoWithSteppers::instance().move(ui->distanceValueWidget->distance(), ArduinoWithSteppers::Right);
        ui->moveTrackerWidget->move(ui->distanceValueWidget->distance(), MoveTrackerWidget::Direction::Right);
    });
    ui->knobWidget->setButton(TileWidget::Place::Top, [this]() -> void {
        ArduinoWithSteppers::instance().move(ui->distanceValueWidget->distance(), ArduinoWithSteppers::Up);
        ui->moveTrackerWidget->move(ui->distanceValueWidget->distance(), MoveTrackerWidget::Direction::Up);
    });
    ui->knobWidget->setButton(TileWidget::Place::Central, [this]() -> void {
        ArduinoWithSteppers::instance().stop();
    });
    ui->knobWidget->setButton(TileWidget::Place::BottomRight, [this]() -> void {
        ArduinoWithSteppers::instance().calibrate();
        ui->moveTrackerWidget->setPosition(QPointF(0.0, 0.0));
    });

    connect(
        &ArduinoWithSteppers::instance(), &ArduinoWithSteppers::distanceRecieved,
        this, [this](const QPointF positions) -> void {
            ui->moveTrackerWidget->setPosition(positions);
        }
    );
}

MainWindow::~MainWindow() noexcept {}
