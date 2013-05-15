#ifndef CALCULATEPROJECTDEADLINES_H
#define CALCULATEPROJECTDEADLINES_H

#include <QSharedPointer>
#include <AMQPcpp.h>

#include "PluginHandler/JobInterface.h"

#include "Common/GraphBuilder.h"

#include "Common/protobufs/models/WorkflowGraph.pb.h"
#include "Common/protobufs/models/WorkflowNode.pb.h"
#include "Common/protobufs/models/Project.pb.h"

class CalculateProjectDeadlines : public JobInterface
{
    Q_INTERFACES(JobInterface)

public:
    CalculateProjectDeadlines();
    ~CalculateProjectDeadlines();
    void run();
    void setAMQPMessage(AMQPMessage *message);
    void calculateSubGraphDeadlines(WorkflowNode node, GraphBuilder builder, QSharedPointer<Project> project);

private:
    AMQPMessage *message;

};

#endif // CALCULATEPROJECTDEADLINES_H
