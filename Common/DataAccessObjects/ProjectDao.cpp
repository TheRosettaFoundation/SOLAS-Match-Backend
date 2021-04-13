#include "ProjectDao.h"

#include "../ModelGenerator.h"

QList<QSharedPointer<Project> > ProjectDao::getProjects(QSharedPointer<MySQLHandler> db, int id, QString title, QString desc, QString impact,
                                                        QString deadline, int orgId, QString ref, int wordCount,
                                                        QString created, QString language, QString country, int imageUploaded, int imageApproved)
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
        args += "null, ";
    }

    if (imageUploaded != -1) {
        args += QString::number(imageUploaded) + ", ";
    } else {
        args += "null, ";
    }

    if (imageApproved != -1) {
        args += QString::number(imageApproved) + ", ";
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
                                               QString created, QString language, QString country, int imageUploaded, int imageApproved)
{
    QSharedPointer<Project> project;
    QList<QSharedPointer<Project> > projectList = ProjectDao::getProjects(db, id, title, desc, impact, deadline, orgId,
                                                                          ref, wordCount, created, language, country, imageUploaded, imageApproved);
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
    args += "null, null, null, null, null, null, null, null, null, null, null, null, null, null";

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

std::string ProjectDao::discourse_parameterize(const std::string a, int project_id)
{
    QString s = QString::fromUtf8(a.c_str());
//    if (project_id > 9277) { //(**)[dev project_id server ID] Backwards compatible
    if (project_id > 26399) { //(**)[KP ID] Backwards compatible
        s.append(" " + QString::number(project_id));
    }

    s.replace("\\r", "-");
    s.replace("\\n", "-");
    s.replace("\\t", "-");

    s.remove('\'');

    QString out("https://community.translatorswb.org/t/");
    for (int i = 0; i < s.length(); i++) {
        if (s[i] < 0x30) {
            out.append('-');
        } else if (s[i] >  0x017E) {
            out.append('-');
        } else if (s[i] >= 0x0179) {
            out.append('z');
        } else if (s[i] >= 0x0176) {
            out.append('y');
        } else if (s[i] >= 0x0174) {
            out.append('w');
        } else if (s[i] >= 0x0168) {
            out.append('u');
        } else if (s[i] >= 0x0162) {
            out.append('t');
        } else if (s[i] >= 0x015A) {
            out.append('s');
        } else if (s[i] >= 0x0154) {
            out.append('r');
        } else if (s[i] >= 0x0152) {
            out.append("oe");
        } else if (s[i] >= 0x014C) {
            out.append('o');
        } else if (s[i] >= 0x0143) {
            out.append('n');
        } else if (s[i] >= 0x0139) {
            out.append('l');
        } else if (s[i] >= 0x0136) {
            out.append('k');
        } else if (s[i] >= 0x0134) {
            out.append('j');
        } else if (s[i] >= 0x0132) {
            out.append("ij");
        } else if (s[i] >= 0x0128) {
            out.append('i');
        } else if (s[i] >= 0x0124) {
            out.append('h');
        } else if (s[i] >= 0x011C) {
            out.append('g');
        } else if (s[i] >= 0x0112) {
            out.append('e');
        } else if (s[i] >= 0x010E) {
            out.append('d');
        } else if (s[i] >= 0x0106) {
            out.append('c');
        } else if (s[i] >= 0x0100) {
            out.append('a');
        } else if (s[i] >= 0x007B && s[i] <= 0x00BF) {
            out.append('-');
        } else if (s[i] >= 0x003A && s[i] <= 0x0040) {
            out.append('-');
        } else if (s[i] >= 0x005B && s[i] <= 0x0060) {
            out.append('-');
        } else if (s[i] >= 0x00FF) {
            out.append('y');
        } else if (s[i] >= 0x00FE) {
            out.append("th");
        } else if (s[i] >= 0x00FD) {
            out.append('y');
        } else if (s[i] >= 0x00F9) {
            out.append('u');
        } else if (s[i] >= 0x00F8) {
            out.append('o');
        } else if (s[i] >= 0x00F7) {
            out.append('-');
        } else if (s[i] >= 0x00F2) {
            out.append('o');
        } else if (s[i] >= 0x00F1) {
            out.append('n');
        } else if (s[i] >= 0x00F0) {
            out.append('d');
        } else if (s[i] >= 0x00EC) {
            out.append('i');
        } else if (s[i] >= 0x00E8) {
            out.append('e');
        } else if (s[i] >= 0x00E7) {
            out.append('c');
        } else if (s[i] >= 0x00E6) {
            out.append("ae");
        } else if (s[i] >= 0x00E0) {
            out.append('a');
        } else if (s[i] >= 0x00DF) {
            out.append("ss");
        } else if (s[i] >= 0x00DE) {
            out.append("th");
        } else if (s[i] >= 0x00DD) {
            out.append('y');
        } else if (s[i] >= 0x00D9) {
            out.append('u');
        } else if (s[i] >= 0x00D8) {
            out.append('o');
        } else if (s[i] >= 0x00D7) {
            out.append('x');
        } else if (s[i] >= 0x00D2) {
            out.append('o');
        } else if (s[i] >= 0x00D1) {
            out.append('n');
        } else if (s[i] >= 0x00D0) {
            out.append('d');
        } else if (s[i] >= 0x00CC) {
            out.append('i');
        } else if (s[i] >= 0x00C8) {
            out.append('e');
        } else if (s[i] >= 0x00C7) {
            out.append('c');
        } else if (s[i] >= 0x00C6) {
            out.append("ae");
        } else if (s[i] >= 0x00C0) {
            out.append('a');
        } else {
            out.append(s[i]);
        }
    }

    while (out.length() > 0 && out[0] == '-') out.remove(0, 1);
    while (out.length() > 0 && out[out.length() - 1] == '-') out.remove(out.length() - 1, 1);
    int index;
    while ((index = out.indexOf("--")) != -1) out.remove(index, 1);

    return out.toLower().toStdString();
}
