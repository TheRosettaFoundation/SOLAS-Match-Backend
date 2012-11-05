#ifndef EMAILGENERATOR_H
#define EMAILGENERATOR_H

#include <QString>

#include "Email.h"
#include "Common/protobufs/emails/TaskScoreEmail.pb.h"

class EmailGenerator
{
public:
    EmailGenerator();
    Email *generateEmail(TaskScoreEmail *email_message);

};

#endif // EMAILGENERATOR_H
