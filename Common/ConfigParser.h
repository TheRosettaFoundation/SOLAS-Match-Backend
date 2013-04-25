#ifndef CONFIGPARSER_H
#define CONFIGPARSER_H

#define INI_FILE_LOCATION "./conf.ini"

#include <QString>
#include <QSettings>

class ConfigParser
{
public:
    ConfigParser();
    ~ConfigParser();
    QString get(QString key);

private:
    QSettings *mSettings;

};

#endif // CONFIGPARSER_H
