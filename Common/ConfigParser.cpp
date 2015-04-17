#include "ConfigParser.h"

#include <QStringList>
#include <QDir>

ConfigParser::ConfigParser()
{
    static QSettings singleton(INI_FILE_LOCATION, QSettings::IniFormat);
    mSettings = &singleton;
}

ConfigParser::~ConfigParser()
{
    //delete mSettings;
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
