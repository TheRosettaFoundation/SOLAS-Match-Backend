#ifndef USERFEEDBACKGENERATOR_H
#define USERFEEDBACKGENERATOR_H

#include "../IEmailGenerator.h"

class UserFeedbackGenerator : public IEmailGenerator
{
public:
    UserFeedbackGenerator();
    void run();

};

#endif // USERFEEDBACKGENERATOR_H
