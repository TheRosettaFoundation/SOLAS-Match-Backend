#ifndef CLAIMEDTASKUPLOADEDGENERATOR_H
#define CLAIMEDTASKUPLOADEDGENERATOR_H

#include "../IEmailGenerator.h"

class ClaimedTaskUploadedGenerator : public IEmailGenerator
{
public:
    static void run(int task_id, int translator_id);
};

#endif // CLAIMEDTASKUPLOADEDGENERATOR_H
