#ifndef ORGDEADLINEPASSEDEMAILGENERATOR_H
#define ORGDEADLINEPASSEDEMAILGENERATOR_H

#include "../IEmailGenerator.h"
#include "Common/protobufs/emails/OrgTaskDeadlinePassed.pb.h"

class OrgDeadlinePassedMailGenerator : public IEmailGenerator
{
public:
    OrgDeadlinePassedMailGenerator();
    void run();

};

#endif // ORGDEADLINEPASSEDEMAILGENERATOR_H
