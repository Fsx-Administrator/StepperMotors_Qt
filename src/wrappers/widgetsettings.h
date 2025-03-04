#pragma once

#include "inifile.h"
#include "inifilestorage.h"


class WidgetSettings
{

public:
    explicit WidgetSettings(const QString &name)
    try : _SECTION_NAME_(name)
        , settings_(IniFileStorage::load(_CONFIG_FILE_NAME_, name))
    {}
    catch (const IniFileException &exception)
    {
        qWarning() << exception.what();
    }

    virtual ~WidgetSettings()
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

    template<class T>
    [[nodiscard]] inline T get(const QString &name)
    {
        return settings_.get<T>(name);
    }

    inline void set(const QString &name, const QVariant &value)
    {
        settings_.set(name, value);
    }

private:
    static inline const QString _CONFIG_FILE_NAME_ = "config.ini";

    const QString _SECTION_NAME_;
    SettingsMap settings_;

};
