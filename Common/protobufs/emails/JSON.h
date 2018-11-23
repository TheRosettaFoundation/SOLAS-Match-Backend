#include <string>
#include <QJsonObject>
#include <QJsonDocument>

namespace SolasMatch::Common::Protobufs::Emails {

class JSON
{
public:
    static bool isJSON(std::string json_serialized);
    void ParseFromString(std::string json_serialized);

    int email_type();
    int user_id();
    int project_id();
    int task_id();
    int claimant_id();
    int translator_id();
    int org_id();
    int org_member_id();
    int badge_id();
    int site_admin_id();
    int org_admin_id();
    int file_version();
    std::string class_name();
    std::string feedback();
    std::string body();
    std::string recipient_email();

private:
    QJsonObject json_object;
};

}
