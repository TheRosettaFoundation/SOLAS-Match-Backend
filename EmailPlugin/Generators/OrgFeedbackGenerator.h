#ifndef ORGFEEDBACKGENERATOR_H
#define ORGFEEDBACKGENERATOR_H

#include "../IEmailGenerator.h"

class OrgFeedbackGenerator
{
public:
    static void run(int claimant_id, int task_id, int user_id, QString feedback);
};

#endif // ORGFEEDBACKGENERATOR_H
