#include "PluginScheduler.h"

#include <QXmlStreamReader>
#include <QTimer>
#include <QList>
#include <QFile>

#include <QDebug>

#include "TimedTask.h"
#include "RequestGenerator.h"

#include "Common/protobufs/requests/UserTaskScoreRequest.pb.h"

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
        QList<QPointer<TimedTask> > taskList = QList<QPointer<TimedTask> >();
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
                QTime interval = QTime(0, 0, 0);
                QXmlStreamAttributes atts = xmlReader.attributes();

                if(atts.hasAttribute("days")) {
                    qDebug() << "Days not supported";
                }
                if(atts.hasAttribute("hours")) {
                    interval = interval.addSecs(atts.value("hours").toString().toInt() * 60 * 60);
                }
                if(atts.hasAttribute("mins")) {
                    interval = interval.addSecs(atts.value("mins").toString().toInt() * 60);
                }
                if(atts.hasAttribute("secs")) {
                    interval = interval.addSecs(atts.value("secs").toString().toInt());
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
            QTime interval = taskItem->getInterval();
            int msecs;
            if(startTime > currentTime) {
                while(startTime > currentTime) {
                    startTime = startTime.addMSecs(-(this->timeInMSecs(interval)));
                }
                startTime = startTime.addMSecs(this->timeInMSecs(interval));
                msecs = currentTime.msecsTo(startTime);
            } else {
                while(currentTime > startTime) {
                    startTime = startTime.addMSecs(this->timeInMSecs(interval));
                }
                msecs = currentTime.msecsTo(startTime);
            }
            QTimer::singleShot(msecs, taskItem, SLOT(processAndStartTimer()));
        }
    }
}

void PluginScheduler::processTask(QPointer<TimedTask> task)
{
    qDebug() << "PluginScheduler::Processing task";
    RequestGenerator generator = RequestGenerator();
    if(task->getMessage() == "UserTaskScoreRequest") {
        QSharedPointer<UserTaskScoreRequest> request =
                generator.GenerateTask(QSharedPointer<UserTaskScoreRequest>(new UserTaskScoreRequest));

        MessagingClient client;
        client.init();
        client.publish(task->getExchange(), task->getTopic(),
                       QString::fromStdString(request->SerializeAsString()));
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

int PluginScheduler::timeInMSecs(QTime time)
{
    int msecs = (time.hour() * 60 * 60 * 1000);
    msecs += (time.minute() * 60 * 1000);
    msecs += (time.second() * 1000);
    return msecs;
}
