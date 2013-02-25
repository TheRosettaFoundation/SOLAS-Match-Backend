#include "StatisticsUpdate.h"

#include <QThread>
#include <QUuid>
#include <QDebug>

StatisticsUpdate::StatisticsUpdate()
{
    //Default Constructor
}

StatisticsUpdate::StatisticsUpdate(AMQPMessage *mess)
{
    this->message = mess;
}

StatisticsUpdate::~StatisticsUpdate()
{
    //Default destructor
}

void StatisticsUpdate::run()
{
    qDebug() << "Starting new Thread for statistics update " << this->thread()->currentThreadId();
    MySQLHandler *db = new MySQLHandler(QUuid::createUuid().toString());
    if (db->init()) {
        db->call("statsUpdateAll", "");
    } else {
        qDebug() << "Unable to connect to DB";
    }

    if (message->getQueue()) {
        message->getQueue()->Ack(message->getDeliveryTag());
    }

    delete db;
}
