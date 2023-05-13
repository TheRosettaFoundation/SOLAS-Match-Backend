#ifndef USERFEEDBACKGENERATOR_H
#define USERFEEDBACKGENERATOR_H

#include "../IEmailGenerator.h"

class UserFeedbackGenerator : public IEmailGenerator
{
public:
    static void run(int claimant_id, int task_id, QString feedback);
};

#endif // USERFEEDBACKGENERATOR_H
