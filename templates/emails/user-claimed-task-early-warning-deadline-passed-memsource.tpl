<p>
    {{#USER_HAS_NAME}}
        {{USERNAME}},
    {{/USER_HAS_NAME}}
    {{#NO_USER_NAME}}
        Hello,
    {{/NO_USER_NAME}}
</p>

{{#TRANSLATION}}
<p>
    Thank you for claiming a task on Kató Platform!
    The deadline for the {{TASK_TYPE}} task for
    "{{TASK_TITLE}}" from {{SOURCE_LANGUAGE}} into {{TARGET_LANGUAGE}} is {{DEADLINE_TIME}}.
    You have 6 days left to complete the translation task. Please make sure you complete it before the deadline.
</p>
<p>
    Please translate this task in Memsource, our CAT tool:<br />
    <a href="{{MATECAT}}">Translation URL</a>
</p>
<p>
    When all segments are translated, click "Complete".
</p>
{{/TRANSLATION}}
{{#REVISING}}
<p>
    Thank you for claiming a task on Kató Platform!
    The deadline for the {{TASK_TYPE}} task for
    "{{TASK_TITLE}}" from {{SOURCE_LANGUAGE}} into {{TARGET_LANGUAGE}} is {{DEADLINE_TIME}}.
    You have 6 days left to complete the revision task. Please make sure you complete it before the deadline.
</p>
<p>
    Please revise this task in Memsource, our CAT tool:<br />
    <a href="{{MATECAT}}">Revision URL</a>
</p>
<p>
    When all segments are revised, click "Complete".
</p>
{{/REVISING}}
<p>
    If you have questions about the deadline or any other questions, please leave a comment in the Kató Community discussion thread associated with your project:<br />
    <a href="{{COMMUNITY}}">{{COMMUNITY}}</a>
</p>


{{>FOOTER}}
