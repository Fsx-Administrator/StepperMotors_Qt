#pragma once

#include "sectionsmap.h"

#include <QSettings>


class IniFileException : public std::runtime_error
{

public:
    IniFileException(const QString &message) : std::runtime_error(message.toStdString()) {};

};


class IniFile
{

public:
    explicit IniFile(const QString &fileName);

    SectionsMap read() const;
    SettingsMap read(const QString &sectionName) const;
    void write(const SectionsMap &sectionsMap) noexcept;
    void write(const QString &sectionName, const SettingsMap &settingsMap) noexcept;

private:
    std::unique_ptr<QSettings> settings_;

};
