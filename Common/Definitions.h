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

struct task_type_item {
    int enum_type;
    int enabled;
    std::string type;
};
struct task_type_item task_types[] = {
    {CHUNKING,     0, "Segmentation"},
    {TRANSLATION,  1, "Translation"},
    {PROOFREADING, 1, "Revising"},
    {POSTEDITING,  0, "Desegmentation"},
    {QUALITY,      0, "QA??"},
    {APPROVAL,     1, "Approval??"}
};
const int task_types_count = 6;

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

#endif // DEFINITIONS_H
