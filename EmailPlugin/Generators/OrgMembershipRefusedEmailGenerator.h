#ifndef ORGMEMBERSHIPREFUSEDEMAILGENERATOR_H
#define ORGMEMBERSHIPREFUSEDEMAILGENERATOR_H

#include "../IEmailGenerator.h"

class OrgMembershipRefusedEmailGenerator : public IEmailGenerator
{
public:
    OrgMembershipRefusedEmailGenerator();
    void run();

};

#endif // ORGMEMBERSHIPREFUSEDEMAILGENERATOR_H
