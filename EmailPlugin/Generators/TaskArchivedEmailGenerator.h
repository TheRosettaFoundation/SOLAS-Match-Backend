#ifndef TASKARCHIVEDEMAILGENERATOR_H
#define TASKARCHIVEDEMAILGENERATOR_H

#include "../IEmailGenerator.h"

class TaskArchivedEmailGenerator : public IEmailGenerator
{
public:
    TaskArchivedEmailGenerator();
    void run();

};

#endif // TASKARCHIVEDEMAILGENERATOR_H
