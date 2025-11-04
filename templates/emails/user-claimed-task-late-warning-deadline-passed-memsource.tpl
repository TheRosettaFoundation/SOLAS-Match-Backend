<p>
    {{#USER_HAS_NAME}}
        {{USERNAME}},
    {{/USER_HAS_NAME}}
    {{#NO_USER_NAME}}
        Hello,
    {{/NO_USER_NAME}}
</p>
<p>
    Thank you for claiming a task on TWB Platform!
    This is to remind you that the "{{TASK_TYPE}}" task for "{{TASK_TITLE}}" from {{SOURCE_LANGUAGE}} into {{TARGET_LANGUAGE}} is overdue. The deadline for the task was on {{DEADLINE_TIME}} UTC.
</p>
{{#TRANSLATION}}
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
    Please revise this task in Phrase TMS, our CAT tool:<br />
    <a href="{{MATECAT}}">Revision URL</a>
</p>
<p>
    When all segments are revised, click "Complete".
</p>
{{/REVISING}}
{{#APPROVAL}}
<p>
    Please proofread this task in Phrase TMS, our CAT tool:<br />
    <a href="{{MATECAT}}">Proofreading and Approval URL</a>
</p>
<p>
    When all segments are proofread, click "Complete".
</p>
{{/APPROVAL}}
{{#COURSE}}
<p>
    The deadline for "{{TASK_TITLE}}" on TWB Learning Center has passed more than a week ago.
    If there is no visible progress in the next 6 days, you will be automatically unenrolled from the course and your corresponding task will be deleted automatically, along with all the parts completed so far.
    This policy helps ensure our records reflect current participation.
</p>
<p>
    Any new progress on "{{TASK_TITLE}}" will extend your deadline by 2 weeks.
    When the course is completed in TWB Learning Center, your TWB Platform task will be completed automatically.
</p>
{{/COURSE}}
{{#SPOT_QUALITY_INSPECTION}}
<p>
    Please inspect the quality of this task in Phrase TMS, our CAT tool:<br />
    <a href="{{MATECAT}}">Quality Inspection URL</a><br />
</p>
<p>
   When all segments are reviewed, click "Complete". And then go to My Tasks in TWB Platform to complete and submit your review.
</p>
{{/SPOT_QUALITY_INSPECTION}}
{{#QUALITY_EVALUATION}}
<p>
    Please inspect the quality of this task in Phrase TMS, our CAT tool:<br />
    <a href="{{MATECAT}}">Quality Evaluation URL</a><br />
</p>
<p>
   When all segments are reviewed, click "Complete". And then go to My Tasks in TWB Platform to complete and submit your review.
</p>
{{/QUALITY_EVALUATION}}
<p>{{TASK_INSTRUCTIONS}}</p>
<p>
    Please complete the task as soon as possible. If you need a deadline extension or are unable to deliver this work,
    please leave a comment in the TWB Community forum thread associated with this project:<br />
    <a href="{{COMMUNITY}}">{{COMMUNITY}}</a><br />
    Please note that in some cases we are unable to extend task deadlines and would have to reassign the task to another translator.
    For more details please see <a href="https://community.translatorswb.org/t/deadlines-on-kato-platform/248">Deadlines on TWB Platform</a>
</p>


{{>FOOTER}}
