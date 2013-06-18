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
    QSharedPointer<QSqlQuery> call(QString proc_name, QString args);
    QList<QSharedPointer <QSqlQuery> > multicall(QString proc_name, QList<QString> arglist);
    static QVariant getValueFromQuery(QString field_name, QSharedPointer<QSqlQuery> mQuery);
    static QVariant getValueFromQuery(int field_pos, QSharedPointer<QSqlQuery> mQuery);
    static QMap<QString, int> getFieldMap(QSharedPointer<QSqlQuery> q);
    static QString wrapString(QString str);
    static QString wrapStdString(const std::string str);

private:
    MySQLHandler(QString name);
    static QList<QSharedPointer<MySQLHandler> > connectionPool;
    QSqlDatabase *conn;
    QString connName;
    QString host;
    QString database;
    QString user;
    QString pass;
    QSharedPointer<QSqlQuery> query(QString query);
    void close();
    bool init();
    bool openConnection();

};

#endif // MYSQLHANDLER_H
