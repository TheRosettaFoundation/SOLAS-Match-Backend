#ifndef USERTASKCANCELLEDEMAILGENERATOR_H
#define USERTASKCANCELLEDEMAILGENERATOR_H

#include "../IEmailGenerator.h"
#include "Common/protobufs/emails/UserTaskCancelled.pb.h"

class UserTaskCancelledEmailGenerator : public IEmailGenerator
{
public:
    UserTaskCancelledEmailGenerator();
    void run();

};

#endif // USERTASKCANCELLEDEMAILGENERATOR_H
