#-------------------------------------------------
#
# Project created by QtCreator 2012-09-26T12:46:40
#
#-------------------------------------------------

! include( ../Common.pri ) {
    error( Couldn't find the Common.pri file! )
}

QT       += network sql

QT       -= gui

TARGET = Common

LIBS += -lprotobuf \
        -L/usr/local/lib -lamqpcpp -lrabbitmq

DEFINES += COMMON_LIBRARY

SOURCES += \
    ConfigParser.cpp \
    MySQLHandler.cpp \
    MessagingClient.cpp \
    protobufs/emails/EmailMessage.pb.cc \
    protobufs/emails/TaskScoreEmail.pb.cc \
    protobufs/emails/OrgMembershipAccepted.pb.cc \
    protobufs/emails/OrgMembershipRefused.pb.cc \
    protobufs/emails/PasswordResetEmail.pb.cc \
    protobufs/emails/TaskArchived.pb.cc \
    protobufs/emails/TaskClaimed.pb.cc \
    protobufs/emails/UserTaskClaim.pb.cc \
    ModelGenerator.cpp \
    protobufs/models/User.pb.cc \
    DataAccessObjects/UserDao.cpp \
    DataAccessObjects/TagDao.cpp \
    protobufs/models/Tag.pb.cc \
    protobufs/models/Organisation.pb.cc \
    DataAccessObjects/OrganisationDao.cpp \
    protobufs/models/ArchivedTask.pb.cc \
    DataAccessObjects/TaskDao.cpp \
    protobufs/models/Task.pb.cc \
    protobufs/requests/UserTaskScoreRequest.pb.cc \
    protobufs/requests/DeadlineCheckRequest.pb.cc \
    protobufs/emails/OrgTaskDeadlinePassed.pb.cc \
    protobufs/emails/UserClaimedTaskDeadlinePassed.pb.cc \
    protobufs/models/ArchivedProject.pb.cc \
    protobufs/models/Project.pb.cc \
    DataAccessObjects/ProjectDao.cpp \
    protobufs/models/Statistic.pb.cc \
    protobufs/requests/StatisticsUpdateRequest.pb.cc \
    protobufs/emails/UserTaskStreamEmail.pb.cc \
    protobufs/models/Language.pb.cc \
    DataAccessObjects/LanguageDao.cpp \
    protobufs/requests/UserTaskStreamNotificationRequest.pb.cc \
    protobufs/models/Locale.pb.cc \
    protobufs/emails/EmailVerification.pb.cc \
    protobufs/emails/BannedLogin.pb.cc \
    protobufs/models/BannedUser.pb.cc \
    protobufs/requests/RequestMessage.pb.cc \
    protobufs/requests/TaskUploadNotificationRequest.pb.cc \
    protobufs/emails/ClaimedTaskSourceUpdated.pb.cc \
    protobufs/emails/ClaimedTaskUploaded.pb.cc \
    protobufs/emails/TrackedTaskUploaded.pb.cc \
    protobufs/requests/CalculateProjectDeadlinesRequest.pb.cc \
    protobufs/models/WorkflowGraph.pb.cc \
    protobufs/models/WorkflowNode.pb.cc \
    GraphBuilder.cpp \
    protobufs/emails/OrgFeedback.pb.cc \
    protobufs/emails/UserFeedback.pb.cc \
    protobufs/requests/OrgCreatedNotificationRequest.pb.cc \
    DataAccessObjects/AdminDao.cpp \
    protobufs/emails/OrgCreatedOrgAdmin.pb.cc \
    protobufs/emails/OrgCreatedSiteAdmin.pb.cc \
    protobufs/models/UserTaskStreamNotification.pb.cc \
    protobufs/emails/UserReferenceEmail.pb.cc \
    protobufs/emails/UserBadgeAwardedEmail.pb.cc \
    protobufs/models/Badge.pb.cc \
    DataAccessObjects/BadgeDao.cpp

HEADERS +=\
    MySQLHandler.h \
    ConfigParser.h \
    MessagingClient.h \
    protobufs/emails/EmailMessage.pb.h \
    protobufs/emails/TaskScoreEmail.pb.h \
    protobufs/emails/OrgMembershipAccepted.pb.h \
    protobufs/emails/OrgMembershipRefused.pb.h \
    protobufs/emails/PasswordResetEmail.pb.h \
    protobufs/emails/TaskArchived.pb.h \
    protobufs/emails/TaskClaimed.pb.h \
    protobufs/emails/UserTaskClaim.pb.h \
    ModelGenerator.h \
    protobufs/models/User.pb.h \
    DataAccessObjects/UserDao.h \
    DataAccessObjects/TagDao.h \
    protobufs/models/Tag.pb.h \
    protobufs/models/Organisation.pb.h \
    DataAccessObjects/OrganisationDao.h \
    protobufs/models/ArchivedTask.pb.h \
    DataAccessObjects/TaskDao.h \
    protobufs/models/Task.pb.h \
    protobufs/requests/UserTaskScoreRequest.pb.h \
    protobufs/requests/DeadlineCheckRequest.pb.h \
    protobufs/emails/OrgTaskDeadlinePassed.pb.h \
    protobufs/emails/UserClaimedTaskDeadlinePassed.pb.h \
    protobufs/models/ArchivedProject.pb.h \
    protobufs/models/Project.pb.h \
    DataAccessObjects/ProjectDao.h \
    protobufs/models/Statistic.pb.h \
    protobufs/requests/StatisticsUpdateRequest.pb.h \
    protobufs/emails/UserTaskStreamEmail.pb.h \
    DataAccessObjects/LanguageDao.h \
    protobufs/models/Language.pb.h \
    protobufs/requests/UserTaskStreamNotificationRequest.pb.h \
    protobufs/models/Locale.pb.h \
    protobufs/emails/EmailVerification.pb.h \
    protobufs/emails/BannedLogin.pb.h \
    protobufs/models/BannedUser.pb.h \
    protobufs/requests/RequestMessage.pb.h \
    protobufs/requests/TaskUploadNotificationRequest.pb.h \
    protobufs/emails/ClaimedTaskSourceUpdated.pb.h \
    protobufs/emails/ClaimedTaskUploaded.pb.h \
    protobufs/emails/TrackedTaskUploaded.pb.h \
    protobufs/requests/CalculateProjectDeadlinesRequest.pb.h \
    Definitions.h \
    GraphBuilder.h \
    protobufs/models/WorkflowGraph.pb.h \
    protobufs/models/WorkflowNode.pb.h \
    protobufs/emails/OrgFeedback.pb.h \
    protobufs/emails/UserFeedback.pb.h \
    protobufs/requests/OrgCreatedNotificationRequest.pb.h \
    DataAccessObjects/AdminDao.h \
    protobufs/emails/OrgCreatedOrgAdmin.pb.h \
    protobufs/emails/OrgCreatedSiteAdmin.pb.h \
    protobufs/models/UserTaskStreamNotification.pb.h \
    protobufs/emails/UserReferenceEmail.pb.h \
    protobufs/emails/UserBadgeAwardedEmail.pb.h \
    DataAccessObjects/BadgeDao.h \
    protobufs/models/Badge.pb.h

symbian {
    MMP_RULES += EXPORTUNFROZEN
    TARGET.UID3 = 0xE198F06F
    TARGET.CAPABILITY = 
    TARGET.EPOCALLOWDLLDATA = 1
    addFiles.sources = Common.dll
    addFiles.path = !:/sys/bin
    DEPLOYMENT += addFiles
}

unix:!symbian {
    maemo5 {
        target.path = /opt/usr/lib
    } else {
        target.path = /usr/lib
    }
    INSTALLS += target
}
