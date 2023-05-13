#ifndef SENDTASKUPLOADNOTIFICATIONS_H
#define SENDTASKUPLOADNOTIFICATIONS_H

#include <QList>
#include <QSharedPointer>

#include "Common/MySQLHandler.h"

class SendTaskUploadNotifications
{
public:
    static void run(int task_id);
private:
};

#endif // SENDTASKUPLOADNOTIFICATIONS_H
