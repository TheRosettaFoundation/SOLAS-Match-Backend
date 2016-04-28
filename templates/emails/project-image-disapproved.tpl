<p>
    {{#USER_HAS_NAME}}
        {{USERNAME}},
    {{/USER_HAS_NAME}}
    {{#NO_USER_NAME}}
        Hello,
    {{/NO_USER_NAME}}
</p>

<p>
    The administrators have decided not to publish the image associated with the project <a href="{{PROJECT_VIEW}}">{{PROJECT_TITLE}}</a>. 
    Review your image and resubmit a different image or contact <a href="mailto:info@trommons.org">info@trommons.org</a> for more information.
</p>

<p>
    From,<br />
    The {{SITE_NAME}} Team
</p>
