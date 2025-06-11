#pragma once

#include <QComboBox>


class PortNameComboBox : public QComboBox
{
    Q_OBJECT

public:
    explicit PortNameComboBox(QWidget *parent = nullptr);
    ~PortNameComboBox();

    [[nodiscard]] QString currentPortName() const noexcept;

protected:
    void timerEvent(QTimerEvent *event) override;

private slots:
    void refresh();

private:
    const int _REFRESH_TIMEOUT_;

    int refreshTimerId_;

};
