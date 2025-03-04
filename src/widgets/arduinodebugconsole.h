#pragma once

#include "debugconsole.h"


class ArduinoDebugConsole final : public DebugConsole
{
    Q_OBJECT

public:
    explicit ArduinoDebugConsole(QWidget *parent = nullptr) noexcept
        : DebugConsole(parent)
    {}
    ~ArduinoDebugConsole() noexcept = default;

public slots:
    void appendConnectSection() noexcept
    {
        appendSection("Connected");
    }

    void appendDisconnectSection() noexcept
    {
        appendSection("Disconnected");
    }

};
