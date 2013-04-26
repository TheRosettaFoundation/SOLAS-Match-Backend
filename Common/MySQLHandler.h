#ifndef MYSQLHANDLER_H
#define MYSQLHANDLER_H

#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QSharedPointer>
#include <QMutex>
#include <QVariant>
#include <QString>
#include <string>

class MySQLHandler
{
public:
    ~MySQLHandler();
    static QSharedPointer<MySQLHandler> getInstance();
    bool init();
    void close();
    QSharedPointer<QSqlQuery> query(QString query);
    QSharedPointer<QSqlQuery> call(QString proc_name, QString args);
    static QVariant getValueFromQuery(QString field_name, QSharedPointer<QSqlQuery> mQuery);
    static QString wrapString(QString str);
    static QString wrapStdString(const std::string str);

private:
    MySQLHandler(QString name);
    QSqlDatabase *conn;
    QString connName;
    QString host;
    QString database;
    QString user;
    QString pass;
    bool openConnection();

};

#endif // MYSQLHANDLER_H
