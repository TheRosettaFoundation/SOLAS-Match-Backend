<p>
    {{#USER_HAS_NAME}}
        {{USERNAME}},
    {{/USER_HAS_NAME}}
    {{#NO_USER_NAME}}
        Hello,
    {{/NO_USER_NAME}}
</p>

<p>
{{#TRANSLATION}}
Thank you for claiming a task on Kató Platform!
You have 6 days remaining to complete the "{{TASK_TYPE}}" task for
"{{TASK_TITLE}}"
from {{SOURCE_LANGUAGE}} into {{TARGET_LANGUAGE}}.
Please ensure that you complete the translation before the deadline
and the status bar shows 100% on Kató TM here:<br />
<a href=
"{{MATECAT}}"
>
{{MATECAT}}
</a>
{{/TRANSLATION}}
{{#REVISING}}
Thank you for claiming a task on Kató Platform!
You have 6 days remaining to complete the "{{TASK_TYPE}}" task for
"{{TASK_TITLE}}"
from {{SOURCE_LANGUAGE}} into {{TARGET_LANGUAGE}}.
Please ensure that you complete the revising task before the deadline
and make sure the it is approved (status bar shows fully green) on Kató TM here:<br />
<a href=
"{{MATECAT}}"
>
{{MATECAT}}
</a>
{{/REVISING}}
</p>
<p>
If you have any questions about the deadline or other questions,
please leave a comment in the Kató Community discussion thread
associated with your project:<br />
<a href=
"{{COMMUNITY}}"
>
{{COMMUNITY}}
</a>
</p>


{{>FOOTER}}
