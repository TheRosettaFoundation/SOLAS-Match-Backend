#ifndef DEFINITIONS_H
#define DEFINITIONS_H

#include <QMap>
#include <QSharedPointer>
#include "Common/MessagingClient.h"
#include "Email.h"

typedef QMap<QSharedPointer<Email>, AMQPMessage *> EmailQueue;

#endif // DEFINITIONS_H
