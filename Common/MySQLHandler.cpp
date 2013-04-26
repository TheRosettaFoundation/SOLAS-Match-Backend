#include "MySQLHandler.h"

#include <QDebug>
#include <QUuid>
#include <QMutex>
#include <QMutexLocker>
#include <QtSql/QSqlDriver>
#include <QtSql/QSqlError>
#include <QtSql/QSqlRecord>

#include "ConfigParser.h"

MySQLHandler::MySQLHandler(QString name)
{
    ConfigParser settings;
    this->conn = 0;
    this->host = settings.get("database.server");
    this->database = settings.get("database.database");
    this->user = settings.get("database.username");
    this->pass = settings.get("database.password");
    this->connName = name;
}

MySQLHandler::~MySQLHandler()
{
    qDebug() << "Deleting MySQLHandler " << this->connName;
}

QSharedPointer<MySQLHandler> MySQLHandler::getInstance()
{
    qDebug() << "MySQLHandler::getInstance";
    static QMutex mutex;
    QMutexLocker locker(&mutex);
    return QSharedPointer<MySQLHandler>(new MySQLHandler(QUuid::createUuid().toString()));
}

bool MySQLHandler::init()
{
    bool ret = this->openConnection();
    this->database = "";
    this->user = "";
    this->pass = "";
    return ret;
}

bool MySQLHandler::openConnection()
{
    qDebug() << "MySQLHandler::Opening MySQL Connection";
    bool ret = false;

    if (this->conn == 0) {
        this->conn = new QSqlDatabase(QSqlDatabase::addDatabase("QMYSQL", this->connName));
        this->conn->setHostName(this->host);
        this->conn->setDatabaseName(this->database);
        this->conn->setUserName(this->user);
        this->conn->setPassword(this->pass);
    }

    if (!this->conn->isOpen()) {
        if (!this->conn->open()) {
            qDebug() << "Failed to connect to database: " << this->conn->lastError().text();
        } else {
            qDebug() << this->connName << " MySQL connection established";
            ret = true;
        }
    } else {
        ret = true;
        qDebug() << this->connName << " connection already established";
    }

    return ret;
}

void MySQLHandler::close()
{
    qDebug() << "Closing SQL Connection";
    this->conn->close();
}

QSharedPointer<QSqlQuery> MySQLHandler::query(QString query)
{
    QSharedPointer<QSqlQuery> mQuery = QSharedPointer<QSqlQuery>(new QSqlQuery(query, *(this->conn)));

    return mQuery;
}

QSharedPointer<QSqlQuery> MySQLHandler::call(QString proc_name, QString args)
{
    QString query = "Call " + proc_name + " (" + args + ")";
    QSharedPointer<QSqlQuery> q = QSharedPointer<QSqlQuery>(new QSqlQuery(query, *(this->conn)));
    if (q->lastError().isValid()) {
        qDebug() << "MySQLHandler: ERROR - " << q->lastError().text();
    }

    return q;
}

QVariant MySQLHandler::getValueFromQuery(QString field_name, QSharedPointer<QSqlQuery> mQuery)
{
    QVariant ret = 0;
    int field_pos = mQuery->record().indexOf(field_name);
    if(field_pos != -1) {
        ret = mQuery->value(field_pos);
    }

    return ret;
}

QString MySQLHandler::wrapString(QString str)
{
    return "'" + str + "'";
}

QString MySQLHandler::wrapStdString(const std::string str)
{
    return MySQLHandler::wrapString(QString::fromStdString(str));
}
