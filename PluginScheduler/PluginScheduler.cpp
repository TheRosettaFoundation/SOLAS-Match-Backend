#include "PluginScheduler.h"

#include <QXmlStreamReader>
#include <QList>
#include <QFile>

#include <QDebug>

#include "TimedTask.h"

#include "Common/ConfigParser.h"

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
        QList<QSharedPointer<TimedTask> > taskList = QList<QSharedPointer<TimedTask> >();
        QSharedPointer<TimedTask> task = QSharedPointer<TimedTask>();
        QXmlStreamReader xmlReader;
        xmlReader.setDevice(&xmlFile);
        while(!xmlReader.atEnd()) {
            xmlReader.readNext();

            if(xmlReader.name() == "task") {
                if(!xmlReader.isEndElement()) {
                    task = QSharedPointer<TimedTask>(new TimedTask());
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
            }
        }
        if(xmlReader.hasError()) {
            qDebug() << "XML Reader Error: " << xmlReader.errorString();
        }

        foreach(QSharedPointer<TimedTask> taskItem, taskList) {
            taskItem->printTask();
        }

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
