#ifndef ORGMEMBERSHIPACCEPTEDGENERATOR_H
#define ORGMEMBERSHIPACCEPTEDGENERATOR_H

#include "../IEmailGenerator.h"

class OrgMembershipAcceptedGenerator : public IEmailGenerator
{
public:
    OrgMembershipAcceptedGenerator();
    void run();

};

#endif // ORGMEMBERSHIPACCEPTEDGENERATOR_H
