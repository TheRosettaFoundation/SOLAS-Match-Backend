#include "StatisticsUpdate.h"

#include <QThread>
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
    qDebug() << "Starting new Thread for statistics update";
    QSharedPointer<MySQLHandler> db = MySQLHandler::getInstance();
    db->call("statsUpdateAll", "");
    qDebug() << "Finished Statistics Update";
}

void StatisticsUpdate::setAMQPMessage(AMQPMessage *message)
{
    this->message = message;
}
