#pragma once

#include "sectionsmap.h"


class IniFileStorage
{

public:
    IniFileStorage() = delete;
    IniFileStorage(const IniFileStorage &) = delete;
    IniFileStorage(IniFileStorage &&) = delete;
    ~IniFileStorage() = delete;

    IniFileStorage& operator=(const IniFileStorage &) = delete;
    IniFileStorage& operator=(IniFileStorage &&) = delete;

    static void save(const QString &fileName, const SectionsMap &sections);
    static void save(const QString &fileName, const QString &sectionName, const SettingsMap &settings);
    [[nodiscard]] static SectionsMap load(const QString &fileName);
    [[nodiscard]] static SettingsMap load(const QString &fileName, const QString &sectionName);

};
