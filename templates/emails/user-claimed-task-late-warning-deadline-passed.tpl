<p>
    {{#USER_HAS_NAME}}
        {{USERNAME}},
    {{/USER_HAS_NAME}}
    {{#NO_USER_NAME}}
        Hello,
    {{/NO_USER_NAME}}
</p>

<p>
    Thank you for claiming a volunteering task on Trommons!
    This is to remind you that the "{{TASK_TYPE}}" task for "{{TASK_TITLE}}" from {{SOURCE_LANGUAGE}} into {{TARGET_LANGUAGE}} is overdue.
    Please ensure to upload your file as soon as possible. 
    If you have any questions about this task, please contact <a href="info@trommons.org">info@trommons.org</a>
</p>

<p>
    From,<br />
    The {{SITE_NAME}} Team
</p>


{{>FOOTER}}
