<p>
    {{#USER_HAS_NAME}}
        {{USERNAME}},
    {{/USER_HAS_NAME}}
    {{#NO_USER_NAME}}
        Hello,
    {{/NO_USER_NAME}}
</p>
<p>
    Thank you for claiming a task on Kató Platform!
    This is to remind you that the "{{TASK_TYPE}}" task for "{{TASK_TITLE}}" from {{SOURCE_LANGUAGE}} into {{TARGET_LANGUAGE}} is overdue. The deadline for the task was on {{DEADLINE_TIME}}. 
</p>
{{#TRANSLATION}}
<p>
    Please translate this task in Memsource, our CAT tool:<br />
    <a href="{{MATECAT}}">Translation URL</a>
</p>
<p>
    When all segments are translated, click "Complete".
</p>
{{/TRANSLATION}}
