#include "PootlePlugin.h"

#include "Common/ConfigParser.h"
#include "Common/MessagingClient.h"
#include "Common/DataAccessObjects/TaskDao.h"
#include "Common/protobufs/emails/EmailMessage.pb.h"
#include "Common/protobufs/emails/PootleProjectCreated.pb.h"

#include <QDebug>
#include <QTimer>
#include <QDir>
#include <qjson/parser.h>
#include <QtNetwork/QNetworkReply>

PootlePlugin::PootlePlugin()
{
    // Default ctor
}

void PootlePlugin::run()
{
    qDebug() << "Running PootlePlugin";
    apiClient = new QNetworkAccessManager(this);
    fsWatcher = QSharedPointer<QFileSystemWatcher>(new QFileSystemWatcher());

    ConfigParser settings;
    QString pootleDirectory = settings.get("PootlePlugin.interface_directory");
    fsWatcher->addPath(pootleDirectory);

    connect(fsWatcher.data(), SIGNAL(directoryChanged(const QString&)), this, SLOT(directoryChanged(QString)));
    connect(apiClient, SIGNAL(finished(QNetworkReply*)), this, SLOT(apiRequestFinished(QNetworkReply*)));

    this->directoryChanged(pootleDirectory);
}

void PootlePlugin::directoryChanged(QString location)
{
    qDebug() << "PootlePlugin: Witnessed change at " << location;
    QDir trommonsDir = QDir(location);
    QStringList dirs = trommonsDir.entryList(QDir::Dirs | QDir::NoDotAndDotDot);
    foreach (QString dirName, dirs) {
        QString fullPath = trommonsDir.absolutePath() + "/" + dirName;
        if (!dirsToBeProcessed.contains(fullPath)) {
            dirsToBeProcessed.append(fullPath);
            QTimer::singleShot(5000, this, SLOT(processDirectory()));
        }
    }
}

void PootlePlugin::processDirectory()
{
    if (dirsToBeProcessed.length() > 0) {
        QString currentDirPath = dirsToBeProcessed.first() + "/";
        qDebug() << "Processing directory " << currentDirPath;
        dirsToBeProcessed.removeFirst();
        qDebug() << "Meta file location: " << currentDirPath + "meta.json";
        QFile meta(currentDirPath + "meta.json");
        if (meta.exists()) {
            this->processMetaFile(&meta, currentDirPath);
        } else {
            qDebug() << "PootlePlugin: No meta file, did something go wrong?";
        }
        this->removeDir(currentDirPath);
    } else {
        qDebug() << "PootlePlugin: No dir to be processed";
    }
}

void PootlePlugin::processMetaFile(QFile *file, QString location)
{
    if (!file->open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "PootlePlugin: Failed to open file " << file->fileName();
    } else {
        QString fileText = "";
        QTextStream in(file);
        while (!in.atEnd()) {
            fileText += in.readLine();
        }
        file->close();

        QJson::Parser parser;
        bool ok;
        QByteArray byteArray;
        byteArray.append(fileText);

        QVariantMap jsonMap = parser.parse(byteArray, &ok).toMap();
        if (!ok) {
            qDebug() << "Failed to parse JSON: " << fileText;
        } else {
            qDebug() << "Successfully parsed JSON " << fileText;
            if ((jsonMap.contains("created") && jsonMap["created"].toBool()) &&
                    !(jsonMap.contains("completed") && jsonMap["completed"].toBool())) {
                MessagingClient messagingClient;
                if (messagingClient.init()) {
                    PootleProjectCreated email;
                    email.set_email_type(EmailMessage::PootleProjectCreated);
                    email.set_link(jsonMap["backlink"].toString().toStdString());
                    int taskId = this->getTaskIdFromPath(location);
                    email.set_task_id(taskId);
                    QSharedPointer<MySQLHandler> db = MySQLHandler::getInstance();
                    QSharedPointer<User> user = TaskDao::getUserClaimedTask(db, taskId);
                    email.set_user_id(user->id());
                    ConfigParser settings;
                    QString exchange = settings.get("messaging.exchange");
                    QString topic = "email";
                    messagingClient.publish(exchange, topic, QString::fromStdString(email.SerializeAsString()));
                }
            } else if((jsonMap.contains("created") && jsonMap["created"].toBool()) &&
                      (jsonMap.contains("completed") && jsonMap["completed"].toBool())) {
                this->uploadOutputFile(location);
            } else {
                qDebug() << "PootlePlugin: Invalid JSON data";
            }
        }
    }
}

void PootlePlugin::uploadOutputFile(QString fileDirectory)
{
    qDebug() << "PootlePlugin: Pootle has completed processing the task, locate and upload the output file.";
    QDir fileDir(fileDirectory);
    QStringList nameFilters;
    nameFilters << "*.po";
    QStringList files = fileDir.entryList(nameFilters, QDir::Files);
    if (files.length() > 0) {
        QString filename;
        if (files.length() > 1) {
            qDebug() << "PootlePlugin: Found multiple files, selecting first for upload";
        }
        filename = files.first();
        int taskId = this->getTaskIdFromPath(fileDirectory);
        QSharedPointer<MySQLHandler> db = MySQLHandler::getInstance();
        QSharedPointer<User> user = TaskDao::getUserClaimedTask(db, taskId);
        ConfigParser settings;
        QUrl url(settings.get("site.api") + "v0/tasks/uploadOutputFile/" + QString::number(taskId) +
                 "/" + QString::number(user->id()) + ".json/");
        QNetworkRequest request(url);
        request.setHeader(QNetworkRequest::ContentTypeHeader, "text/plain");
        QFile file(fileDirectory + filename);
        if (file.exists()) {
            file.open(QIODevice::ReadOnly | QIODevice::Text);
            QByteArray fileData = file.readAll();
            file.close();
            qDebug() << "Calling PUT " << url << " with data " << fileData;
            apiClient->put(request, fileData);
        }
    }
}

int PootlePlugin::getTaskIdFromPath(QString path)
{
    int taskId = -1;
    QRegExp regex("task-(\\d+)");
    if (regex.indexIn(path) != -1) {
        taskId = regex.cap(1).toInt();
    } else {
        qDebug() << "PootlePlugin: regex did not match anything in string " + path;
    }
    return taskId;
}

void PootlePlugin::apiRequestFinished(QNetworkReply *reply)
{
    if (reply->error() == QNetworkReply::NoError) {
        qDebug() << "Successfully returned from API";
    } else {
        qDebug() << "Error returned from API: " << reply->errorString();
    }

    reply->deleteLater();
}

bool PootlePlugin::removeDir(QString dirName)
{
    bool result = true;
    QDir dir(dirName);

    if (dir.exists(dirName)) {
        Q_FOREACH(QFileInfo info, dir.entryInfoList(QDir::NoDotAndDotDot | QDir::System | QDir::Hidden  | QDir::AllDirs | QDir::Files, QDir::DirsFirst)) {
            if (info.isDir()) {
                result = this->removeDir(info.absoluteFilePath());
            }
            else {
                result = QFile::remove(info.absoluteFilePath());
            }

            if (!result) {
                return result;
            }
        }
        result = dir.rmdir(dirName);
    }
    return result;
}

void PootlePlugin::setThreadPool(QThreadPool *tp)
{
    this->mThreadPool = tp;
}

bool PootlePlugin::isEnabled()
{
    return true;
}
