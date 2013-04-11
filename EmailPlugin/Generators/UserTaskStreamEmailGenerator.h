#ifndef USERTASKSTREAMEMAILGENERATOR_H
#define USERTASKSTREAMEMAILGENERATOR_H

#include "../IEmailGenerator.h"
#include "Common/protobufs/emails/UserTaskStreamEmail.pb.h"

class UserTaskStreamEmailGenerator : public IEmailGenerator
{
    UserTaskStreamEmailGenerator();
    void run();

};

#endif // USERTASKSTREAMEMAILGENERATOR_H
