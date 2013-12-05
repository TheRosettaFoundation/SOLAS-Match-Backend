#ifndef PROJECTCREATEDGENERATOR_H
#define PROJECTCREATEDGENERATOR_H

#include "../IEmailGenerator.h"
#include "Common/protobufs/emails/ProjectCreatedEmail.pb.h"

class ProjectCreatedGenerator : public IEmailGenerator
{
public:
    ProjectCreatedGenerator();
    void run();

};

#endif // PROJECTCREATEDGENERATOR_H
