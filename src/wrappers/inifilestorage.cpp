#include "inifilestorage.h"

#include "inifile.h"


SectionsMap IniFileStorage::load(const QString &fileName)
{
    try
    {
        IniFile iniFile(fileName);
        return iniFile.read();
    }
    catch (const IniFileException &exception)
    {
        throw exception;
    }
}

SettingsMap IniFileStorage::load(const QString &fileName, const QString &sectionName)
{
    try
    {
        IniFile iniFile(fileName);
        return iniFile.read(sectionName);
    }
    catch (const IniFileException &exception)
    {
        throw exception;
    }
}

void IniFileStorage::save(const QString &fileName, const SectionsMap &sections)
{
    try
    {
        IniFile iniFile(fileName);
        iniFile.write(sections);
    }
    catch (const IniFileException &exception)
    {
        throw exception;
    }
}

void IniFileStorage::save(
    const QString &fileName,
    const QString &sectionName,
    const SettingsMap &settings
    )
{
    try
    {
        IniFile iniFile(fileName);
        iniFile.write(sectionName, settings);
    }
    catch (const IniFileException &exception)
    {
        throw exception;
    }
}
