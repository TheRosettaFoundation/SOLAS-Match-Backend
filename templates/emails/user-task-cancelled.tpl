<p>
    {{USERNAME}},
</p>
<p>
    You claimed a {{TASK_TYPE}} task for "{{TASK_TITLE}}" from {{SOURCE_LANGUAGE}} into {{TARGET_LANGUAGE}} with Translators without Borders.
</p>
{{#CLAIMED}}
<p>text only displayed for when user has claimed the task (but not yet in progress)</p>
{{/CLAIMED}}
{{#IN_PROGRESS}}
<p>text only displayed for when the task is in progress (i.e. the translation prerequisites are complete)</p>
{{/IN_PROGRESS}}
<p>
    If you have any questions about this task, please leave a comment in the TWB Community discussion thread associated with your project:<br />
    <a href="{{COMMUNITY}}">{{COMMUNITY}}</a>
</p>
<p>
   Thank you for your work on this task and for your continued support!
</p>

{{>FOOTER}}
