#pragma once

#include "arduinodebugconsole.h"

#include <QLineEdit>
#include <QPointer>


class DebugWindow;

class DebugWindow_Ui
{

public:
    explicit DebugWindow_Ui(DebugWindow *parent);
    ~DebugWindow_Ui() noexcept = default;

    DebugWindow_Ui(const DebugWindow_Ui &) = delete;
    DebugWindow_Ui(DebugWindow_Ui &&) = delete;
    DebugWindow_Ui &operator=(const DebugWindow_Ui &) = delete;
    DebugWindow_Ui &operator=(DebugWindow_Ui &&) = delete;

    QPointer<ArduinoDebugConsole> console;
    QPointer<QLineEdit> requestLineEdit;

};
