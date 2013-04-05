#ifndef DEFINITIONS_H
#define DEFINITIONS_H

#include <QQueue>
#include <QSharedPointer>
#include "Email.h"

typedef QQueue<QSharedPointer<Email> > EmailQueue;

#endif // DEFINITIONS_H
