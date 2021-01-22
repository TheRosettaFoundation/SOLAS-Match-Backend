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
    You have one week remaining to complete the "{{TASK_TYPE}}" task for
    "{{TASK_TITLE}}" from {{SOURCE_LANGUAGE}} into {{TARGET_LANGUAGE}}.
    Please ensure that you complete the translation before the deadline.
</p>
<p>
    To translate this task, please use memsource:<br />
    <a href="{{MATECAT}}">{{MATECAT}}</a><br />
    For more information, please see <a href="https://community.translatorswb.org/t/useful-posts-index/2883">Kató Q&A</a>.
</p>
<p>
    When all segments are translated, please ensure you click "Complete".
</p>
{{/TRANSLATION}}
{{#REVISING}}
<p>
    Thank you for claiming a task on Kató Platform!
    You have one week remaining to complete the "{{TASK_TYPE}}" task for
    "{{TASK_TITLE}}" from {{SOURCE_LANGUAGE}} into {{TARGET_LANGUAGE}}.
    Please ensure that you complete the revising task before the deadline.
</p>
<p>
    To revise this task, please use memsource:<br />
    <a href="{{MATECAT}}">{{MATECAT}}</a><br />
    For more information, please see <a href="https://community.translatorswb.org/t/useful-posts-index/2883">Kató Q&A</a>.
</p>
<p>
    When all segments are revised, please ensure you click "Complete".
</p>
{{/REVISING}}
<p>
    If you have any questions about the deadline or other questions, please leave a comment in the Kató Community discussion thread associated with your project:<br />
    <a href="{{COMMUNITY}}">{{COMMUNITY}}</a>
</p>


{{>FOOTER}}
