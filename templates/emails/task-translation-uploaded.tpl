<p>
    {{#USER_HAS_NAME}}
        {{USERNAME}},
    {{/USER_HAS_NAME}}
    {{#NO_USER_NAME}}
        Hello,
    {{/NO_USER_NAME}}
</p>

<p>
    A task that you are following on SOLAS Match has changed its status.
    The translator {{TRANSLATOR_NAME}} has uploaded a translation for the 
    file "{{TASK_TITLE}}". To download the the latest version of the file 
    please visit your <a href="{{DASHBOARD_URL}}">client dashboard</a>. 
    You will find the download button under the {{ORG_NAME}} title.
</p>
<p>
    The SOLAS Match Team
</p>
