<p>
    {{#USER_HAS_NAME}}
        {{USERNAME}},
    {{/USER_HAS_NAME}}
    {{#NO_USER_NAME}}
        Hello,
    {{/NO_USER_NAME}}
</p>
<p>
    You claimed a {{TASK_TYPE}} task for "{{TASK_TITLE}}" from {{SOURCE_LANGUAGE}} into {{TARGET_LANGUAGE}} with Translators without Borders.
</p>
{{#TRANSLATION}}
<p>
    Please translate this task in Phrase TMS, our CAT tool:<br />
    <a href="{{MATECAT}}">Translation URL</a><br />
</p>
<p>
    When all segments are translated, click "Complete".
</p>
{{/TRANSLATION}}
{{#TRANSLATION_WAIT}}
<p>
    Please translate this task in Phrase TMS, our CAT tool:<br />
    <a href="{{MATECAT}}">Translation URL</a><br />
</p>
<p>
    When all segments are translated, click "Complete".
</p>
{{/TRANSLATION_WAIT}}
{{#REVISING}}
<p>
    Please revise this task in Phrase TMS, our CAT tool:<br />
    <a href="{{MATECAT}}">Revision URL</a><br />
</p>
<p>
   When all segments are revised, click "Complete".
</p>
{{/REVISING}}
{{#REVISING_WAIT}}
<p>
    <strong>You will receive an email notification when the task is ready for you to revise.</strong> The email will include a link to the revision task in Phrase TMS, our CAT tool.
</p>
{{/REVISING_WAIT}}
{{#APPROVAL}}
<p>
    Please proofread this task in Phrase TMS, our CAT tool:<br />
    <a href="{{MATECAT}}">Proofreading and Approval URL</a><br />
</p>
<p>
   When all segments are proofread, click "Complete".
</p>
{{/APPROVAL}}
{{#APPROVAL_WAIT}}
<p>
    <strong>You will receive an email notification when the task is ready for you to proofread.</strong> The email will include a link to the proofreading and approval task in Phrase TMS, our CAT tool.
</p>
{{/APPROVAL_WAIT}}
<p>
    If you have any questions about this task, please leave a comment in the TWB Community discussion thread associated with your project:<br />
    <a href="{{COMMUNITY}}">{{COMMUNITY}}</a>
</p>
<p>
   Thank you for your work on this task and for your continued support!
</p>


{{>FOOTER}}
