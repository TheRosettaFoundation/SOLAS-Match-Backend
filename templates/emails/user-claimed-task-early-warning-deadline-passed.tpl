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
    You have one week remaining to complete the "{{TASK_TYPE}}" task for
    "{{TASK_TITLE}}" from {{SOURCE_LANGUAGE}} into {{TARGET_LANGUAGE}}.
    Please ensure that you complete the translation before the deadline and mark as complete on Kató TM and Kató Platform
    (click "Copy your translation from Kató TM to Kató").
</p>
<p>
    If you have any questions about the deadline, please leave a comment in the Kató Community discussion thread associated with your project:<br />
    <a href="{{COMMUNITY}}">{{COMMUNITY}}</a>
</p>


{{>FOOTER}}
