#pragma once

#include <QMainWindow>


class MainWindow_Ui;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() = default;

private:
    MainWindow_Ui *ui;

};
