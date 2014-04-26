#ifndef IREQUESTINTERFACE_H
#define IREQUESTINTERFACE_H

#include <QRunnable>
#include <QString>

class IRequestInterface : public QRunnable
{
public:
    IRequestInterface();

    virtual void run() = 0;

    void setProtoBody(QString proto);

protected:
    QString protoBody;

};


#endif // IREQUESTINTERFACE_H
