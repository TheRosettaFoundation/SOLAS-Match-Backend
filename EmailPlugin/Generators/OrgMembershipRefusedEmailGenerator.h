#ifndef ORGMEMBERSHIPREFUSEDEMAILGENERATOR_H
#define ORGMEMBERSHIPREFUSEDEMAILGENERATOR_H

#include "../IEmailGenerator.h"

class OrgMembershipRefusedEmailGenerator : public IEmailGenerator
{
public:
    static void run(int user_id, int org_id);
};

#endif // ORGMEMBERSHIPREFUSEDEMAILGENERATOR_H
