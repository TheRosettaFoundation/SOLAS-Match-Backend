#ifndef DEFINITIONS_H
#define DEFINITIONS_H

#include <QString>
#include <QPair>

enum TaskTypes {
    CHUNKING     = 1,
    TRANSLATION  = 2,
    PROOFREADING = 3,
    POSTEDITING  = 4,
    QUALITY      = 5,
    APPROVAL     = 6
};

enum TaskStatus {
    WAITING_FOR_PREREQUISITES = 1,
    PENDING_CLAIM = 2,
    IN_PROGRESS = 3,
    COMPLETE = 4
};

enum BanTypes {
    DAY = 1,
    WEEK = 2,
    MONTH = 3,
    PERMANENT = 4
};

const int RETURN_ALL = 0;

// <languageCode, countryCode>
typedef QPair<std::string, std::string> LCCode;

typedef QPair<int, int> userTag;
typedef userTag taskTag;

struct LidMatch {
    LidMatch(const std::string & s1): key(s1) {}
    std::string key;
    bool operator()(const LCCode & x) const
    {
        return  x.first == key ;
    }


};

struct CidMatch {
    CidMatch(const std::string & s1): key(s1) {}
    std::string key;
    bool operator()(const LCCode & x) const
    {
        return  x.second == key ;
    }


};

// Queues for insert_queue_request...
#define TASKQUEUE    1
#define USERQUEUE    2
#define PROJECTQUEUE 3

// From PluginScheduler::processTask...
#define RUNTASKSTREAM                 200
#define RUNDEADLINECHECK              201
#define RUNSTATISTICSUPDATE           202

// From PHP (currently all to PROJECTQUEUE)...
#define EmailVerification              13
#define PasswordResetEmail              5
#define UserBadgeAwardedEmail          22
#define BannedLogin                    14
#define UserReferenceEmail             21
#define OrgCreatedNotificationRequest 100
#define OrgMembershipAccepted           3
#define OrgMembershipRefused            4
#define ProjectImageUploadedEmail      29
#define ProjectImageApprovedEmail      31
#define ProjectImageDisapprovedEmail   32
#define ProjectImageRemovedEmail       30
#define TaskArchived                    6
#define OrgFeedback                    18
#define UserTaskClaim                   2
#define TaskClaimed                     7
#define TaskUploadNotificationRequest 101
#define TaskRevokedNotification       102
#define UserFeedback                   11
#define UserTaskCancelled              36
#define OrgInvite                      37
#define draft_invoice                  38

// email send priorities
#define HIGH    3
#define MEDIUM  2
#define LOW     1
#define SENT    0

#define SITE_ADMIN         64
#define PROJECT_OFFICER    32
#define COMMUNITY_OFFICER  16
#define NGO_ADMIN           8
#define NGO_PROJECT_OFFICER 4
#define NGO_LINGUIST        2
#define LINGUIST            1


#endif // DEFINITIONS_H
