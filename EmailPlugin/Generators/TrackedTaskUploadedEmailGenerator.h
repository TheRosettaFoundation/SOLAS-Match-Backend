#ifndef TASKTRANSLATIONUPLOADEDEMAILGENERATOR_H
#define TASKTRANSLATIONUPLOADEDEMAILGENERATOR_H

#include "../IEmailGenerator.h"
#include "Common/protobufs/emails/TrackedTaskUploaded.pb.h"

class TrackedTaskUploadedEmailGenerator : public IEmailGenerator
{
public:
    TrackedTaskUploadedEmailGenerator();
    void run();

};

#endif // TASKTRANSLATIONUPLOADEDEMAILGENERATOR_H
