#ifndef EMAILCOUNTCOMMAND_H
#define EMAILCOUNTCOMMAND_H

#include "ICommand.h"

#include <QTimer>

class EmailCountCommand : public ICommand
{
    Q_OBJECT

public:
    EmailCountCommand();
    virtual ~EmailCountCommand();

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
    MessagingClient* messagingClient;
    QTimer* message_queue_read_timer;

};

#endif // EMAILCOUNTCOMMAND_H
