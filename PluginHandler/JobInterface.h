#ifndef JOBINTERFACE_H
#define JOBINTERFACE_H

#include <QRunnable>
#include <AMQPcpp.h>

class JobInterface : public QRunnable
{
public:
    virtual ~JobInterface() {}
    virtual void run() = 0;
};

#define JobInterface_iid "solas.match.job.interface/0.1"

Q_DECLARE_INTERFACE(JobInterface, JobInterface_iid)

#endif // JOBINTERFACE_H
