#include "inifile.h"


IniFile::IniFile(const QString &fileName)
    : settings_(std::make_unique<QSettings>(fileName, QSettings::IniFormat))
{}

SectionsMap IniFile::read() const
{
    try
    {
        SectionsMap sectionsMap;

        for (const auto &group : settings_->childGroups())
            sectionsMap[group] = read(group);

        return sectionsMap;
    }
    catch (const IniFileException &exception)
    {
        std::throw_with_nested(IniFileException(settings_->fileName() + " :: Ini file cannot be read"));
    }
}

SettingsMap IniFile::read(const QString &sectionName) const
{
    SettingsMap settingsMap;

    settings_->beginGroup(sectionName);
    if (settings_->childKeys().empty())
        throw IniFileException(settings_->fileName() + " :: There is not section " + sectionName);

    for (const auto &key : settings_->childKeys())
        settingsMap[key] = settings_->value(key, QVariant(0));
    settings_->endGroup();

    return settingsMap;
}

void IniFile::write(const SectionsMap &sectionsMap)
{
    for (const auto &section : sectionsMap)
        write(sectionsMap.key(section), section);
}

void IniFile::write(const QString &sectionName, const SettingsMap &settingsMap)
{
    settings_->beginGroup(sectionName);

    const auto keys = settingsMap.keys();
    for (const auto &key : keys)
        settings_->setValue(key, settingsMap[key]);

    settings_->endGroup();
}
