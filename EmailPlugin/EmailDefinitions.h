#ifndef EMAILDEFINITIONS_H
#define EMAILDEFINITIONS_H

#include <QMap>
#include <QSharedPointer>
#include "Common/MessagingClient.h"
#include "Email.h"

typedef QMap<QSharedPointer<Email>, AMQPMessage *> EmailQueue;

#define TEMPLATE_DIRECTORY "/etc/SOLAS-Match/templates/"

#endif // EMAILDEFINITIONS_H
