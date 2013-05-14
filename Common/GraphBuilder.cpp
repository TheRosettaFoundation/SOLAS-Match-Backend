#include "GraphBuilder.h"

#include <QMap>
#include <QDebug>

#include "Common/MySQLHandler.h"

#include "Common/DataAccessObjects/TaskDao.h"

GraphBuilder::GraphBuilder()
{
    this->graph = QSharedPointer<WorkflowGraph>();
}

bool GraphBuilder::getProjectGraph(int projectId)
{
    bool ret = true;
    if (this->graph.isNull()) {
        this->graph = QSharedPointer<WorkflowGraph>(new WorkflowGraph);
    }
    this->graph->Clear();
    this->graph->set_projectid(projectId);
    QSharedPointer<MySQLHandler> db = MySQLHandler::getInstance();
    QList<QSharedPointer<Task> > tasks = TaskDao::getTasks(db, -1, projectId);
    if (tasks.count() > 0) {
        QMap<int, QList<QSharedPointer<Task> > > taskPreReqs = QMap<int, QList<QSharedPointer<Task> > >();
        QList<int> previousLayer = QList<int>();
        QList<int> currentLayer = QList<int>();
        foreach (QSharedPointer<Task> task, tasks) {
            QList<QSharedPointer<Task> > preReqs = TaskDao::getTaskPreReqs(db, task->id());
            if (preReqs.count() < 1) {
                WorkflowNode *node = new WorkflowNode();
                node->set_taskid(task->id());
                this->insertNode(node);
                previousLayer.append(task->id());
            } else {
                taskPreReqs.insert(task->id(), preReqs);
            }
        }

        if (this->graph->rootnode_size() > 0) {
            while (taskPreReqs.count() > 0 && previousLayer.count() > 0) {
                QMapIterator<int, QList<QSharedPointer<Task> > > i(taskPreReqs);
                while (i.hasNext()) {
                    i.next();
                    QList<int> satisfiedPreReqs = QList<int>();
                    QList<QSharedPointer<Task> > preReqs = i.value();
                    foreach (QSharedPointer<Task> task, preReqs) {
                        if (previousLayer.contains(task->id())) {
                            satisfiedPreReqs.append(task->id());
                            preReqs.removeOne(task);
                        }
                    }

                    if (preReqs.count() < 1) {
                        WorkflowNode *newNode = new WorkflowNode();
                        newNode->set_taskid(i.key());

                        foreach (int preReqId, satisfiedPreReqs) {
                            newNode->add_previous(preReqId);

                            int nodeIndex = this->find(preReqId);
                            WorkflowNode *pNode = this->graph->mutable_allnodes(nodeIndex);
                            pNode->add_next(i.key());
                            this->updateNode(pNode);
                        }
                        this->insertNode(newNode);

                        currentLayer.append(i.key());
                        taskPreReqs.remove(i.key());
                    } else {
                        taskPreReqs.insert(i.key(), preReqs);
                    }
                }

                previousLayer = currentLayer;
                currentLayer.clear();
            }

            if (taskPreReqs.count() > 0) {
                qDebug() << "GraphBuilder: A deadlock occured";
                ret = false;
            }
        } else {
            qDebug() << "GraphBuilder: No root nodes present";
            ret = false;
        }
    } else {
        qDebug() << "GraphBuilder: No tasks present";
        ret = false;
    }

    return ret;
}

bool GraphBuilder::insertNode(WorkflowNode *node)
{
    bool ret = false;
    int index = this->find(node->taskid());
    if (index < 0) {
        if (node->previous_size() == 0) {
            this->graph->add_rootnode(node->taskid());
        }
        WorkflowNode *newNode = this->graph->add_allnodes();
        newNode->CopyFrom(*node);
        ret = true;
    }
    return ret;
}

bool GraphBuilder::updateNode(WorkflowNode *node)
{
    bool ret = false;
    int index = this->find(node->taskid());
    if (index >= 0) {
        if (node->previous_size() == 0) {
            if (!this->isRootNode(node->taskid())) {
                this->graph->add_rootnode(node->taskid());
            }
        } else {
            if (this->isRootNode(node->taskid())) {
                const::google::protobuf::RepeatedField< ::google::protobuf::int32> rootNodes = this->graph->rootnode();
                this->graph->clear_rootnode();
                foreach (::google::protobuf::int32 taskId, rootNodes) {
                    if (taskId != node->taskid()) {
                        this->graph->add_rootnode(taskId);
                    }
                }
            }
        }
        WorkflowNode *oldNode = this->graph->mutable_allnodes(index);
        oldNode->CopyFrom(*node);
        ret = true;
    }
    return ret;
}

int GraphBuilder::find(int taskId)
{
    int index = -1;
    int i = 0;
    while (i < this->graph->allnodes_size() && index == -1) {
        if (taskId == this->graph->allnodes(i).taskid()) {
            index = i;
        }
        i++;
    }
    return index;
}

QSharedPointer<WorkflowGraph> GraphBuilder::getGraph()
{
    return this->graph;
}

void GraphBuilder::setGraph(QSharedPointer<WorkflowGraph> graph)
{
    this->graph = graph;
}

bool GraphBuilder::isRootNode(int taskId)
{
    bool found = false;
    int i = 0;
    while (i < this->graph->rootnode_size() && !found) {
        if (this->graph->rootnode(i) == taskId) {
            found = true;
        }
        i++;
    }
    return found;
}

void GraphBuilder::printGraph()
{
    QString graphData = "";
    if (!this->graph.isNull()) {
        if (this->graph->rootnode_size() > 0) {
            QList<int> currentLayer = QList<int>();
            QList<int> nextLayer = QList<int>();

            graphData += "GraphData\n";
            int i = 0;
            while (i < this->graph->rootnode_size()) {
                int nodeId = this->graph->rootnode(i);
                int index = this->find(nodeId);
                WorkflowNode node = this->graph->allnodes(index);
                graphData += this->printNode(node);

                foreach (::google::protobuf::int32 nextId, node.next()) {
                    if (!nextLayer.contains(nextId)) {
                        nextLayer.append(nextId);
                    }
                }
                i++;
            }
            currentLayer = nextLayer;
            nextLayer.clear();

            while (currentLayer.count() > 0) {
                graphData += "\n";
                i = 0;
                while (i < currentLayer.count()) {
                    int nodeId = currentLayer.at(i);
                    int index = this->find(nodeId);
                    WorkflowNode node = this->graph->allnodes(index);
                    graphData += this->printNode(node);

                    foreach (::google::protobuf::int32 nextId, node.next()) {
                        if (!nextLayer.contains(nextId)) {
                            nextLayer.append(nextId);
                        }
                    }
                    i++;
                }
                currentLayer = nextLayer;
                nextLayer.clear();
            }
        } else {
            qDebug() << "GraphBuilder: Unable to print graph - no root nodes";
        }
    } else {
        qDebug() << "GraphBuilder: Unable to print graph - graph is null";
    }
    qDebug() << "==========================================\n" << graphData
             << "\n==================================================";
}

QString GraphBuilder::printNode(WorkflowNode node)
{
    QString nodeData = "";
    nodeData += "Node: " + QString::number(node.taskid());
    nodeData += " IN: [";
    foreach (::google::protobuf::int32 pId, node.previous()) {
        nodeData += QString::number(pId) + ", ";
    }
    nodeData += "] OUT: [";
    foreach (::google::protobuf::int32 pId, node.next()) {
        nodeData += QString::number(pId) + ", ";
    }
    nodeData += "]\n";
    return nodeData;
}
