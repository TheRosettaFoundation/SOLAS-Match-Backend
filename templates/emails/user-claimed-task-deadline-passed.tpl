<p>
    {{#USER_HAS_NAME}}
        {{USERNAME}},
    {{/USER_HAS_NAME}}
    {{#NO_USER_NAME}}
        Hello,
    {{/NO_USER_NAME}}
</p>

<p>
    The task "{{TASK_TITLE}}" has passed its deadline. As the task deadline has passed, please ensure to upload your output file. 
    If you have any questions about the deadline, please contact <a href="info@trommons.org"> info@trommons.org. </a>
</p>

<p>
    From,<br />
    The {{SITE_NAME}} Team
</p>


{{>FOOTER}}
