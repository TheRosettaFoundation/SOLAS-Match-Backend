#ifndef USERTASKCLAIMEMAILGENERATOR_H
#define USERTASKCLAIMEMAILGENERATOR_H

#include "../IEmailGenerator.h"
#include "Common/protobufs/emails/UserTaskClaim.pb.h"

class UserTaskClaimEmailGenerator : public IEmailGenerator
{
public:
    UserTaskClaimEmailGenerator();
    void run();

};

#endif // USERTASKCLAIMEMAILGENERATOR_H
