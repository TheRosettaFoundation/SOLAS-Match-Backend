#include "LanguageDao.h"

#include "Common/ModelGenerator.h"

QList<QSharedPointer<Language> > LanguageDao::getLanguages(QSharedPointer<MySQLHandler> db)
{
    QList<QSharedPointer<Language> > languages;
    QString args = "null, null, null";
    QSharedPointer<QSqlQuery> mQuery = db->call("getLanguage", args);
    if (mQuery->first()) {
        QMap<QString, int> fieldMap = MySQLHandler::getFieldMap(mQuery);
        do {
            QSharedPointer<Language> lang = QSharedPointer<Language>(new Language());
            ModelGenerator::Generate(mQuery, lang, fieldMap);
            languages.append(lang);
        } while (mQuery->next());
    }
    return languages;
}

QSharedPointer<Language> LanguageDao::getLanguage(QSharedPointer<MySQLHandler> db, int id, QString code)
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
            args += MySQLHandler::wrapString(code) + ", ";
        } else {
            args +=  "null, ";
        }
        args += "null";

        QSharedPointer<QSqlQuery> mQuery = db->call("getLanguage", args);
        if (mQuery->first()) {
            QMap<QString, int> fieldMap = MySQLHandler::getFieldMap(mQuery);
            language = QSharedPointer<Language>(new Language());
            ModelGenerator::Generate(mQuery, language, fieldMap);
        }
    }
    return language;
}
