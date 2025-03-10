#pragma once

#include <QMainWindow>
#include <QPointer>


class DebugWindow_Ui;

class DebugWindow final : public QMainWindow
{
    Q_OBJECT

public:
    explicit DebugWindow(QWidget *parent = nullptr) noexcept;
    ~DebugWindow() noexcept;

signals:
    void messageSent(const QString &message);

private:
    QScopedPointer<DebugWindow_Ui> ui;

};
