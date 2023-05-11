#ifndef ORGTASKREVOKEDGENERATOR_H
#define ORGTASKREVOKEDGENERATOR_H

#include "../IEmailGenerator.h"

class OrgTaskRevokedGenerator : public IEmailGenerator
{
public:
    static void run(int task_id, int user_id, int claimant_id);
};

#endif // ORGTASKREVOKEDGENERATOR_H
