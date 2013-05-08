#include "RequestGenerator.h"

#include <QDebug>
#include <QTime>

RequestGenerator::RequestGenerator()
{
}

QSharedPointer<UserTaskScoreRequest> RequestGenerator::GenerateTask(QSharedPointer<UserTaskScoreRequest> task)
{
    task->set_name(task->name());
    task->set_task_id(-1);
    return task;
}

QSharedPointer<DeadlineCheckRequest> RequestGenerator::GenerateTask(QSharedPointer<DeadlineCheckRequest> task)
{
    task->set_name(task->name());
    task->set_task_id(-1);
    return task;
}

QSharedPointer<StatisticsUpdateRequest> RequestGenerator::GenerateTask(QSharedPointer<StatisticsUpdateRequest> task)
{
    task->set_name(task->name());   // This fixes a proto issue with serialization
    return task;
}

QSharedPointer<UserTaskStreamNotificationRequest> RequestGenerator::GenerateTask(
        QSharedPointer<UserTaskStreamNotificationRequest> task)
{
    task->set_name(task->name());   // This fixes a proto issue with serialization
    return task;
}
