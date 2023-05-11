#ifndef TASKREVOKEDNOTIFICATIONHANDLER_H
#define TASKREVOKEDNOTIFICATIONHANDLER_H

#include <QObject>

#include "PluginHandler/JobInterface.h"

class TaskRevokedNotificationHandler
{
public:
    static void run(int task_id, int claimant_id);

private:
};

#endif // TASKREVOKEDNOTIFICATIONHANDLER_H
