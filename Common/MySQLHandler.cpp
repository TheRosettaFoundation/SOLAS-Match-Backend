#include "MySQLHandler.h"

#include <QDebug>
#include <QUuid>
#include <QMutex>
#include <QMutexLocker>
#include <QtSql/QSqlDriver>
#include <QtSql/QSqlError>
#include <QtSql/QSqlRecord>
#include <QThread>

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
    //qDebug() << "Deleting MySQLHandler " << this->connName;
    this->close();
    delete this->conn;
}

QSharedPointer<MySQLHandler> MySQLHandler::getInstance()
{
    static QMutex mutex;
    QMutexLocker locker(&mutex);
    return QSharedPointer<MySQLHandler>(new MySQLHandler(QUuid::createUuid().toString()));
}

bool MySQLHandler::init()
{
    bool ret = this->openConnection();
    return ret;
}

bool MySQLHandler::openConnection()
{
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
            qDebug() << "MySQLHandler: Failed to connect to database on 1st attempt: " << this->conn->lastError().text();

            // https://github.com/TheRosettaFoundation/SOLAS-Match-Backend/issues/44
            // Give it one more chance...
            this->close();         // Should probably not be issued, but mimics existing code path after a failure
            delete this->conn;     // Try a complete restart of connection for safety
            this->conn = 0;        // For extra extra safety only

            QThread::msleep(3000); // Give socket/MySQL server some time to stabilise

            this->conn = new QSqlDatabase(QSqlDatabase::addDatabase("QMYSQL", this->connName));
            this->conn->setHostName(this->host);
            this->conn->setDatabaseName(this->database);
            this->conn->setUserName(this->user);
            this->conn->setPassword(this->pass);

            if (!this->conn->open()) {
                qDebug() << "MySQLHandler: Failed to connect to database on 2nd attempt: " << this->conn->lastError().text();
            } else {
                //qDebug() << this->connName << " MySQL connection established";
                ret = true;
            }
        } else {
            //qDebug() << this->connName << " MySQL connection established";
            ret = true;
        }
    } else {
        ret = true;
    }

    return ret;
}

void MySQLHandler::close()
{
    this->conn->close();
}

QSharedPointer<QSqlQuery> MySQLHandler::query(QString query)
{
    QSharedPointer<QSqlQuery> mQuery = QSharedPointer<QSqlQuery>(new QSqlQuery(query, *(this->conn)));

    return mQuery;
}

QSharedPointer<QSqlQuery> MySQLHandler::call(QString proc_name, QString args)
{
    QSharedPointer<QSqlQuery> ret = QSharedPointer<QSqlQuery>(new QSqlQuery());
    if (this->init()) {
        QString query = "Call " + proc_name + " (" + args + ")";
        ret = QSharedPointer<QSqlQuery>(new QSqlQuery(query, *(this->conn)));
        if (ret->lastError().isValid()) {
            qDebug() << "MySQLHandler: ERROR - call " << proc_name << "()-" << ret->lastError().text();
        }
    } else {
        qDebug() << "MySQLHandler::call - Initialization failed";
    }

    return ret;
}

QList<QSharedPointer <QSqlQuery> > MySQLHandler::multicall(QString proc_name, QList<QString> arglist)
{
    QList<QSharedPointer <QSqlQuery> > ret = QList<QSharedPointer <QSqlQuery> >();
    QSharedPointer<QSqlQuery> q = QSharedPointer<QSqlQuery>(new QSqlQuery(*(this->conn)));

    foreach (QString str,arglist) {
        ret.append(this->call(proc_name,str));
    }


//    if (this->init()) {
//        QString query = "Call " + proc_name+" (";
//        QStringList item =arglist.first().split(",");
//        for(int i = 0; i<item.size(); i++){
//            if(i!=0) query +=",";
//            query +="?";
//        }
//        query += ")";
//        q->prepare(query);
//        foreach (QString args, arglist) {
//            item =args.split(",");
//            for(int i = 0; i<item.size(); i++){
//               q->addBindValue(item.at(i));
//            }

//           QSharedPointer<QSqlQuery> result = QSharedPointer<QSqlQuery>(new QSqlQuery(query, *(this->conn)));

//           if (result->lastError().isValid()) {
//               qDebug() << "MySQLHandler: ERROR - " << result->lastError().text();
//           } else ret.append(result);
//        }


//    } else {
//        qDebug() << "MySQLHandler::call - Initialization failed";
//    }

    return ret;
}

QVariant MySQLHandler::getValueFromQuery(QString field_name, QSharedPointer<QSqlQuery> mQuery)
{
    QVariant ret = 0;
    int field_pos = mQuery->record().indexOf(field_name);
    if (field_pos != -1) {
        ret = mQuery->value(field_pos);
    }

    return ret;
}

QVariant MySQLHandler::getValueFromQuery(int field_pos, QSharedPointer<QSqlQuery> mQuery)
{
    QVariant ret = 0;
    if (field_pos >= 0 && field_pos < mQuery->record().count()) {
        ret = mQuery->value(field_pos);
    }

    return ret;
}

std::string MySQLHandler::getStringFromQuery(int field_pos, QSharedPointer<QSqlQuery> mQuery)
{
    QByteArray bytes = QByteArray(MySQLHandler::getValueFromQuery(field_pos, mQuery).toString().toUtf8());
    std::string ret(bytes.constData(), bytes.length());
    return ret;
}

QMap<QString, int> MySQLHandler::getFieldMap(QSharedPointer<QSqlQuery> q)
{
    QMap<QString, int> fieldMap;
    QSqlRecord rec = q->record();
    for (int i = 0; i < rec.count(); i++) {
        fieldMap.insert(rec.fieldName(i), i);
    }
    return fieldMap;
}

QString MySQLHandler::wrapString(QString str)
{
    str.replace("\\", "\\\\");
    str.replace("'", "\\'");

    return "'" + str + "'";
}

QString MySQLHandler::wrapStdString(const std::string str)
{
    return MySQLHandler::wrapString(QString::fromUtf8(str.c_str(), str.length()));
}
