#ifndef USERREFERENCEEMAILGENERATOR_H
#define USERREFERENCEEMAILGENERATOR_H

#include "../IEmailGenerator.h"
#include "Common/protobufs/emails/UserTaskClaim.pb.h"

class UserReferenceEmailGenerator : public IEmailGenerator
{
public:
    UserReferenceEmailGenerator();
    void run();

};

#endif // USERREFERENCEEMAILGENERATOR_H
