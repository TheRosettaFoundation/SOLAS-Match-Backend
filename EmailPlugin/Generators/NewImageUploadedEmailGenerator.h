#ifndef NEWIMAGEUPLOADEDEMAILGENERATOR_H
#define NEWIMAGEUPLOADEDEMAILGENERATOR_H

#include "../IEmailGenerator.h"

class NewImageUploadedEmailGenerator: public IEmailGenerator
{
public:
    void run(int project_id);
};
#endif // NEWIMAGEUPLOADEDEMAILGENERATOR_H
