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

QList<QMap<QString, QVariant>> LanguageDao::get_selections(QSharedPointer<MySQLHandler> db)
{
    QList<QMap<QString, QVariant>> selections = QList<QMap<QString, QVariant>>();
    QSharedPointer<QSqlQuery> mQuery = db->call("get_selections", "");
    if (mQuery->first()) {
        QMap<QString, int> fieldMap = MySQLHandler::getFieldMap(mQuery);
        do {
            QMap<QString, QVariant> row = QMap<QString, QVariant>();
            row["language_code"] = MySQLHandler::getValueFromQuery(fieldMap.value("language_code"), mQuery);
            row["country_code"]  = MySQLHandler::getValueFromQuery(fieldMap.value("country_code"), mQuery);
            row["selection"]     = MySQLHandler::getValueFromQuery(fieldMap.value("selection"), mQuery);
            row["memsource"]     = MySQLHandler::getValueFromQuery(fieldMap.value("memsource"), mQuery);
            row["enabled"]       = MySQLHandler::getValueFromQuery(fieldMap.value("enabled"), mQuery);
            selections.append(row);
        } while (mQuery->next());
    }
    return selections;
}
