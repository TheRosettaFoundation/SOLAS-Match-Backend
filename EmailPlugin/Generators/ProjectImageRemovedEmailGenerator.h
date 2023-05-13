#ifndef PROJECTIMAGEREMOVEDEMAILGENERATOR_H
#define PROJECTIMAGEREMOVEDEMAILGENERATOR_H

#include "../IEmailGenerator.h"

class ProjectImageRemovedEmailGenerator: public IEmailGenerator
{
public:
    static void run(int project_id);
};
#endif // PROJECTIMAGEREMOVEDEMAILGENERATOR_H
