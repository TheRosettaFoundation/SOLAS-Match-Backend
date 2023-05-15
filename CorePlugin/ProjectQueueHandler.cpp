#include "ProjectQueueHandler.h"

#include <QThread>
#include <QTimer>
#include <QDebug>

#include "Common/ConfigParser.h"

#include "UserJobs/OrgCreatedNotifications.h"
#include "UserJobs/TaskRevokedNotificationHandler.h"
#include "TaskJobs/SendTaskUploadNotifications.h"

#include "Generators/OrgMembershipAcceptedGenerator.h"
#include "Generators/OrgMembershipRefusedEmailGenerator.h"
#include "Generators/PasswordResetEmailGenerator.h"
#include "Generators/TaskArchivedEmailGenerator.h"
#include "Generators/TaskClaimedEmailGenerator.h"
#include "Generators/UserTaskClaimEmailGenerator.h"
#include "Generators/UserTaskCancelledEmailGenerator.h"
#include "Generators/OrgFeedbackGenerator.h"
#include "Generators/UserFeedbackGenerator.h"
#include "Generators/TrackedTaskUploadedEmailGenerator.h"
#include "Generators/EmailVerificationGenerator.h"
#include "Generators/BannedLoginGenerator.h"
#include "Generators/ClaimedTaskSourceUpdatedGenerator.h"
#include "Generators/ClaimedTaskUploadedGenerator.h"
#include "Generators/OrgCreated_OrgEmail.h"
#include "Generators/OrgCreated_SiteAdmin.h"
#include "Generators/UserReferenceEmailGenerator.h"
#include "Generators/UserBadgeAwardedGenerator.h"
#include "Generators/UserTaskRevokedGenerator.h"
#include "Generators/OrgTaskRevokedGenerator.h"
#include "Generators/ProjectCreatedGenerator.h"
#include "Generators/NewImageUploadedEmailGenerator.h"
#include "Generators/ProjectImageRemovedEmailGenerator.h"
#include "Generators/ProjectImageApprovedEmailGenerator.h"
#include "Generators/ProjectImageDisapprovedEmailGenerator.h"

using namespace SolasMatch::Common::Protobufs::Requests;

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
                        SendTaskuploadNotifications::run(queue_request["task_id"].toInt());
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
