#ifndef EMAILVERIFICATIONGENERATOR_H
#define EMAILVERIFICATIONGENERATOR_H

#include "../IEmailGenerator.h"
#include "Common/protobufs/emails/EmailVerification.pb.h"

class EmailVerificationGenerator : public IEmailGenerator
{
public:
    EmailVerificationGenerator();
    void run();

};

#endif // EMAILVERIFICATIONGENERATOR_H
