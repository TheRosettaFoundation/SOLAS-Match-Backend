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
<p>{{TASK_INSTRUCTIONS}}</p>
<p>
    If you have questions about the deadline or any other questions, please leave a comment in the TWB Community forum thread associated with this project:<br />
    <a href="{{COMMUNITY}}">{{COMMUNITY}}</a>
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
<p>{{TASK_INSTRUCTIONS}}</p>
<p>
    If you have questions about the deadline or any other questions, please leave a comment in the TWB Community forum thread associated with this project:<br />
    <a href="{{COMMUNITY}}">{{COMMUNITY}}</a>
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
<p>{{TASK_INSTRUCTIONS}}</p>
<p>
    If you have questions about the deadline or any other questions, please leave a comment in the TWB Community forum thread associated with this project:<br />
    <a href="{{COMMUNITY}}">{{COMMUNITY}}</a>
</p>
{{/APPROVAL}}
{{#COURSE}}
<p>
    Thank you for enrolling on "{{TASK_TITLE}}" on TWB Learning Center! A matching task has been created for you on the TWB Platform.
    The deadline to complete the course is {{DEADLINE_TIME}} UTC. That’s in 6 days.
    We ask everyone to complete their courses within 3 months to help us keep the learning space active and make sure you maximize what you learn.
    Please complete the task before the deadline so your progress is saved and you get credited for the time spent on this activity.
</p>
<p>
   When the course is completed in TWB Learning Center, your TWB Platform task will be completed automatically.
</p>
{{/COURSE}}
{{#SPOT_QUALITY_INSPECTION}}
<p>
    Thank you for claiming a task on TWB Platform!
    The deadline for the {{TASK_TYPE}} task for
    "{{TASK_TITLE}}" from {{SOURCE_LANGUAGE}} into {{TARGET_LANGUAGE}} is {{DEADLINE_TIME}} UTC.
    You have 6 days left to complete the task. Please make sure you complete it before the deadline.
</p>
<p>
    Please inspect the quality of this task in Phrase TMS, our CAT tool:<br />
    <a href="{{MATECAT}}">Quality Inspection URL</a><br />
</p>
<p>
   When all segments are reviewed, click "Complete". And then go to My Tasks in TWB Platform to complete and submit your review.
</p>
<p>{{TASK_INSTRUCTIONS}}</p>
<p>
    If you have questions about the deadline or any other questions, please leave a comment in the TWB Community forum thread associated with this project:<br />
    <a href="{{COMMUNITY}}">{{COMMUNITY}}</a>
</p>
{{/SPOT_QUALITY_INSPECTION}}
{{#QUALITY_EVALUATION}}
<p>
    Thank you for claiming a task on TWB Platform!
    The deadline for the {{TASK_TYPE}} task for
    "{{TASK_TITLE}}" from {{SOURCE_LANGUAGE}} into {{TARGET_LANGUAGE}} is {{DEADLINE_TIME}} UTC.
    You have 6 days left to complete the task. Please make sure you complete it before the deadline.
</p>
<p>
    Please inspect the quality of this task in Phrase TMS, our CAT tool:<br />
    <a href="{{MATECAT}}">Quality Evaluation URL</a><br />
</p>
<p>
   When all segments are reviewed, click "Complete". And then go to My Tasks in TWB Platform to complete and submit your review.
</p>
<p>{{TASK_INSTRUCTIONS}}</p>
<p>
    If you have questions about the deadline or any other questions, please leave a comment in the TWB Community forum thread associated with this project:<br />
    <a href="{{COMMUNITY}}">{{COMMUNITY}}</a>
</p>
{{/QUALITY_EVALUATION}}
{{#SHELLTASK}}
<p>
    Thank you for claiming a task on TWB Platform!
    The deadline for the {{TASK_TYPE}} task for
    "{{TASK_TITLE}}" from {{SOURCE_LANGUAGE}} into {{TARGET_LANGUAGE}} is {{DEADLINE_TIME}} UTC.
    You have 6 days left to complete the task. Please make sure you complete it before the deadline.
</p>
<p>{{TASK_INSTRUCTIONS}}</p>
<p>
    If you have questions about the deadline or any other questions, please leave a comment in the TWB Community forum thread associated with this project:<br />
    <a href="{{COMMUNITY}}">{{COMMUNITY}}</a>
</p>
{{/SHELLTASK}}

{{>FOOTER}}
