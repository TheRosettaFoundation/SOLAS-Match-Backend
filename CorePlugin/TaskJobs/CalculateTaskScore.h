#ifndef CALCULATETASKSCOREJOB_H
#define CALCULATETASKSCOREJOB_H

#include <QObject>
#include <AMQPcpp.h>
#include <QList>
#include <QSharedPointer>

#include "PluginHandler/JobInterface.h"
#include "Common/protobufs/models/Task.pb.h"
#include "Common/MySQLHandler.h"

class CalculateTaskScore : public JobInterface
{
    Q_INTERFACES(JobInterface)

public:
    CalculateTaskScore();
    CalculateTaskScore(AMQPMessage *);
    ~CalculateTaskScore();
    void run();
    void setAMQPMessage(AMQPMessage *message);

private:
    QList<QSharedPointer<Task> > getTasks();
    int getTaskIdFromMessage();
    int getCurrentScore(int user_id, int task_id);
    void saveUserTaskScore(int user_id, int task_id, int score);
    AMQPMessage *message;
    QSharedPointer<MySQLHandler> db;

};

#endif // CALCULATETASKSCOREJOB_H
