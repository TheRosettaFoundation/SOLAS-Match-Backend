<p>
    Dear {{USERNAME}},
</p>
<p>
    We had to cancel the the {{TASK_TYPE}} task for "{{TASK_TITLE}}" from {{SOURCE_LANGUAGE}} into {{TARGET_LANGUAGE}} due to change in plans. We are sorry for the inconvenience.
</p>
{{#CLAIMED}}
<p>
If you have any questions about this task, please leave a comment in the TWB Community discussion thread associated with your project: <a href="{{COMMUNITY}}">{{COMMUNITY}}</a>
</p>
{{/CLAIMED}}
{{#IN_PROGRESS}}
<p>
All the words you already completed for this task will count towards your recognition points. If you have any questions about this task, please leave a comment in the TWB Community discussion thread associated with your project: <a href="{{COMMUNITY}}">{{COMMUNITY}}</a>
</p>
{{/IN_PROGRESS}}
<p>
    We thank you for your interest and hope you'll find other tasks to claim soon.
</p>

{{>FOOTER}}
