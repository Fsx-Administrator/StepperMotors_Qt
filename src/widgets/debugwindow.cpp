#include "debugwindow.h"
#include "debugwindow_ui.h"

#include "arduinowithsteppers.h"


DebugWindow::DebugWindow(QWidget *parent) noexcept
    : QMainWindow(parent)
    , ui(new DebugWindow_Ui(this))
{
    connect(ui->requestLineEdit, &QLineEdit::returnPressed, this, [this]() -> void {
        ui->console->appendRequest(ui->requestLineEdit->text());
        ArduinoWithSteppers::instance().sendMessage(ui->requestLineEdit->text());
        ui->requestLineEdit->clear();
    });
    connect(&ArduinoWithSteppers::instance(), &Arduino::messageRecieved, ui->console, &DebugConsole::appendAnswer);
    connect(&ArduinoWithSteppers::instance(), &Arduino::connected, this, [this](const bool successfully) -> void {
        qDebug() << "here";
        if (successfully)
            ui->console->appendConnectSection();
        else
            ui->console->appendDisconnectSection();
    });
}

DebugWindow::~DebugWindow() noexcept {}
