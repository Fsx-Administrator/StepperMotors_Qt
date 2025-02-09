#pragma once

#include <QComboBox>


class BaudRateComboBox : public QComboBox
{
    Q_OBJECT

public:
    explicit BaudRateComboBox(QWidget *parent = nullptr) noexcept;
    ~BaudRateComboBox() noexcept = default;

    [[nodiscard]] quint32 currentBaudRate() const noexcept;
    void setCurrentBaudRate(const quint32 baudRate) noexcept;

signals:
    void baudRateChanged(const quint32 baudRate);

};
