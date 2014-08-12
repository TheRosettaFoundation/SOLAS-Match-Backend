#ifndef LANGUAGEDAO_H
#define LANGUAGEDAO_H

#include <QList>
#include<QSharedPointer>

#include "Common/MySQLHandler.h"
#include "Common/protobufs/models/Language.pb.h"

using namespace SolasMatch::Common::Protobufs::Models;

class LanguageDao
{
public:
    static QList<QSharedPointer<Language> > getLanguages(QSharedPointer<MySQLHandler> db);
    static QSharedPointer<Language> getLanguage(QSharedPointer<MySQLHandler> db, int id = -1, QString code = "");

};

#endif // LANGUAGEDAO_H
