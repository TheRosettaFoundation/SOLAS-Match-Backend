#ifndef LANGUAGEDAO_H
#define LANGUAGEDAO_H

#include <QList>
#include<QSharedPointer>

#include "Common/MySQLHandler.h"
#include "Common/protobufs/models/Language.pb.h"

class LanguageDao
{
public:
    static QList<QSharedPointer<Language> > getLanguages(MySQLHandler *db);
    static QSharedPointer<Language> getLanguage(MySQLHandler *db, int id = -1, QString code = "");

};

#endif // LANGUAGEDAO_H
