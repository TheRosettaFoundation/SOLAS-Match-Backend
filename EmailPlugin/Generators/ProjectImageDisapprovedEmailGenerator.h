#ifndef PROJECTIMAGEDISAPPROVEDEMAILGENERATOR_H
#define PROJECTIMAGEDISAPPROVEDEMAILGENERATOR_H

#include "../IEmailGenerator.h"
#include "Common/protobufs/emails/ProjectImageDisapprovedEmail.pb.h"

class ProjectImageDisapprovedEmailGenerator  : public IEmailGenerator
{
public:
    ProjectImageDisapprovedEmailGenerator();
    void run();
};

#endif // PROJECTIMAGEDISAPPROVEDEMAILGENERATOR_H
