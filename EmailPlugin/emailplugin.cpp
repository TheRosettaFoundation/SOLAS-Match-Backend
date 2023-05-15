#include "emailplugin.h"

#include <QDebug>
#include <QTimer>

#include "qxtmailmessage.h"
#include "qxtsmtp.h"

#include "Smtp.h"
#include "Common/ConfigParser.h"

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
}

void EmailPlugin::setThreadPool(QThreadPool *tp)
{
    this->mThreadPool = tp;
}

bool EmailPlugin::isEnabled()
{
    return enabled;
}
