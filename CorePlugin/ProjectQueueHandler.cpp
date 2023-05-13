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
#include "Generators/NewImageUploadedEmailGenerator.h"
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
            QMap<QString, QVariant> queue_request = TaskDao::get_queue_request(db, PROJECTQUEUE);
            if (!queue_request.isNull()) {
                qDebug() << "ProjectQueueHandler type:" << queue_request["type"];
                switch (queue_request["type"]) {




                    case BannedLogin:
                    case EmailVerification:
                    case OrgFeedback:
                    case OrgMembershipAccepted:
                    case OrgMembershipRefused:
                    case PasswordResetEmail:
                    case ProjectImageApprovedEmail:
                    case ProjectImageDisapprovedEmail:
                    case ProjectImageRemovedEmail:
                    case ProjectImageUploadedEmail:
                    case TaskArchived:
                    case TaskClaimed:
                    case TaskScoreEmail:
                    case UserBadgeAwardedEmail:
                    case UserFeedback:
                    case UserReferenceEmail:
                    case UserTaskCancelled:
                    case UserTaskClaim:










                    case 3?:
NOT HERE                        TaskRevokedNotificationHandler::run(queue_request["task_id"], queue_request["claimant_id"]);
                    break;

                    case 3?:
NOT HERE                        OrgCreatedNotifications::run(queue_request["org_id"]);
                    break;



                    case 3?:
SendTaskuploadNotifications::run(queue_request["task_id"]);
                    break;





                    case 3?:
                        TaskRevokedNotificationHandler::run(queue_request["task_id"], queue_request["claimant_id"]);
                    break;

                    case 3?:
                        OrgCreatedNotifications::run(queue_request["org_id"]);
                    break;



    public static function sendBannedLoginEmail($userId)
            $proto->setUserId($userId);
            $message = $messagingClient->createMessageFromProto($proto);
            $messagingClient->sendTopicMessage(
    public static function sendEmailVerification($userId)
            $messageProto->setUserId($userId);
            $message = $messagingClient->createMessageFromProto($messageProto);
            $messagingClient->sendTopicMessage(
    public static function sendOrgFeedback($feedback)
            $message = $messagingClient->createMessageFromProto($feedback);
            $messagingClient->sendTopicMessage(
    public static function sendOrgCreatedNotifications($orgId)
            $proto->setOrgId($orgId);
            $message = $client->createMessageFromProto($proto);
            $client->sendTopicMessage(
    public static function sendUserAssignedBadgeEmail($userId, $badgeId)
            $proto->setUserId($userId);
            $proto->setBadgeId($badgeId);
            $message = $client->createMessageFromProto($proto);
            $client->sendTopicMessage(
    public static function sendUserFeedback($feedback)
            $message = $messagingClient->createMessageFromProto($feedback);
            $messagingClient->sendTopicMessage(
    public static function notifyUserClaimedTask($userId, $taskId)
            $message_type->setUserId($userId);
            $message_type->setTaskId($taskId);
            $message = $messagingClient->createMessageFromProto($message_type);
            $messagingClient->sendTopicMessage(
    public static function notifyUserTaskCancelled($userId, $taskId)
            $message_type->setUserId($userId);
            $message_type->setTaskId($taskId);
            $message = $messagingClient->createMessageFromProto($message_type);
            $messagingClient->sendTopicMessage(
    public static function sendPasswordResetEmail($user_id)
            $message_type->setUserId($user_id);
            $message = $messagingClient->createMessageFromProto($message_type);
            $messagingClient->sendTopicMessage(
    public static function notifyUserOrgMembershipRequest($userId, $orgId, $accepted)
                $message_type->setUserId($userId);
                $message_type->setOrgId($orgId);
                $message = $messagingClient->createMessageFromProto($message_type);
                $messagingClient->sendTopicMessage(
                $message_type->setUserId($userId);
                $message_type->setOrgId($orgId);
                $message = $messagingClient->createMessageFromProto($message_type);
                $messagingClient->sendTopicMessage(
    public static function notifyOrgClaimedTask($userId, $taskId)
                $message_type->setTaskId($taskId);
                $message_type->setTranslatorId($userId);
                    $message_type->setUserId($user->getId());
                    $message = $messagingClient->createMessageFromProto($message_type);
                    $messagingClient->sendTopicMessage(
    public static function sendTaskUploadNotifications($taskId, $version)
            $messageProto->setTaskId($taskId);
            $messageProto->setFileVersion($version);
            $message = $messagingClient->createMessageFromProto($messageProto);
            $messagingClient->sendTopicMessage(
    public static function sendTaskArchivedNotifications($taskId, $subscribedUsers)
                $message_type->setTaskId($taskId);
                    $message_type->setUserId($user->getId());
                    $message = $messagingClient->createMessageFromProto($message_type);
                    $messagingClient->sendTopicMessage(
    public static function sendTaskRevokedNotifications($taskId, $claimantId)
            $messageProto->setTaskId($taskId);
            $messageProto->setClaimantId($claimantId);
            $message = $client->createMessageFromProto($messageProto);
            $client->sendTopicMessage(
    public static function sendProjectImageUploaded($projectId)
            $proto->setProjectId($projectId);
            $message = $messagingClient->createMessageFromProto($proto);
            $messagingClient->sendTopicMessage(
    public static function sendProjectImageRemoved($projectId)
            $proto->setProjectId($projectId);
            $message = $messagingClient->createMessageFromProto($proto);
            $messagingClient->sendTopicMessage(
    public static function sendProjectImageApprovedEmail($projectId)
                $message_type->setProjectId($projectId);
                    $message_type->setUserId($user->getId());
                    $message = $messagingClient->createMessageFromProto($message_type);
                    $messagingClient->sendTopicMessage(
    public static function sendProjectImageDisapprovedEmail($projectId)
                $message_type->setProjectId($projectId);
                    $message_type->setUserId($user->getId());
                    $message = $messagingClient->createMessageFromProto($message_type);
                    $messagingClient->sendTopicMessage(


PHP Do to DB...
    public static function requestReference($userId)
    {
        $messagingClient = new Lib\MessagingClient();
        if ($messagingClient->init()) {
            $request = new Common\Protobufs\Emails\UserReferenceEmail();
            $request->setUserId($userId);
            $message = $messagingClient->createMessageFromProto($request);
            $messagingClient->sendTopicMessage(
                $message,
                $messagingClient->MainExchange,
                $messagingClient->UserReferenceRequestTopic
            );
        }
    }






                }
                TaskDao::mark_queue_request_sent(db, queue_request["id"]);
            }
        }
        mutex.unlock();
    } else qDebug() << "ProjectQueueHandler: Skipping consumeFromQueue() invocation";
}
