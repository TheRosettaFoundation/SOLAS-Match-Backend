<p>
    {{#USER_HAS_NAME}}
        {{USERNAME}},
    {{/USER_HAS_NAME}}
    {{#NO_USER_NAME}}
        Hello,
    {{/NO_USER_NAME}}
</p>

<p>
    The administrators have approved the image uploaded with the project <a href="{{PROJECT_VIEW}}">{{PROJECT_TITLE}}</a>. The image will
    soon appear in the task stream.
</p>

<p>
    From,<br />
    The {{SITE_NAME}} Team
</p>


{{>FOOTER}}
