#include "emailplugin.h"

#include <QDebug>
#include <QTimer>

#include "qxtmailmessage.h"
#include "qxtsmtp.h"

#include "Smtp.h"
#include "Common/ConfigParser.h"

using namespace SolasMatch::Common::Protobufs::Emails;

//QT4.8 (see Q_PLUGIN_METADATA for QT5) Q_EXPORT_PLUGIN2(EmailPlugin, EmailPlugin)

EmailPlugin::EmailPlugin()
{
    ConfigParser settings;
    enabled = (QString::compare("y", settings.get("mail.enabled")) == 0);
}

void EmailPlugin::run()
{
    qDebug() << "EmailPlugin::Starting new Thread " << this->thread()->currentThreadId();
    ConfigParser settings;

    smtp = new Smtp();

    QTimer *message_queue_read_timer = new QTimer();
    connect(message_queue_read_timer, SIGNAL(timeout()), this, SLOT(consumeFromQueue()));
    message_queue_read_timer->start(settings.get("messaging.poll_rate").toInt());
}

void EmailPlugin::consumeFromQueue()
{
    static QMutex mutex;
    if (mutex.tryLock()) {
        if (!QFileInfo::exists("/repo/SOLAS-Match-Backend/STOP_consumeFromQueue")) {
            QSharedPointer<MySQLHandler> db = MySQLHandler::getInstance();
            QMap<QString, QVariant> queue_request = TaskDao::get_queue_request(db, PROJECTQUEUE);
            if (!queue_request.isNull()) {



                TaskDao::mark_queue_request_sent(db, queue_request["id"]);
            }
        }
        mutex.unlock();
    } else qDebug() << "EmailPlugin: Skipping consumeFromQueue() invocation";
}

void EmailPlugin::setThreadPool(QThreadPool *tp)
{
    this->mThreadPool = tp;
}

bool EmailPlugin::isEnabled()
{
    return enabled;
}
