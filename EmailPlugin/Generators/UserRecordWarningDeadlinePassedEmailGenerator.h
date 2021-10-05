#ifndef USERRECORDWARNINGDEADLINEPASSEDEMAILGENERATOR_H
#define USERRECORDWARNINGDEADLINEPASSEDEMAILGENERATOR_H

#include "../IEmailGenerator.h"
#include "Common/protobufs/emails/UserRecordWarningDeadlinePassed.pb.h"

class UserRecordWarningDeadlinePassedEmailGenerator : IEmailGenerator
{
public:
    UserRecordWarningDeadlinePassedEmailGenerator();
    void run();

};

#endif // USERRECORDWARNINGDEADLINEPASSEDEMAILGENERATOR_H
