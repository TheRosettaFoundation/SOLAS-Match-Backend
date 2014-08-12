#ifndef GRAPHBUILDER_H
#define GRAPHBUILDER_H

#include <QSharedPointer>

#include "protobufs/models/WorkflowGraph.pb.h"
#include "protobufs/models/WorkflowNode.pb.h"

using namespace  SolasMatch::Common::Protobufs::Models;

class GraphBuilder
{
public:
    GraphBuilder();
    bool getProjectGraph(int projectId);
    bool insertNode(WorkflowNode *node);
    bool updateNode(WorkflowNode *node);
    bool isGraphValid();
    int find(int taskId);
    QSharedPointer<WorkflowGraph> getGraph();
    void printGraph();
    void setGraph(QSharedPointer<WorkflowGraph> graph);

private:
    bool isRootNode(int taskId);
    QString printNode(WorkflowNode node);
    QSharedPointer<WorkflowGraph> graph;

};

#endif // GRAPHBUILDER_H
