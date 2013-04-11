#ifndef ORGMEMBERSHIPREFUSEDEMAILGENERATOR_H
#define ORGMEMBERSHIPREFUSEDEMAILGENERATOR_H

#include "../IEmailGenerator.h"
#include "Common/protobufs/emails/OrgMembershipRefused.pb.h"

class OrgMembershipRefusedEmailGenerator : public IEmailGenerator
{
public:
    OrgMembershipRefusedEmailGenerator();
    void run();

};

#endif // ORGMEMBERSHIPREFUSEDEMAILGENERATOR_H
