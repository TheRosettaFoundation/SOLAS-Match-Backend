#ifndef USERTASKREVOKEDGENERATOR_H
#define USERTASKREVOKEDGENERATOR_H

#include "../IEmailGenerator.h"
#include "Common/protobufs/emails/UserTaskRevokedEmail.pb.h"

class UserTaskRevokedGenerator : public IEmailGenerator
{
public:
    UserTaskRevokedGenerator();
    void run();

};

#endif // USERTASKREVOKEDGENERATOR_H
