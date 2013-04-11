#ifndef TASKARCHIVEDEMAILGENERATOR_H
#define TASKARCHIVEDEMAILGENERATOR_H

#include "../IEmailGenerator.h"
#include "Common/protobufs/emails/TaskArchived.pb.h"

class TaskArchivedEmailGenerator : public IEmailGenerator
{
public:
    TaskArchivedEmailGenerator();
    void run();

};

#endif // TASKARCHIVEDEMAILGENERATOR_H
