#include "PluginScheduler.h"

#include <QXmlStreamReader>
#include <QTimer>
#include <QList>
#include <QFile>

#include <QDebug>

#include "TimedTask.h"
#include "RequestGenerator.h"

#include "Common/protobufs/requests/UserTaskScoreRequest.pb.h"
#include "Common/protobufs/requests/DeadlineCheckRequest.pb.h"
#include "Common/protobufs/requests/StatisticsUpdateRequest.pb.h"

#include "Common/ConfigParser.h"
#include "Common/MessagingClient.h"

Q_EXPORT_PLUGIN2(PluginScheduler, PluginScheduler)

#define SCHEDULE_LOCATION "/etc/SOLAS-Match/schedule.xml"

PluginScheduler::PluginScheduler()
{
    ConfigParser settings;
    this->enabled = (QString::compare("y", settings.get("PluginScheduler.enabled")) == 0);
}

void PluginScheduler::run()
{
    qDebug() << "PluginScheduler::Starting new Thread " << this->thread()->currentThreadId();
    QFile xmlFile(SCHEDULE_LOCATION);
    if(!xmlFile.open(QFile::ReadOnly | QFile::Text)) {
        qDebug() << "PluginScheduler::ERROR: File " << SCHEDULE_LOCATION << " does not exist.";
    } else {
        taskList = QList<QPointer<TimedTask> >();
        QPointer<TimedTask> task = QPointer<TimedTask>();
        QXmlStreamReader xmlReader;
        xmlReader.setDevice(&xmlFile);
        while(!xmlReader.atEnd()) {
            xmlReader.readNext();

            if(xmlReader.name() == "task") {
                if(!xmlReader.isEndElement()) {
                    task = QPointer<TimedTask>(new TimedTask());
                    QXmlStreamAttributes atts = xmlReader.attributes();

                    if(atts.hasAttribute("startTime")) {
                        QTime startTime = QTime::fromString(
                                    atts.value("startTime").toString(), "hh:mm");
                        task->setStartTime(startTime);
                    }

                } else {
                    taskList.append(task);
                }
            }

            if(xmlReader.name() == "interval" && !xmlReader.isEndElement()) {
                QXmlStreamAttributes atts = xmlReader.attributes();
                TimeInterval interval;

                if(atts.hasAttribute("days")) {
                    interval.days = atts.value("days").toString().toInt();
                }
                if(atts.hasAttribute("hours")) {
                    interval.hours = atts.value("hours").toString().toInt();
                }
                if(atts.hasAttribute("mins")) {
                    interval.mins = atts.value("mins").toString().toInt();
                }
                if(atts.hasAttribute("secs")) {
                    interval.secs = atts.value("secs").toString().toInt();
                }

                task->setInterval(interval);
            }
            if(xmlReader.name() == "message" && !xmlReader.isEndElement()) {
                QXmlStreamAttributes atts = xmlReader.attributes();

                if(atts.hasAttribute("exchange")) {
                    task->setExchange(atts.value("exchange").toString());
                }
                if(atts.hasAttribute("topic")) {
                    task->setTopic(atts.value("topic").toString());
                }

                task->setMessage(xmlReader.readElementText().trimmed());
            }
        }
        if(xmlReader.hasError()) {
            qDebug() << "XML Reader Error: " << xmlReader.errorString();
        }

        foreach(QPointer<TimedTask> taskItem, taskList) {
            taskItem->printTask();

            connect(taskItem, SIGNAL(processTask(QPointer<TimedTask>)), this, SLOT(processTask(QPointer<TimedTask>)));

            QTime currentTime = QTime::currentTime();
            QTime startTime = taskItem->getStartTime();
            int msecs;
            if(startTime == startTime.addMSecs(taskItem->getIntervalInMSecs())) {
                qDebug() << "Run every day at same time";
            } else if(startTime > currentTime) {
                while(startTime > currentTime) {
                    startTime = startTime.addMSecs(-(taskItem->getIntervalInMSecs()));
                }
                startTime = startTime.addMSecs(taskItem->getIntervalInMSecs());
            } else {
                while(currentTime > startTime) {
                    startTime = startTime.addMSecs(taskItem->getIntervalInMSecs());
                }
            }
            msecs = currentTime.msecsTo(startTime);
            if(msecs < 0) {
                msecs += 86400000; //one day in msecs
            }
            QTimer::singleShot(msecs, taskItem, SLOT(processAndStartTimer()));
        }
    }
}

void PluginScheduler::processTask(QPointer<TimedTask> task)
{
    qDebug() << "PluginScheduler::Processing task";
    RequestGenerator generator = RequestGenerator();
    QSharedPointer< ::google::protobuf::Message> request = QSharedPointer< ::google::protobuf::Message>();
    if(task->getMessage() == "UserTaskScoreRequest") {
        request = generator.GenerateTask(QSharedPointer<UserTaskScoreRequest>(new UserTaskScoreRequest));
    } else if(task->getMessage() == "DeadlineCheckRequest") {
        request = generator.GenerateTask(QSharedPointer<DeadlineCheckRequest>(new DeadlineCheckRequest));
    } else if (task->getMessage() == "StatisticsUpdateRequest") {
        request = generator.GenerateTask(QSharedPointer<StatisticsUpdateRequest>(new StatisticsUpdateRequest));
    } else if (task->getMessage() == "UserTaskStreamNotificationRequest") {
        request = generator.GenerateTask(QSharedPointer<UserTaskStreamNotificationRequest>
                                         (new UserTaskStreamNotificationRequest));
    }

    if(request) {
        MessagingClient client;
        client.init();
        client.publish(task->getExchange(), task->getTopic(),
                       QString::fromStdString(request->SerializeAsString()));
    } else {
        qDebug() << "PluginScheduler: Invalid request type";
    }
}

void PluginScheduler::setThreadPool(QThreadPool *tp)
{
    this->mThreadPool = tp;
}

bool PluginScheduler::isEnabled()
{
    return this->enabled;
}
