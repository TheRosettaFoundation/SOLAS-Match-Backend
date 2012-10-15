#ifndef MYSQLHANDLER_H
#define MYSQLHANDLER_H

#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QVariant>
#include <QString>

class MySQLHandler
{
public:
    MySQLHandler(QString name);
    bool init();
    void close();
    QSqlQuery *query(QString query);
    QSqlQuery *call(QString proc_name, QString args);
    static QVariant getValueFromQuery(QString field_name, QSqlQuery *mQuery);

private:
    QSqlDatabase *conn;
    QString connName;
    QString host;
    QString database;
    QString user;
    QString pass;
    bool openConnection();

};

#endif // MYSQLHANDLER_H
