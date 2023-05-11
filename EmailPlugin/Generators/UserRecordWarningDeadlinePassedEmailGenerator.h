#ifndef USERRECORDWARNINGDEADLINEPASSEDEMAILGENERATOR_H
#define USERRECORDWARNINGDEADLINEPASSEDEMAILGENERATOR_H

#include "../IEmailGenerator.h"

class UserRecordWarningDeadlinePassedEmailGenerator : IEmailGenerator
{
public:
    static void run(int user_id);
};

#endif // USERRECORDWARNINGDEADLINEPASSEDEMAILGENERATOR_H
