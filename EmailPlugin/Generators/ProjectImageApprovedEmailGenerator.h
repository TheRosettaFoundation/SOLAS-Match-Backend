#ifndef PROJECTIMAGEAPPROVEDEMAILGENERATOR_H
#define PROJECTIMAGEAPPROVEDEMAILGENERATOR_H

#include "../IEmailGenerator.h"

class ProjectImageApprovedEmailGenerator
{
public:
    static void run(int user_id, int project_id);
};

#endif // PROJECTIMAGEAPPROVEDEMAILGENERATOR_H
