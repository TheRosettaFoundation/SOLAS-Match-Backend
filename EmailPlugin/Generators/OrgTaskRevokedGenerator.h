#ifndef ORGTASKREVOKEDGENERATOR_H
#define ORGTASKREVOKEDGENERATOR_H

#include "../IEmailGenerator.h"
#include "Common/protobufs/emails/OrgTaskRevokedEmail.pb.h"

class OrgTaskRevokedGenerator : public IEmailGenerator
{
public:
    OrgTaskRevokedGenerator();
    void run();

};

#endif // ORGTASKREVOKEDGENERATOR_H
