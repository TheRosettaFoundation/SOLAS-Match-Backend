#-------------------------------------------------
#
# Project created by QtCreator 2012-10-31T09:53:35
#
#-------------------------------------------------

! include( ../Common.pri ) {
    error( Couldn't find the Common.pri file! )
}

QT       += network

QT       -= gui

TARGET = EmailPlugin
TEMPLATE = lib

CONFIG += plugin qxt

QXT    += network

DESTDIR = ../plugins

LIBS += -L../Common -lCommon \
    -L/usr/local/lib -lamqpcpp -lrabbitmq \
    -lprotobuf -lctemplate

DEFINES += EMAILPLUGIN_LIBRARY

SOURCES += emailplugin.cpp \
    Smtp.cpp \
    Email.cpp \
    IEmailGenerator.cpp \
    Generators/OrgMembershipAcceptedGenerator.cpp \
    Generators/OrgMembershipRefusedEmailGenerator.cpp \
    Generators/TaskScoreEmailGenerator.cpp \
    Generators/PasswordResetEmailGenerator.cpp \
    Generators/TaskArchivedEmailGenerator.cpp \
    Generators/TaskClaimedEmailGenerator.cpp \
    Generators/UserTaskClaimEmailGenerator.cpp \
    Generators/OrgDeadlinePassedEmailGenerator.cpp \
    Generators/UserTaskDeadlineEmailGenerator.cpp \
    Generators/UserTaskStreamEmailGenerator.cpp \
    Generators/EmailVerificationGenerator.cpp \
    Generators/BannedLoginGenerator.cpp \
    Generators/TrackedTaskUploadedEmailGenerator.cpp \
    Generators/ClaimedTaskUploadedGenerator.cpp \
    Generators/ClaimedTaskSourceUpdatedGenerator.cpp \
    Generators/OrgFeedbackGenerator.cpp \
    Generators/UserFeedbackGenerator.cpp \
    Generators/OrgCreated_OrgEmail.cpp \
    Generators/OrgCreated_SiteAdmin.cpp \
    Generators/UserReferenceEmailGenerator.cpp \
    Generators/UserBadgeAwardedGenerator.cpp \
    Generators/UserTaskRevokedGenerator.cpp \
    Generators/OrgTaskRevokedGenerator.cpp \
    Generators/ProjectCreatedGenerator.cpp \
    Generators/NewImageUploadedEmailGenerator.cpp \
    Generators/ProjectImageRemovedEmailGenerator.cpp \
    Generators/ProjectImageApprovedEmailGenerator.cpp \
    Generators/ProjectImageDisapprovedEmailGenerator.cpp

HEADERS += emailplugin.h\
        Smtp.h \
    Email.h \
    Generators/TaskScoreEmailGenerator.h \
    IEmailGenerator.h \
    Generators/OrgMembershipAcceptedGenerator.h \
    Generators/OrgMembershipRefusedEmailGenerator.h \
    Generators/PasswordResetEmailGenerator.h \
    Generators/TaskArchivedEmailGenerator.h \
    Generators/TaskClaimedEmailGenerator.h \
    Generators/UserTaskClaimEmailGenerator.h \
    Generators/OrgDeadlinePassedEmailGenerator.h \
    Generators/UserTaskDeadlineEmailGenerator.h \
    Generators/UserTaskStreamEmailGenerator.h \
    Generators/EmailVerificationGenerator.h \
    Generators/BannedLoginGenerator.h \
    Generators/TrackedTaskUploadedEmailGenerator.h \
    Generators/ClaimedTaskUploadedGenerator.h \
    Generators/ClaimedTaskSourceUpdatedGenerator.h \
    EmailDefinitions.h \
    Generators/OrgFeedbackGenerator.h \
    Generators/UserFeedbackGenerator.h \
    Generators/OrgCreated_OrgEmail.h \
    Generators/OrgCreated_SiteAdmin.h \
    Generators/UserReferenceEmailGenerator.h \
    Generators/UserBadgeAwardedGenerator.h \
    Generators/UserTaskRevokedGenerator.h \
    Generators/OrgTaskRevokedGenerator.h \
    Generators/ProjectCreatedGenerator.h \
    Generators/NewImageUploadedEmailGenerator.h \
    Generators/ProjectImageRemovedEmailGenerator.h \
    Generators/ProjectImageApprovedEmailGenerator.h \
    Generators/ProjectImageDisapprovedEmailGenerator.h
