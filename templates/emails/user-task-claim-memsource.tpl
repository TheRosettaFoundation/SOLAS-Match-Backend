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
    You claimed a {{TASK_TYPE}} task for "{{TASK_TITLE}}" from {{SOURCE_LANGUAGE}} into {{TARGET_LANGUAGE}} with Translators without Borders.
    You can review the task instructions and find the link to Phrase TMS, our CAT Tool, here:<br />
    <a href="{{TASK_PAGE}}">Task View URL</a>
</p>
<p>
    When all segments are translated, click "Complete" to finish the task.
</p>
{{/TRANSLATION}}
{{#TRANSLATION_WAIT}}
<p>
    You claimed a {{TASK_TYPE}} task for "{{TASK_TITLE}}" from {{SOURCE_LANGUAGE}} into {{TARGET_LANGUAGE}} with Translators without Borders.
    You can review the task instructions and find the link to Phrase TMS, our CAT Tool, here:<br />
    <a href="{{TASK_PAGE}}">Task View URL</a>
</p>
<p>
    When all segments are translated, click "Complete" to finish the task.
</p>
{{/TRANSLATION_WAIT}}
{{#REVISING}}
<p>
    You claimed a {{TASK_TYPE}} task for "{{TASK_TITLE}}" from {{SOURCE_LANGUAGE}} into {{TARGET_LANGUAGE}} with Translators without Borders.
    You can review the task instructions and find the link to Phrase TMS, our CAT Tool, here:<br />
    <a href="{{TASK_PAGE}}">Task View URL</a>
</p>
<p>
   When all segments are revised, click "Complete" to finish the task.
</p>
{{/REVISING}}
{{#REVISING_WAIT}}
<p>
    You claimed a {{TASK_TYPE}} task for "{{TASK_TITLE}}" from {{SOURCE_LANGUAGE}} into {{TARGET_LANGUAGE}} with Translators without Borders.
</p>
<p>
    <strong>You will receive an email notification when the task is ready for you to revise.</strong> In the meantime, you can review the task instructions here:<br />
    <a href="{{TASK_PAGE}}">Task View URL</a>
</p>
<p>{{PREVIOUS_DEADLINE_TIME}}</p>
{{/REVISING_WAIT}}
{{#APPROVAL}}
<p>
    You claimed a {{TASK_TYPE}} task for "{{TASK_TITLE}}" from {{SOURCE_LANGUAGE}} into {{TARGET_LANGUAGE}} with Translators without Borders.
    You can review the task instructions and find the link to Phrase TMS, our CAT Tool, here:<br />
    <a href="{{TASK_PAGE}}">Task View URL</a>
</p>
<p>
   When all segments are proofread, click "Complete" to finish the task.
</p>
{{/APPROVAL}}
{{#APPROVAL_WAIT}}
<p>
    You claimed a {{TASK_TYPE}} task for "{{TASK_TITLE}}" from {{SOURCE_LANGUAGE}} into {{TARGET_LANGUAGE}} with Translators without Borders.
</p>
<p>
    <strong>You will receive an email notification when the task is ready for you to proofread.</strong> In the meantime, you can review the task instructions here:<br />
    <a href="{{TASK_PAGE}}">Task View URL</a>
</p>
<p>{{PREVIOUS_DEADLINE_TIME}}</p>
{{/APPROVAL_WAIT}}
{{#SPOT_QUALITY_INSPECTION}}
<p>
    You claimed a {{TASK_TYPE}} task for "{{TASK_TITLE}}" from {{SOURCE_LANGUAGE}} into {{TARGET_LANGUAGE}} with Translators without Borders.
    You can review the task instructions and find the link to Phrase TMS, our CAT Tool, here:<br />
    <a href="{{TASK_PAGE}}">Task View URL</a>
</p>
<p>
   When all segments are reviewed, click "Complete". Then, go to My Tasks in TWB Platform to complete and submit your review.
</p>
{{/SPOT_QUALITY_INSPECTION}}
{{#SPOT_QUALITY_INSPECTION_WAIT}}
<p>
    You claimed a {{TASK_TYPE}} task for "{{TASK_TITLE}}" from {{SOURCE_LANGUAGE}} into {{TARGET_LANGUAGE}} with Translators without Borders.
    You can review the task instructions and find the link to Phrase TMS, our CAT Tool, here:<br />
    <a href="{{TASK_PAGE}}">Task View URL</a>
</p>
<p>
   When all segments are reviewed, click "Complete". Then, go to My Tasks in TWB Platform to complete and submit your review.
</p>
{{/SPOT_QUALITY_INSPECTION_WAIT}}
{{#QUALITY_EVALUATION}}
<p>
    You claimed a {{TASK_TYPE}} task for "{{TASK_TITLE}}" from {{SOURCE_LANGUAGE}} into {{TARGET_LANGUAGE}} with Translators without Borders.
    You can review the task instructions and find the link to Phrase TMS, our CAT Tool, here:<br />
    <a href="{{TASK_PAGE}}">Task View URL</a>
</p>
<p>
   When all segments are reviewed, click "Complete". Then, go to My Tasks in TWB Platform to complete and submit your review.
</p>
{{/QUALITY_EVALUATION}}
{{#QUALITY_EVALUATION_WAIT}}
<p>
    You claimed a {{TASK_TYPE}} task for "{{TASK_TITLE}}" from {{SOURCE_LANGUAGE}} into {{TARGET_LANGUAGE}} with Translators without Borders.
    You can review the task instructions and find the link to Phrase TMS, our CAT Tool, here:<br />
    <a href="{{TASK_PAGE}}">Task View URL</a>
</p>
<p>
   When all segments are reviewed, click "Complete". Then, go to My Tasks in TWB Platform to complete and submit your review.
</p>
{{/QUALITY_EVALUATION_WAIT}}
{{#SHELLTASK}}
<p>
    You have been assigned a {{TASK_TYPE}} task for "{{TASK_TITLE}}" from {{SOURCE_LANGUAGE}} into {{TARGET_LANGUAGE}} with Translators without Borders.
    You can review the task instructions here:<br />
    <a href="{{TASK_PAGE}}">Task View URL</a>
</p>
{{MATECAT}}
{{/SHELLTASK}}
<p>{{TASK_INSTRUCTIONS}}</p>
<p>
    If you have any questions about this task, please leave a comment in the TWB Community forum thread associated with this project:<br />
    <a href="{{COMMUNITY}}">{{COMMUNITY}}</a>
</p>
<p>
   Thank you for your work on this task and for your continued support!
</p>


{{>FOOTER}}
