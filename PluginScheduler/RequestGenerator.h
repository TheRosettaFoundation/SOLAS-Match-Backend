#ifndef REQUESTGENERATOR_H
#define REQUESTGENERATOR_H

#include "Common/protobufs/requests/UserTaskScoreRequest.pb.h"
#include "Common/protobufs/requests/DeadlineCheckRequest.pb.h"
#include "Common/protobufs/requests/StatisticsUpdateRequest.pb.h"
#include "Common/protobufs/requests/UserTaskStreamNotificationRequest.pb.h"

#include <QSharedPointer>
using namespace SolasMatch::Common::Protobufs::Requests;

class RequestGenerator
{
public:
    RequestGenerator();
    QSharedPointer<UserTaskScoreRequest> GenerateTask(QSharedPointer<UserTaskScoreRequest>);
    QSharedPointer<DeadlineCheckRequest> GenerateTask(QSharedPointer<DeadlineCheckRequest>);
    QSharedPointer<StatisticsUpdateRequest> GenerateTask(QSharedPointer<StatisticsUpdateRequest>);
    QSharedPointer<UserTaskStreamNotificationRequest> GenerateTask(QSharedPointer<UserTaskStreamNotificationRequest>);

};

#endif // REQUESTGENERATOR_H
