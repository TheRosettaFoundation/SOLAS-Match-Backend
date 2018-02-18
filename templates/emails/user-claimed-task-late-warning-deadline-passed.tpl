<p>
    {{#USER_HAS_NAME}}
        {{USERNAME}},
    {{/USER_HAS_NAME}}
    {{#NO_USER_NAME}}
        Hello,
    {{/NO_USER_NAME}}
</p>

<p>
    Thank you for claiming a volunteering task on Kató Trommons!
    This is to remind you that the "{{TASK_TYPE}}" task for "{{TASK_TITLE}}" from {{SOURCE_LANGUAGE}} into {{TARGET_LANGUAGE}} is overdue.
    Please ensure to finish and copy your file from Kató TM or upload your file as soon as possible.
    If you have any questions about this task, please contact <a href="mailto:translators@translatorswithoutborders.org">translators@translatorswithoutborders.org</a>
</p>

<p>
    From,<br />
    The {{SITE_NAME}} Team
</p>


{{>FOOTER}}
