#ifndef REQUESTGENERATOR_H
#define REQUESTGENERATOR_H

#include "Common/protobufs/requests/UserTaskScoreRequest.pb.h"

#include <QSharedPointer>

class RequestGenerator
{
public:
    RequestGenerator();
    QSharedPointer<UserTaskScoreRequest> GenerateTask(QSharedPointer<UserTaskScoreRequest>);

};

#endif // REQUESTGENERATOR_H
