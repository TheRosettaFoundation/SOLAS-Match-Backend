<p>
    {{USERNAME}},
</p>
{{#REVISING}}
<p>
    A task on {{SITE_NAME}} has changed its status. The translator has completed the "{{TASK_TYPE}}" task for "{{TASK_TITLE}}"
    from {{SOURCE_LANGUAGE}} into {{TARGET_LANGUAGE}}.
</p>
<p>
    Please revise this task in Phrase TMS, our CAT tool:<br />
    <a href="{{MATECAT_REVISION}}">Revision URL</a>
</p>
<p>
   When all segments are revised, click "Complete".
</p>
{{/REVISING}}
{{#APPROVAL}}
<p>
    A task on {{SITE_NAME}} has changed its status. The revisor has completed the "{{TASK_TYPE}}" task for "{{TASK_TITLE}}"
    from {{SOURCE_LANGUAGE}} into {{TARGET_LANGUAGE}}.
</p>
<p>
    Please proofread this task in Phrase TMS, our CAT tool:<br />
    <a href="{{MATECAT_REVISION}}">Proofreading and Approval URL</a>
</p>
<p>
   When all segments are proofread, click "Complete".
</p>
{{/APPROVAL}}
<p>
    If you have any questions about this task, please leave a comment in the TWB Community forum thread associated with this project:<br />
    <a href="{{COMMUNITY}}">{{COMMUNITY}}</a>
</p>
<p>
   Thank you for your work on this task and for your continued support!
</p>

{{>FOOTER}}
