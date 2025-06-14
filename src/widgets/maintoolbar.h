#pragma once

#include <QToolBar>


class BaudRateComboBox;
class PortNameComboBox;
class ToggledPushButton;

class MainToolBar : public QToolBar
{
    Q_OBJECT

public:
    explicit MainToolBar(QWidget *parent = nullptr);
    ~MainToolBar() = default;

private:
    BaudRateComboBox *baudRateComboBox_;
    PortNameComboBox *portNameComboBox_;
    ToggledPushButton *connectToggledPushButton_;

};
