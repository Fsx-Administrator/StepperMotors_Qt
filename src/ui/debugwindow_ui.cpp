#include "debugwindow_ui.h"

#include "debugwindow.h"

#include <QVBoxLayout>


DebugWindow_Ui::DebugWindow_Ui(DebugWindow *parent)
    : console(new ArduinoDebugConsole(parent))
    , requestLineEdit(new QLineEdit(parent))
{
    auto widget = new QWidget(parent);
    auto layout = new QVBoxLayout(widget);
    layout->addWidget(requestLineEdit);
    layout->addWidget(console);
    widget->setLayout(layout);
    parent->setCentralWidget(widget);

    parent->setWindowFlag(Qt::MSWindowsFixedSizeDialogHint);
}
