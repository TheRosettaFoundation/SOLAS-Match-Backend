#include "ProjectQueueHandler.h"

#include <QThread>
#include <QTimer>
#include <QFileInfo>
#include <QDebug>

#include "Common/ConfigParser.h"

#include "UserJobs/OrgCreatedNotifications.h"
#include "UserJobs/TaskRevokedNotificationHandler.h"
#include "TaskJobs/SendTaskUploadNotifications.h"

#include "../EmailPlugin/Generators/OrgMembershipAcceptedGenerator.h"
#include "../EmailPlugin/Generators/OrgMembershipRefusedEmailGenerator.h"
#include "../EmailPlugin/Generators/PasswordResetEmailGenerator.h"
#include "../EmailPlugin/Generators/TaskArchivedEmailGenerator.h"
#include "../EmailPlugin/Generators/TaskClaimedEmailGenerator.h"
#include "../EmailPlugin/Generators/UserTaskClaimEmailGenerator.h"
#include "../EmailPlugin/Generators/UserTaskCancelledEmailGenerator.h"
#include "../EmailPlugin/Generators/OrgFeedbackGenerator.h"
#include "../EmailPlugin/Generators/UserFeedbackGenerator.h"
#include "../EmailPlugin/Generators/EmailVerificationGenerator.h"
#include "../EmailPlugin/Generators/BannedLoginGenerator.h"
#include "../EmailPlugin/Generators/OrgCreated_OrgEmail.h"
#include "../EmailPlugin/Generators/OrgCreated_SiteAdmin.h"
#include "../EmailPlugin/Generators/UserReferenceEmailGenerator.h"
#include "../EmailPlugin/Generators/UserBadgeAwardedGenerator.h"
#include "../EmailPlugin/Generators/UserTaskRevokedGenerator.h"
#include "../EmailPlugin/Generators/OrgTaskRevokedGenerator.h"
#include "../EmailPlugin/Generators/NewImageUploadedEmailGenerator.h"
#include "../EmailPlugin/Generators/ProjectImageRemovedEmailGenerator.h"
#include "../EmailPlugin/Generators/ProjectImageApprovedEmailGenerator.h"
#include "../EmailPlugin/Generators/ProjectImageDisapprovedEmailGenerator.h"

ProjectQueueHandler::ProjectQueueHandler()
{
    // Default Constructor
}

void ProjectQueueHandler::run()
{
    qDebug() << "Running ProjectQueueHandler on thread " << this->thread()->currentThreadId();
    ConfigParser settings;

    QTimer *message_queue_read_timer = new QTimer();
    connect(message_queue_read_timer, SIGNAL(timeout()), this, SLOT(consumeFromQueue()));
    message_queue_read_timer->start(settings.get("messaging.poll_rate").toInt());
}

void ProjectQueueHandler::consumeFromQueue()
{
    static QMutex mutex;
    if (mutex.tryLock()) {
        if (!QFileInfo::exists("/repo/SOLAS-Match-Backend/STOP_consumeFromQueue")) {
            QSharedPointer<MySQLHandler> db = MySQLHandler::getInstance();
            QMap<QString, QVariant> queue_request = UserDao::get_queue_request(db, PROJECTQUEUE);
            if (!queue_request.isEmpty()) {
                qDebug() << "ProjectQueueHandler type:" << queue_request["type"].toInt();
                switch (queue_request["type"].toInt()) {
                    case EmailVerification:
                        EmailVerificationGenerator::run(queue_request["user_id"].toInt());
                        break;
                    case PasswordResetEmail:
                        PasswordResetEmailGenerator::run(queue_request["user_id"].toInt());
                        break;
                    case UserBadgeAwardedEmail:
                        UserBadgeAwardedGenerator::run(queue_request["user_id"].toInt(), queue_request["badge_id"].toInt());
                        break;
                    case BannedLogin:
                        BannedLoginGenerator::run(queue_request["user_id"].toInt());
                        break;
                    case UserReferenceEmail:
                        UserReferenceEmailGenerator::run(queue_request["user_id"].toInt());
                        break;
                    case OrgCreatedNotificationRequest:
                        OrgCreatedNotifications::run(queue_request["org_id"].toInt());
                        break;
                    case OrgMembershipAccepted:
                        OrgMembershipAcceptedGenerator::run(queue_request["user_id"].toInt(), queue_request["org_id"].toInt());
                        break;
                    case OrgMembershipRefused:
                        OrgMembershipRefusedEmailGenerator::run(queue_request["user_id"].toInt(), queue_request["org_id"].toInt());
                        break;
                    case ProjectImageUploadedEmail:
                        NewImageUploadedEmailGenerator::run(queue_request["project_id"].toInt());
                        break;
                    case ProjectImageApprovedEmail:
                        ProjectImageApprovedEmailGenerator::run(queue_request["user_id"].toInt(), queue_request["project_id"].toInt());
                        break;
                    case ProjectImageDisapprovedEmail:
                        ProjectImageDisapprovedEmailGenerator::run(queue_request["user_id"].toInt(), queue_request["project_id"].toInt());
                        break;
                    case ProjectImageRemovedEmail:
                        ProjectImageRemovedEmailGenerator::run(queue_request["project_id"].toInt());
                        break;
                    case TaskArchived:
                        TaskArchivedEmailGenerator::run(queue_request["user_id"].toInt(), queue_request["task_id"].toInt());
                        break;
                    case OrgFeedback:
                        OrgFeedbackGenerator::run(queue_request["claimant_id"].toInt(), queue_request["task_id"].toInt(), queue_request["user_id"].toInt(), queue_request["feedback"].toString());  // user_id is admin or owner
                        break;
                    case UserTaskClaim:
                        UserTaskClaimEmailGenerator::run(queue_request["user_id"].toInt(), queue_request["task_id"].toInt());
                        break;
                    case TaskClaimed:
                        TaskClaimedEmailGenerator::run(queue_request["user_id"].toInt(), queue_request["task_id"].toInt(), queue_request["claimant_id"].toInt());
                        break;
                    case TaskUploadNotificationRequest:
                        XSendTaskuploadNotifications::run(queue_request["task_id"].toInt());
                        break;
                    case TaskRevokedNotification:
                        TaskRevokedNotificationHandler::run(queue_request["claimant_id"].toInt(), queue_request["task_id"].toInt());
                        break;
                    case UserFeedback:
                        UserFeedbackGenerator::run(queue_request["claimant_id"].toInt(), queue_request["task_id"].toInt(), queue_request["feedback"].toString());
                        break;
                    case UserTaskCancelled:
                        UserTaskCancelledEmailGenerator::run(queue_request["user_id"].toInt(), queue_request["task_id"].toInt());
                        break;
                }
                UserDao::mark_queue_request_handled(db, queue_request["id"].toInt());
            }
        }
        mutex.unlock();
    } else qDebug() << "ProjectQueueHandler: Skipping consumeFromQueue() invocation";
}
