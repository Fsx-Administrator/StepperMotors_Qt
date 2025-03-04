#pragma once

#include <QMainWindow>
#include <QPointer>


class MainWindow_Ui;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr) noexcept;
    ~MainWindow() noexcept;

private:
    QScopedPointer<MainWindow_Ui> ui;

};
