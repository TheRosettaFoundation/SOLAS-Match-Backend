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
    You have one week to complete the "{{TASK_TYPE}}" task for "{{TASK_TITLE}}" from {{SOURCE_LANGUAGE}} into {{TARGET_LANGUAGE}}. 
    Please ensure to finish and copy your file from Kató TM or upload your file before the deadline passes.
    If you have any questions about the deadline, please contact <a href="mailto:translators@translatorswithoutborders.org">translators@translatorswithoutborders.org</a>
</p>

<p>
    From,<br />
    The {{SITE_NAME}} Team
</p>


{{>FOOTER}}
