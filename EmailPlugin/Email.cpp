#include "Email.h"

#include <QDebug>

#include <regex>

std::string Email::htmlspecialchars(const std::string& in)
{
    std::string out;
    out.reserve(in.length());
    for(std::string::size_type i = 0; i < in.length(); i++) {
        switch(in[i]) {
            case '<':
                out.append("&lt;");
                break;
            case '>':
                out.append("&gt;");
                break;
            default:
                out.append(&in[i], 1);
                break;
        }
    }
    return out;
}

std::string Email::uiCleanseHTMLNewlineAndTabs(const std::string& in)
{
    std::string out;
    out.reserve(in.length() + 50);

    bool crEncountered = false;
    for (std::string::size_type i = 0; i < in.length(); i++) {
        switch(in[i]) {
            case '<':
                out.append("&lt;");
                crEncountered = false;
                break;
            case '>':
                out.append("&gt;");
                crEncountered = false;
                break;
            case '\r':
                out.append("<br/>");
                crEncountered = true;
                break;
            case '\n':
                if (!crEncountered) out.append("<br/>"); // \r\n, \r will already have output <br/>
                crEncountered = false;
                break;
            case '\t':
                out.append("&nbsp;&nbsp;&nbsp;&nbsp;");
                crEncountered = false;
                break;
            default:
                out.append(&in[i], 1);
                crEncountered = false;
                break;
        }
    }

    // This set of replacements is what is needed and not the code above which may not be exercised except for '<' and '>'
    out = std::regex_replace(out, std::regex(R"(\\r\\n)"), "<br/>");
    out = std::regex_replace(out, std::regex(R"(\\n)"),    "<br/>");
    out = std::regex_replace(out, std::regex(R"(\\r)"),    "<br/>");
    out = std::regex_replace(out, std::regex(R"(\\t)"),    "&nbsp;&nbsp;&nbsp;&nbsp;");

    return out;
}

std::string Email::clean_project_description(const std::string& in)
{
    std::string out;
    out.reserve(in.length() + 5000);

    for (std::string::size_type i = 0; i < in.length(); i++) {
        switch(in[i]) {
            case '<':
                out.append("&lt;");
                break;
            case '>':
                out.append("&gt;");
                break;
            default:
                out.append(&in[i], 1);
                break;
        }
    }

    out = std::regex_replace(out, std::regex(R"(\\r\\n)"), "<br/>");
    out = std::regex_replace(out, std::regex(R"(\\n)"),    "<br/>");
    out = std::regex_replace(out, std::regex(R"(\\r)"),    "<br/>");
    out = std::regex_replace(out, std::regex(R"(\\t)"),    "&nbsp;&nbsp;&nbsp;&nbsp;");

    return out;
}
first remove PREFIX_FOR_BRA AND POSTFIX_FOR_KET so noone can inject
out = std::regex_replace(out, std::regex(R"(<p[^<>]*>)"), "PREFIX_FOR_BRA$&POSTFIX_FOR_KET");
tehn replace PREFIX_FOR_BRA< with PREFIX_FOR_BRA




<p...>
</p>

<span...>
</span>

<strong...>
</strong>

<em...>
</em>

<u...>
</u>


<a...>
</a>

<ol...>
</ol>

<li...>
</li>

<br...>

