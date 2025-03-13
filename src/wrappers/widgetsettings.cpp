#include "widgetsettings.h"

#include "inifile.h"
#include "inifilestorage.h"

#include <QWidget>


WidgetSettings::WidgetSettings(QWidget *parent)
try : _SECTION_NAME_(parent->metaObject()->className())
    , settings_(IniFileStorage::load(_CONFIG_FILE_NAME_, _SECTION_NAME_))
{}
catch (const IniFileException &exception)
{
    qWarning() << exception.what();
}

WidgetSettings::~WidgetSettings()
{
    try
    {
        IniFileStorage::save(_CONFIG_FILE_NAME_, _SECTION_NAME_, settings_);
    }
    catch (const IniFileException &exception)
    {
        qWarning() << exception.what();
    }
}

void WidgetSettings::set(const QString &name, const QVariant &value)
{
    settings_.set(name, value);
}
