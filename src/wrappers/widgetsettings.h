#pragma once

#include "sectionsmap.h"


class QWidget;

class WidgetSettings
{

public:
    explicit WidgetSettings(QWidget *parent);
    virtual ~WidgetSettings();

    template<class T>
    [[nodiscard]] inline T get(const QString &name) { return settings_.get<T>(name); }
    void set(const QString &name, const QVariant &value);

private:
    static inline const QString _CONFIG_FILE_NAME_ = "config.ini";

    const QString _SECTION_NAME_;
    SettingsMap settings_;

};
