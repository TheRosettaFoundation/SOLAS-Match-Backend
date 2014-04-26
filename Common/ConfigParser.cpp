#include "ConfigParser.h"

#include <QStringList>
#include <QDir>

#include <QDebug>

ConfigParser::ConfigParser()
{
    if (QFile::exists(INI_FILE_LOCATION))
    {
        mSettings = new QSettings(INI_FILE_LOCATION, QSettings::IniFormat);
    }
}

ConfigParser::~ConfigParser()
{
    delete mSettings;
}

QString ConfigParser::get(QString key)
{
    QString ret = "";
    QStringList keys = key.split(".");
    mSettings->beginGroup(keys[0]);
    ret = mSettings->value(keys[1]).toString();
    mSettings->endGroup();
    return ret;
}
