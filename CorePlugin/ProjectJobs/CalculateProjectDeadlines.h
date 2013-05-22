#ifndef CALCULATEPROJECTDEADLINES_H
#define CALCULATEPROJECTDEADLINES_H

#include <QMap>
#include <QDateTime>
#include <AMQPcpp.h>
#include <QSharedPointer>

#include "PluginHandler/JobInterface.h"

#include "Common/GraphBuilder.h"
#include "Common/MySQLHandler.h"

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

private:
    void calculateSubGraphDeadlines(WorkflowNode node, GraphBuilder builder, QSharedPointer<Project> project,
                                    QSharedPointer<MySQLHandler> db);
    QMap<QString, int> calculateDeadlineDefaults(QMap<QString, int> deadlineDefaults, QList<QString> deadlineLengths,
                                                 QDateTime created, QDateTime deadline);
    QList<QString> parseGraphForDefaultLengths(QMap<QString, int> defaults, GraphBuilder builder,
                                               ::google::protobuf::RepeatedField< ::google::protobuf::int32> currentLayer,
                                               ::google::protobuf::RepeatedField< ::google::protobuf::int32> *leafNodes);
    void setProjectDeadlines(QList<QString> deadlineLengths, QMap<QString, int> defaults,
                             GraphBuilder builder, QDateTime projectDeadline, QSharedPointer<MySQLHandler> db,
                             ::google::protobuf::RepeatedField< ::google::protobuf::int32> currentLayer);
    AMQPMessage *message;

};

#endif // CALCULATEPROJECTDEADLINES_H
