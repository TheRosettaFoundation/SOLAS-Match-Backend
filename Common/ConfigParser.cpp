#include "ConfigParser.h"

#include <QStringList>
#include <QDebug>
#include <QDir>

ConfigParser::ConfigParser()
{
    qDebug() << "ConfigParser::Reading configuration from " << INI_FILE_LOCATION;
    mSettings = new QSettings(INI_FILE_LOCATION, QSettings::IniFormat);
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
