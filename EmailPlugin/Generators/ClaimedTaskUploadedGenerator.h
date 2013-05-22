#ifndef CLAIMEDTASKUPLOADEDGENERATOR_H
#define CLAIMEDTASKUPLOADEDGENERATOR_H

#include "../IEmailGenerator.h"

class ClaimedTaskUploadedGenerator : public IEmailGenerator
{
public:
    ClaimedTaskUploadedGenerator();
    void run();

};

#endif // CLAIMEDTASKUPLOADEDGENERATOR_H
