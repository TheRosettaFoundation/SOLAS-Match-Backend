<p>
    {{#USER_HAS_NAME}}
        {{USERNAME}},
    {{/USER_HAS_NAME}}
    {{#NO_USER_NAME}}
        Hello,
    {{/NO_USER_NAME}}
</p>

<p>
    A task that you are following on {{SITE_NAME}} has changed its status.
    The "{{TASK_TYPE}}" task for "{{TASK_TITLE}}" from {{SOURCE_LANGUAGE}}
     into {{TARGET_LANGUAGE}} has been claimed by {{TRANSLATOR_NAME}}. 
    You can visit the translator's public profile 
    <a href="{{USER_PROFILE_URL}}">here</a>. You will be informed when 
    a translation becomes available.
</p>
<p>
    From,
    <br />
    The {{SITE_NAME}} Team
</p>


{{>FOOTER}}
