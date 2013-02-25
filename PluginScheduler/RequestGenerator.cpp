#include "RequestGenerator.h"

#include <QTime>

RequestGenerator::RequestGenerator()
{
}

QSharedPointer<UserTaskScoreRequest> RequestGenerator::GenerateTask(QSharedPointer<UserTaskScoreRequest> task)
{
    task->set_task_id(-1);
    return task;
}

QSharedPointer<DeadlineCheckRequest> RequestGenerator::GenerateTask(QSharedPointer<DeadlineCheckRequest> task)
{
    task->set_task_id(-1);
    return task;
}

QSharedPointer<StatisticsUpdateRequest> RequestGenerator::GenerateTask(QSharedPointer<StatisticsUpdateRequest> task)
{
    task->set_request_time(QTime::currentTime().toString().toStdString());
    return task;
}
