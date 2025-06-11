#include "baudratecombobox.h"

#include "widgetsettings.h"

#include <QSerialPort>


BaudRateComboBox::BaudRateComboBox(QWidget *parent)
    : QComboBox(parent)
    , settings_(std::make_unique<WidgetSettings>(this))
{
    addItem(QString::number(QSerialPort::Baud1200));
    addItem(QString::number(QSerialPort::Baud2400));
    addItem(QString::number(QSerialPort::Baud4800));
    addItem(QString::number(QSerialPort::Baud9600));
    addItem(QString::number(QSerialPort::Baud19200));
    addItem(QString::number(QSerialPort::Baud38400));
    addItem(QString::number(QSerialPort::Baud57600));
    addItem(QString::number(QSerialPort::Baud115200));

    connect(this, &QComboBox::currentTextChanged, [this](const QString &text) -> void {
        emit baudRateChanged(text.toUInt());
    });

    if (settings_ != nullptr)
        setCurrentIndex(settings_->get<int>("index"));
}

BaudRateComboBox::~BaudRateComboBox()
{
    if (settings_ != nullptr)
        settings_->set("index", currentIndex());
}

quint32 BaudRateComboBox::currentBaudRate() const noexcept
{
    return currentText().toInt();
}

void BaudRateComboBox::setCurrentBaudRate(const quint32 baudRate)
{
    setCurrentText(QString::number(baudRate));
}
