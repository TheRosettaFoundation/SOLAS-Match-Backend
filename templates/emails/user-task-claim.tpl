<p>
    {{#USER_HAS_NAME}}
        {{USERNAME}},
    {{/USER_HAS_NAME}}
    {{#NO_USER_NAME}}
        Hello,
    {{/NO_USER_NAME}}
</p>

<p>
    You have claimed a "{{TASK_TYPE}}" task for "{{TASK_TITLE}}" from {{SOURCE_LANGUAGE}} into {{TARGET_LANGUAGE}} on {{SITE_NAME}}.
</p>
<p>
    Thanks for helping to volunteer.
</p>
<p>
    As soon as you have processed the file you downloaded, 
    please upload the output file on the following page: <br />
    {{TASK_PAGE}}
</p>
<p>
    Sincerely,<br />
    The {{SITE_NAME}} Team
</p>


{{>FOOTER}}
