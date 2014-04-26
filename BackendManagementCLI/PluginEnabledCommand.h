#ifndef PLUGINENABLEDCOMMAND_H
#define PLUGINENABLEDCOMMAND_H

#include "ICommand.h"

#include "Common/MessagingClient.h"

#include <QTimer>

class PluginEnabledCommand : public ICommand
{
    Q_OBJECT

public:
    PluginEnabledCommand();
    ~PluginEnabledCommand();

    void printHelp(QString appName);
    bool isRequested(QStringList args);

public slots:
    void execute();
    void receivedResponse(AMQPMessage* message);
    void responseCanceled(QString error);
    void responseCanceled(AMQPMessage* message);

signals:
    void finished(QString response);

private:
    QString pluginName;
    MessagingClient* messagingClient;
    QTimer* message_queue_read_timer;

};

#endif // PLUGINENABLEDCOMMAND_H
