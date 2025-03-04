#include "mainwindow.h"

#include "arduinowithsteppers.h"
#include "mainwindow_ui.h"


MainWindow::MainWindow(QWidget *parent) noexcept
    : QMainWindow(parent)
    , ui(new MainWindow_Ui(this))
{
    ui->knobWidget->registerSlot(KnobPushButton::Type::Down, [this]() -> void {
        ArduinoWithSteppers::instance().move(ui->distanceValueWidget->distance(), ArduinoWithSteppers::Down);
        ui->moveTrackerWidget->move(ui->distanceValueWidget->distance(), MoveTrackerWidget::Direction::Down);
    });
    ui->knobWidget->registerSlot(KnobPushButton::Type::Left, [this]() -> void {
        ArduinoWithSteppers::instance().move(ui->distanceValueWidget->distance(), ArduinoWithSteppers::Left);
        ui->moveTrackerWidget->move(ui->distanceValueWidget->distance(), MoveTrackerWidget::Direction::Left);
    });
    ui->knobWidget->registerSlot(KnobPushButton::Type::Right, [this]() -> void {
        ArduinoWithSteppers::instance().move(ui->distanceValueWidget->distance(), ArduinoWithSteppers::Right);
        ui->moveTrackerWidget->move(ui->distanceValueWidget->distance(), MoveTrackerWidget::Direction::Right);
    });
    ui->knobWidget->registerSlot(KnobPushButton::Type::Up, [this]() -> void {
        ArduinoWithSteppers::instance().move(ui->distanceValueWidget->distance(), ArduinoWithSteppers::Up);
        ui->moveTrackerWidget->move(ui->distanceValueWidget->distance(), MoveTrackerWidget::Direction::Up);
    });
    ui->knobWidget->registerSlot(KnobPushButton::Type::Central, [this]() -> void {
        ArduinoWithSteppers::instance().stop();
    });

    connect(
        ui->calibratePushButton, &QPushButton::clicked,
        this, [this]() -> void {
            ArduinoWithSteppers::instance().calibrate();
            ui->moveTrackerWidget->setPosition(QPointF(0.0, 0.0));
        }
    );
    connect(
        &ArduinoWithSteppers::instance(), &ArduinoWithSteppers::distanceRecieved,
        this, [this](const QPointF positions) -> void {
            ui->moveTrackerWidget->setPosition(positions);
        }
    );
}

MainWindow::~MainWindow() noexcept {}
