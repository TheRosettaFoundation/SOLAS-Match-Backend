#-------------------------------------------------
#
# Project created by @spaceindaver
#
#-------------------------------------------------

! include( ../Common.pri ) {
    error( "Couldn't find the Common.pri file!" )
}

QT       -= gui

TARGET = CorePlugin

TEMPLATE = lib

CONFIG += plugin

DESTDIR = ../plugins

LIBS += -L../Common -lCommon \
    -L/usr/local/lib -lprotobuf -lctemplate \
    -L/usr/lib

DEFINES += COREPLUGIN_LIBRARY

SOURCES += CorePlugin.cpp \
    TaskQueueHandler.cpp \
    TaskJobs/DeadlineChecker.cpp \
    UserQueueHandler.cpp \
    UserJobs/TaskStreamNotificationHandler.cpp \
    TaskJobs/SendTaskUploadNotifications.cpp \
    ProjectQueueHandler.cpp \
    UserJobs/OrgCreatedNotifications.cpp \
    UserJobs/TaskRevokedNotificationHandler.cpp \
    ../EmailPlugin/IEmailGenerator.cpp \
    ../EmailPlugin/Email.cpp \
    ../EmailPlugin/Generators/PasswordResetEmailGenerator.cpp \
    ../EmailPlugin/Generators/TaskArchivedEmailGenerator.cpp \
    ../EmailPlugin/Generators/TaskClaimedEmailGenerator.cpp \
    ../EmailPlugin/Generators/UserTaskClaimEmailGenerator.cpp \
    ../EmailPlugin/Generators/UserTaskCancelledEmailGenerator.cpp \
    ../EmailPlugin/Generators/OrgDeadlinePassedEmailGenerator.cpp \
    ../EmailPlugin/Generators/UserClaimedTaskEarlyWarningDeadlinePassedEmailGenerator.cpp \
    ../EmailPlugin/Generators/UserClaimedTaskLateWarningDeadlinePassedEmailGenerator.cpp \
    ../EmailPlugin/Generators/UserRecordWarningDeadlinePassedEmailGenerator.cpp \
    ../EmailPlugin/Generators/UserTaskDeadlineEmailGenerator.cpp \
    ../EmailPlugin/Generators/UserTaskStreamEmailGenerator.cpp \
    ../EmailPlugin/Generators/EmailVerificationGenerator.cpp \
    ../EmailPlugin/Generators/BannedLoginGenerator.cpp \
    ../EmailPlugin/Generators/TrackedTaskUploadedEmailGenerator.cpp \
    ../EmailPlugin/Generators/ClaimedTaskUploadedGenerator.cpp \
    ../EmailPlugin/Generators/OrgFeedbackGenerator.cpp \
    ../EmailPlugin/Generators/UserFeedbackGenerator.cpp \
    ../EmailPlugin/Generators/OrgCreated_OrgEmail.cpp \
    ../EmailPlugin/Generators/OrgCreated_SiteAdmin.cpp \
    ../EmailPlugin/Generators/UserReferenceEmailGenerator.cpp \
    ../EmailPlugin/Generators/UserBadgeAwardedGenerator.cpp \
    ../EmailPlugin/Generators/UserTaskRevokedGenerator.cpp \
    ../EmailPlugin/Generators/OrgTaskRevokedGenerator.cpp \
    ../EmailPlugin/Generators/NewImageUploadedEmailGenerator.cpp \
    ../EmailPlugin/Generators/ProjectImageRemovedEmailGenerator.cpp \

HEADERS += CorePlugin.h \
    ../EmailPlugin/IEmailGenerator.h \
    ../EmailPlugin/EmailDefinitions.h \
    ../EmailPlugin/Email.h \
    TaskQueueHandler.h \
    TaskJobs/DeadlineChecker.h \
    UserQueueHandler.h \
    UserJobs/TaskStreamNotificationHandler.h \
    TaskJobs/SendTaskUploadNotifications.h \
    ProjectQueueHandler.h \
    UserJobs/OrgCreatedNotifications.h \
    UserJobs/TaskRevokedNotificationHandler.h \
    ../EmailPlugin/Generators/PasswordResetEmailGenerator.h \
    ../EmailPlugin/Generators/TaskArchivedEmailGenerator.h \
    ../EmailPlugin/Generators/TaskClaimedEmailGenerator.h \
    ../EmailPlugin/Generators/UserTaskClaimEmailGenerator.h \
    ../EmailPlugin/Generators/UserTaskCancelledEmailGenerator.h \
    ../EmailPlugin/Generators/OrgDeadlinePassedEmailGenerator.h \
    ../EmailPlugin/Generators/UserClaimedTaskEarlyWarningDeadlinePassedEmailGenerator.h \
    ../EmailPlugin/Generators/UserClaimedTaskLateWarningDeadlinePassedEmailGenerator.h \
    ../EmailPlugin/Generators/UserRecordWarningDeadlinePassedEmailGenerator.h \
    ../EmailPlugin/Generators/UserTaskDeadlineEmailGenerator.h \
    ../EmailPlugin/Generators/UserTaskStreamEmailGenerator.h \
    ../EmailPlugin/Generators/EmailVerificationGenerator.h \
    ../EmailPlugin/Generators/BannedLoginGenerator.h \
    ../EmailPlugin/Generators/TrackedTaskUploadedEmailGenerator.h \
    ../EmailPlugin/Generators/ClaimedTaskUploadedGenerator.h \
    ../EmailPlugin/Generators/OrgFeedbackGenerator.h \
    ../EmailPlugin/Generators/UserFeedbackGenerator.h \
    ../EmailPlugin/Generators/OrgCreated_OrgEmail.h \
    ../EmailPlugin/Generators/OrgCreated_SiteAdmin.h \
    ../EmailPlugin/Generators/UserReferenceEmailGenerator.h \
    ../EmailPlugin/Generators/UserBadgeAwardedGenerator.h \
    ../EmailPlugin/Generators/UserTaskRevokedGenerator.h \
    ../EmailPlugin/Generators/OrgTaskRevokedGenerator.h \
    ../EmailPlugin/Generators/NewImageUploadedEmailGenerator.h \
    ../EmailPlugin/Generators/ProjectImageRemovedEmailGenerator.h \
