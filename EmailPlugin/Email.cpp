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
    std::string no_bra_ket;
    no_bra_ket.reserve(in.length() + 5000);

    // Remove PREFIX_FOR_BRA and POSTFIX_FOR_KET to stop injection
    out = std::regex_replace( in, std::regex(R"(PREFIX_FOR_BRA)"),  "");
    out = std::regex_replace(out, std::regex(R"(POSTFIX_FOR_KET)"), "");

    // <p...> etc.
    out = std::regex_replace(out, std::regex(R"(<p[^<>]*>)"),      "PREFIX_FOR_BRA$&POSTFIX_FOR_KET");
    out = std::regex_replace(out, std::regex(R"(<span[^<>]*>)"),   "PREFIX_FOR_BRA$&POSTFIX_FOR_KET");
    out = std::regex_replace(out, std::regex(R"(<strong[^<>]*>)"), "PREFIX_FOR_BRA$&POSTFIX_FOR_KET");
    out = std::regex_replace(out, std::regex(R"(<em[^<>]*>)"),     "PREFIX_FOR_BRA$&POSTFIX_FOR_KET");
    out = std::regex_replace(out, std::regex(R"(<u[^<>]*>)"),      "PREFIX_FOR_BRA$&POSTFIX_FOR_KET");
    out = std::regex_replace(out, std::regex(R"(<a[^<>]*>)"),      "PREFIX_FOR_BRA$&POSTFIX_FOR_KET");
    out = std::regex_replace(out, std::regex(R"(<ol[^<>]*>)"),     "PREFIX_FOR_BRA$&POSTFIX_FOR_KET");
    out = std::regex_replace(out, std::regex(R"(<li[^<>]*>)"),     "PREFIX_FOR_BRA$&POSTFIX_FOR_KET");
    out = std::regex_replace(out, std::regex(R"(<br[^<>]*>)"),     "PREFIX_FOR_BRA$&POSTFIX_FOR_KET");

    // </p> etc.
    out = std::regex_replace(out, std::regex(R"(</p>)"),      "PREFIX_FOR_BRA$&POSTFIX_FOR_KET");
    out = std::regex_replace(out, std::regex(R"(</span>)"),   "PREFIX_FOR_BRA$&POSTFIX_FOR_KET");
    out = std::regex_replace(out, std::regex(R"(</strong>)"), "PREFIX_FOR_BRA$&POSTFIX_FOR_KET");
    out = std::regex_replace(out, std::regex(R"(</em>)"),     "PREFIX_FOR_BRA$&POSTFIX_FOR_KET");
    out = std::regex_replace(out, std::regex(R"(</u>)"),      "PREFIX_FOR_BRA$&POSTFIX_FOR_KET");
    out = std::regex_replace(out, std::regex(R"(</a>)"),      "PREFIX_FOR_BRA$&POSTFIX_FOR_KET");
    out = std::regex_replace(out, std::regex(R"(</ol>)"),     "PREFIX_FOR_BRA$&POSTFIX_FOR_KET");
    out = std::regex_replace(out, std::regex(R"(</li>)"),     "PREFIX_FOR_BRA$&POSTFIX_FOR_KET");

    // Remove < and >
    out = std::regex_replace(out, std::regex(R"(PREFIX_FOR_BRA<)"),  "PREFIX_FOR_BRA");
    out = std::regex_replace(out, std::regex(R"(>POSTFIX_FOR_KET)"), "POSTFIX_FOR_KET");

    for (std::string::size_type i = 0; i < out.length(); i++) {
        switch(out[i]) {
            case '<':
                no_bra_ket.append("&lt;");
                break;
            case '>':
                no_bra_ket.append("&gt;");
                break;
            default:
                no_bra_ket.append(&out[i], 1);
                break;
        }
    }

    no_bra_ket = std::regex_replace(no_bra_ket, std::regex(R"(\\r\\n)"), "<br/>");
    no_bra_ket = std::regex_replace(no_bra_ket, std::regex(R"(\\n)"),    "<br/>");
    no_bra_ket = std::regex_replace(no_bra_ket, std::regex(R"(\\r)"),    "<br/>");
    no_bra_ket = std::regex_replace(no_bra_ket, std::regex(R"(\\t)"),    "&nbsp;&nbsp;&nbsp;&nbsp;");

    // Replace < and >
    no_bra_ket = std::regex_replace(no_bra_ket, std::regex(R"(PREFIX_FOR_BRA)"),  "<");
    no_bra_ket = std::regex_replace(no_bra_ket, std::regex(R"(POSTFIX_FOR_KET)"), ">");

    return no_bra_ket;
}
/*
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
*/
