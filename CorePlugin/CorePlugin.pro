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

CONFIG += plugin

DESTDIR = ../plugins

LIBS += -L../Common -lCommon \
    -L/usr/local/lib -lctemplate

DEFINES += COREPLUGIN_LIBRARY

SOURCES += CorePlugin.cpp \
    TaskQueueHandler.cpp \
    TaskJobs/DeadlineChecker.cpp \
    UserQueueHandler.cpp \
    UserJobs/TaskStreamNotificationHandler.cpp \
    TaskJobs/SendTaskUploadNotifications.cpp \
    ProjectQueueHandler.cpp \
    UserJobs/OrgCreatedNotifications.cpp \
    UserJobs/TaskRevokedNotificationHandler.cpp

HEADERS += CorePlugin.h \
    TaskQueueHandler.h \
    TaskJobs/DeadlineChecker.h \
    UserQueueHandler.h \
    UserJobs/TaskStreamNotificationHandler.h \
    TaskJobs/SendTaskUploadNotifications.h \
    ProjectQueueHandler.h \
    UserJobs/OrgCreatedNotifications.h \
    UserJobs/TaskRevokedNotificationHandler.h
