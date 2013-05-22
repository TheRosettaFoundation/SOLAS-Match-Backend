<p>
    {{#USER_HAS_NAME}}
        {{USERNAME}},
    {{/USER_HAS_NAME}}
    {{#NO_USER_NAME}}
        Hello,
    {{/NO_USER_NAME}}
</p>

<p>
    The task "{{TASK_TITLE}}" has passed its deadline. As you have claimed this
    task you must be sure you have uploaded an output by now.
</p>

<p>
    From,<br />
    The {{SITE_NAME}} Team
</p>

