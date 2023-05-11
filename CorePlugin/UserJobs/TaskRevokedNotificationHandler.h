#ifndef TASKREVOKEDNOTIFICATIONHANDLER_H
#define TASKREVOKEDNOTIFICATIONHANDLER_H

#include <QObject>
#include <AMQPcpp.h>

#include "PluginHandler/JobInterface.h"

class TaskRevokedNotificationHandler : public JobInterface
{
    Q_INTERFACES(JobInterface)

public:
    static void run(int task_id, int claimant_id);

private:
};

#endif // TASKREVOKEDNOTIFICATIONHANDLER_H
