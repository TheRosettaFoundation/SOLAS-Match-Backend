#ifndef NEWIMAGEUPLOADEDEMAILGENERATOR_H
#define NEWIMAGEUPLOADEDEMAILGENERATOR_H

#include "../IEmailGenerator.h"
#include "Common/protobufs/emails/ProjectImageUploadedEmail.pb.h"

class NewImageUploadedEmailGenerator: public IEmailGenerator
{
public:
    NewImageUploadedEmailGenerator();
    void run();

};
#endif // NEWIMAGEUPLOADEDEMAILGENERATOR_H
