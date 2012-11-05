#include "EmailGenerator.h"

#include <QDebug>

EmailGenerator::EmailGenerator()
{
    //Empty constructor
}

Email *EmailGenerator::generateEmail(TaskScoreEmail *email_message)
{
    Q_UNUSED(email_message);
    Email *email = new Email();
    email->setRecipient("spaceindaver0@gmail.com");
    email->setSender("david.ocarroll@solas.match");
    email->setSubject("User Task Score Results");
    email->setBody(QString::fromStdString(email_message->body()));
    qDebug() << "This is a user task score email\n" << email->getBody();
    return email;
}
