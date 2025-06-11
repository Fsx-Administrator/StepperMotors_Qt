#pragma once

#include "debugconsole.h"


class ArduinoDebugConsole final : public DebugConsole
{
    Q_OBJECT

public:
    explicit ArduinoDebugConsole(QWidget *parent = nullptr)
        : DebugConsole(parent)
    {}
    ~ArduinoDebugConsole() = default;

public slots:
    void appendConnectSection()
    {
        appendSection("Connected");
    }

    void appendDisconnectSection()
    {
        appendSection("Disconnected");
    }

};
