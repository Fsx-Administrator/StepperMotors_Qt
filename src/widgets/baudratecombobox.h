#pragma once

#include <QComboBox>


class WidgetSettings;

class BaudRateComboBox : public QComboBox
{
    Q_OBJECT

public:
    explicit BaudRateComboBox(QWidget *parent = nullptr) noexcept;
    ~BaudRateComboBox() noexcept;

    [[nodiscard]] quint32 currentBaudRate() const noexcept;
    void setCurrentBaudRate(const quint32 baudRate) noexcept;

signals:
    void baudRateChanged(const quint32 baudRate);

private:
    std::unique_ptr<WidgetSettings> settings_;

};
