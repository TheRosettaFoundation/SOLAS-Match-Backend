#ifndef PROJECTIMAGEREMOVEDEMAILGENERATOR_H
#define PROJECTIMAGEREMOVEDEMAILGENERATOR_H

#include "../IEmailGenerator.h"
#include "Common/protobufs/emails/ProjectImageRemovedEmail.pb.h"

class ProjectImageRemovedEmailGenerator: public IEmailGenerator
{
public:
    ProjectImageRemovedEmailGenerator();
    void run();

};
#endif // PROJECTIMAGEREMOVEDEMAILGENERATOR_H
