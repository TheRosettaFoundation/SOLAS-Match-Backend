#ifndef PROJECTIMAGESTATUSCHANGEDEMAILGENERATOR_H
#define PROJECTIMAGESTATUSCHANGEDEMAILGENERATOR_H

#include "../IEmailGenerator.h"
#include "Common/protobufs/emails/ProjectImageStatusChangedEmail.pb.h"

class ProjectImageStatusChangedEmailGenerator: public IEmailGenerator
{
public:
    ProjectImageStatusChangedEmailGenerator();
    void run();

};

#endif // PROJECTIMAGESTATUSCHANGEDEMAILGENERATOR_H
