#pragma once

#include <QMainWindow>
#include <QPointer>


class MainWindow_Ui;

class MainWindow final : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    QScopedPointer<MainWindow_Ui> ui;

};
