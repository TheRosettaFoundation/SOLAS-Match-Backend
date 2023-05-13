#ifndef ORGMEMBERSHIPACCEPTEDGENERATOR_H
#define ORGMEMBERSHIPACCEPTEDGENERATOR_H

#include "../IEmailGenerator.h"

class OrgMembershipAcceptedGenerator : public IEmailGenerator
{
public:
    static void run(int user_id, int org_id);
};

#endif // ORGMEMBERSHIPACCEPTEDGENERATOR_H
