#pragma once


class BaudRateComboBox;
class MainWindow;
class PortNameComboBox;
class ToggledPushButton;

class MainWindow_Ui
{
public:
    explicit MainWindow_Ui(MainWindow *parent) noexcept;
    ~MainWindow_Ui() noexcept = default;

private:
    BaudRateComboBox *baudRateComboBox_;
    PortNameComboBox *portNameComboBox_;
    ToggledPushButton *connect_ToggledPushButton_;

};
