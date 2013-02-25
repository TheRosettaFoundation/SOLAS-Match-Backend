#ifndef REQUESTGENERATOR_H
#define REQUESTGENERATOR_H

#include "Common/protobufs/requests/UserTaskScoreRequest.pb.h"
#include "Common/protobufs/requests/DeadlineCheckRequest.pb.h"
#include "Common/protobufs/requests/StatisticsUpdateRequest.pb.h"

#include <QSharedPointer>

class RequestGenerator
{
public:
    RequestGenerator();
    QSharedPointer<UserTaskScoreRequest> GenerateTask(QSharedPointer<UserTaskScoreRequest>);
    QSharedPointer<DeadlineCheckRequest> GenerateTask(QSharedPointer<DeadlineCheckRequest>);
    QSharedPointer<StatisticsUpdateRequest> GenerateTask(QSharedPointer<StatisticsUpdateRequest>);

};

#endif // REQUESTGENERATOR_H
