#ifndef USERTASKDEADLINEEMAILGENERATOR_H
#define USERTASKDEADLINEEMAILGENERATOR_H

#include "../IEmailGenerator.h"

class UserTaskDeadlineEmailGenerator : IEmailGenerator
{
public:
    UserTaskDeadlineEmailGenerator();
    void run();

};

#endif // USERTASKDEADLINEEMAILGENERATOR_H
