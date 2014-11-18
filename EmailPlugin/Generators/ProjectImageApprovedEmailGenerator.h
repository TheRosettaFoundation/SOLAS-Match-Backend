#ifndef PROJECTIMAGEAPPROVEDEMAILGENERATOR_H
#define PROJECTIMAGEAPPROVEDEMAILGENERATOR_H

#include "../IEmailGenerator.h"
#include "Common/protobufs/emails/ProjectImageApprovedEmail.pb.h"

class ProjectImageApprovedEmailGenerator  : public IEmailGenerator
{
public:
    ProjectImageApprovedEmailGenerator();
    void run();
};

#endif // PROJECTIMAGEAPPROVEDEMAILGENERATOR_H
