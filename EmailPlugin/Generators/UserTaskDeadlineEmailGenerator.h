#ifndef USERTASKDEADLINEEMAILGENERATOR_H
#define USERTASKDEADLINEEMAILGENERATOR_H

#include "../IEmailGenerator.h"
#include "Common/protobufs/emails/UserClaimedTaskDeadlinePassed.pb.h"

class UserTaskDeadlineEmailGenerator : IEmailGenerator
{
public:
    UserTaskDeadlineEmailGenerator();
    void run();

};

#endif // USERTASKDEADLINEEMAILGENERATOR_H
