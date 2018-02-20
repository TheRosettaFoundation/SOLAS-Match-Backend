<p>
    {{#USER_HAS_NAME}}
        {{USERNAME}},
    {{/USER_HAS_NAME}}
    {{#NO_USER_NAME}}
        Hello,
    {{/NO_USER_NAME}}
</p>

<p>
    You have claimed a "{{TASK_TYPE}}" task for "{{TASK_TITLE}}" from {{SOURCE_LANGUAGE}} into {{TARGET_LANGUAGE}} on {{SITE_NAME}}.
</p>
<p>
    Thanks for helping to volunteer.
</p>
<p>
    You can translate or revise using Kató TM or alternatively edit the file you downloaded on your local PC.
</p>
<p>
    As soon as you have processed the file on Kató TM (and all segments are marked as translated or approved (revising)),
    please copy it "from Kató TM to Kató Trommons" using the following page:<br />
    {{TASK_PAGE}}
</p>
<p>
    Or if you edited on your local PC, upload the output file on the following page:<br />
    {{TASK_PAGE}}
</p>
<p> 
    You can then request a reference letter on your Profile page. 
</p>

<p>
    Sincerely,<br />
    The {{SITE_NAME}} Team
</p>


{{>FOOTER}}
