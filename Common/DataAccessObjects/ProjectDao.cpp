#include "ProjectDao.h"

#include "../ModelGenerator.h"

QList<QSharedPointer<Project> > ProjectDao::getProjects(QSharedPointer<MySQLHandler> db, int id, QString title, QString desc, QString impact,
                                                        QString deadline, int orgId, QString ref, int wordCount,
                                                        QString created, QString language, QString country)
{
    QList<QSharedPointer<Project> > ret = QList<QSharedPointer<Project> >();
    QString args = "";

    if (id != -1) {
        args += QString::number(id) + ", ";
    } else {
        args += "null, ";
    }

    if (title != "") {
        args += MySQLHandler::wrapString(title) + ", ";
    } else {
        args += "null, ";
    }

    if (desc != "") {
        args += MySQLHandler::wrapString(desc) + ", ";
    } else {
        args += "null, ";
    }

    if (impact != "") {
        args += MySQLHandler::wrapString(impact) + ", ";
    } else {
        args += "null, ";
    }

    if (deadline != "") {
        args += MySQLHandler::wrapString(deadline) + ", ";
    } else {
        args += "null, ";
    }

    if (orgId != -1) {
        args += QString::number(orgId) + ", ";
    } else {
        args += "null, ";
    }

    if (ref != "") {
        args += MySQLHandler::wrapString(ref) + ", ";
    } else {
        args += "null, ";
    }

    if (wordCount != -1) {
        args += QString::number(wordCount) + ", ";
    } else {
        args += "null, ";
    }

    if (created != "") {
        args += MySQLHandler::wrapString(created) + ", ";
    } else {
        args += "null, ";
    }

    if (language != "") {
        args += MySQLHandler::wrapString(language) = ", ";
    } else {
        args += "null, ";
    }

    if (country != "") {
        args += MySQLHandler::wrapString(country);
    } else {
        args += "null";
    }

    QSharedPointer<QSqlQuery> mQuery = db->call("getProject", args);
    if (mQuery->first()) {
        QMap<QString, int> fieldMap = MySQLHandler::getFieldMap(mQuery);
        do {
            QSharedPointer<Project> project = QSharedPointer<Project>(new Project());
            ModelGenerator::Generate(mQuery, project, fieldMap);
            ret.append(project);
        } while (mQuery->next());
    }

    return ret;
}

QSharedPointer<Project> ProjectDao::getProject(QSharedPointer<MySQLHandler> db, int id, QString title, QString desc, QString impact,
                                               QString deadline, int orgId, QString ref, int wordCount,
                                               QString created, QString language, QString country)
{
    QSharedPointer<Project> project;
    QList<QSharedPointer<Project> > projectList = ProjectDao::getProjects(db, id, title, desc, impact, deadline, orgId,
                                                                          ref, wordCount, created, language, country);
    if (projectList.count() > 0) {
        project = projectList.at(0);
    }
    return project;
}

QList<QSharedPointer<ArchivedProject> > ProjectDao::getArchivedProjects(QSharedPointer<MySQLHandler> db, int id)
{
    QList<QSharedPointer<ArchivedProject> > projects = QList<QSharedPointer<ArchivedProject> >();
    QString args = "";
    if (id > 0) {
        args += QString::number(id) + ", ";
    } else {
        args += "null, ";
    }
    args += "null, null, null, null, null, null, null, null, null, null";

    QSharedPointer<QSqlQuery> mQuery = db->call("getArchivedProject", args);
    if (mQuery->first()) {
        QMap<QString, int> fieldMap = MySQLHandler::getFieldMap(mQuery);
        do {
            QSharedPointer<ArchivedProject> project = QSharedPointer<ArchivedProject>(new ArchivedProject());
            ModelGenerator::Generate(mQuery, project, fieldMap);
            projects.append(project);
        } while (mQuery->next());
    }
    return projects;
}

QSharedPointer<ArchivedProject> ProjectDao::getArchivedProject(QSharedPointer<MySQLHandler> db, int id)
{
    QSharedPointer<ArchivedProject> project;
    QList<QSharedPointer<ArchivedProject> > projectList = ProjectDao::getArchivedProjects(db, id);
    if (projectList.count() > 0) {
        project = projectList.at(0);
    }
    return project;
}
