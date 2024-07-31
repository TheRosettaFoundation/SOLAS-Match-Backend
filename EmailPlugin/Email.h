#ifndef EMAIL_H
#define EMAIL_H

#include <QString>
#include <QStringList>

class Email
{
public:
    static std::string htmlspecialchars(const std::string& in);
    static std::string uiCleanseHTMLNewlineAndTabs(const std::string& in);
    static std::string clean_project_description(const std::string& in);
};

#endif // EMAIL_H
