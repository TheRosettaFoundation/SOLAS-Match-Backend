#ifndef DEFINITIONS_H
#define DEFINITIONS_H

enum TaskTypes {
    CHUNKING = 1,
    TRANSLATION = 2,
    PROOFREADING = 3,
    POSTEDITING = 4
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

#endif // DEFINITIONS_H
