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
    Thank you for claiming a task on TWB Platform!
    The deadline for the {{TASK_TYPE}} task for
    "{{TASK_TITLE}}" from {{SOURCE_LANGUAGE}} into {{TARGET_LANGUAGE}} is {{DEADLINE_TIME}} UTC.
    You have 6 days left to complete the translation task. Please make sure you complete it before the deadline.
</p>
<p>
    Please translate this task in Phrase TMS, our CAT tool:<br />
    <a href="{{MATECAT}}">Translation URL</a>
</p>
<p>
    When all segments are translated, click "Complete".
</p>
{{/TRANSLATION}}
{{#REVISING}}
<p>
    Thank you for claiming a task on TWB Platform!
    The deadline for the {{TASK_TYPE}} task for
    "{{TASK_TITLE}}" from {{SOURCE_LANGUAGE}} into {{TARGET_LANGUAGE}} is {{DEADLINE_TIME}} UTC.
    You have 6 days left to complete the revision task. Please make sure you complete it before the deadline.
</p>
<p>
    Please revise this task in Phrase TMS, our CAT tool:<br />
    <a href="{{MATECAT}}">Revision URL</a>
</p>
<p>
    When all segments are revised, click "Complete".
</p>
{{/REVISING}}
{{#APPROVAL}}
<p>
    Thank you for claiming a task on TWB Platform!
    The deadline for the {{TASK_TYPE}} task for
    "{{TASK_TITLE}}" from {{SOURCE_LANGUAGE}} into {{TARGET_LANGUAGE}} is {{DEADLINE_TIME}} UTC.
    You have 6 days left to complete the revision task. Please make sure you complete it before the deadline.
</p>
<p>
    Please proofread this task in Phrase TMS, our CAT tool:<br />
    <a href="{{MATECAT}}">Proofreading and Approval URL</a>
</p>
<p>
    When all segments are proofread, click "Complete".
</p>
{{/APPROVAL}}
{{#SHELLTASK}}
<p>
    Thank you for claiming a task on TWB Platform!
    The deadline for the {{TASK_TYPE}} task for
    "{{TASK_TITLE}}" from {{SOURCE_LANGUAGE}} into {{TARGET_LANGUAGE}} is {{DEADLINE_TIME}} UTC.
    You have 6 days left to complete the task. Please make sure you complete it before the deadline.
</p>
{{/SHELLTASK}}
<p>
    If you have questions about the deadline or any other questions, please leave a comment in the TWB Community discussion thread associated with your project:<br />
    <a href="{{COMMUNITY}}">{{COMMUNITY}}</a>
</p>


{{>FOOTER}}
