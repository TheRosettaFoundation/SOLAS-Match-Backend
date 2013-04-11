#ifndef ORGMEMBERSHIPACCEPTEDGENERATOR_H
#define ORGMEMBERSHIPACCEPTEDGENERATOR_H

#include "../IEmailGenerator.h"
#include "Common/protobufs/emails/OrgMembershipAccepted.pb.h"

class OrgMembershipAcceptedGenerator : public IEmailGenerator
{
public:
    OrgMembershipAcceptedGenerator();
    void run();

};

#endif // ORGMEMBERSHIPACCEPTEDGENERATOR_H
