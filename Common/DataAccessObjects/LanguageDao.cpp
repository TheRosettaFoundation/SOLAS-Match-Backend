#include "LanguageDao.h"

#include "Common/ModelGenerator.h"

QList<QSharedPointer<Language> > LanguageDao::getLanguages(MySQLHandler *db)
{
    QList<QSharedPointer<Language> > languages;
    QString args = "null, null, null";
    QSharedPointer<QSqlQuery> mQuery = db->call("getLanguage", args);
    if (mQuery->first()) {
        do {
            QSharedPointer<Language> lang = ModelGenerator::GenerateLanguage(mQuery);
            languages.append(lang);
        } while (mQuery->next());
    }
    return languages;
}

QSharedPointer<Language> LanguageDao::getLanguage(MySQLHandler *db, int id, QString code)
{
    QSharedPointer<Language> language;
    if (id != -1 || code != "") {
        QString args = "";
        if (id != -1) {
            args += QString::number(id) + ", ";
        } else {
            args += "null, ";
        }

        if (code != "") {
            args += "'" + code + "', ";
        } else {
            args +=  "null, ";
        }
        args += "null";

        QSharedPointer<QSqlQuery> mQuery = db->call("getLanguage", args);
        if (mQuery->first()) {
            language = ModelGenerator::GenerateLanguage(mQuery);
        }
    }
    return language;
}
