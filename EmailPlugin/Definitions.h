#ifndef DEFINITIONS_H
#define DEFINITIONS_H

#include <QMap>
#include <QSharedPointer>
#include "Common/MessagingClient.h"
#include "Email.h"

typedef QMap<QSharedPointer<Email>, AMQPMessage *> EmailQueue;

enum TaskTypes {
    CHUNKING = 1,
    TRANSLATION = 2,
    PROOFREADING = 3,
    POSTEDITING = 4
};

#define TEMPLATE_DIRECTORY "./templates/"

#endif // DEFINITIONS_H
