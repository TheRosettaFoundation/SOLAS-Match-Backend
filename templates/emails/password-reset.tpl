<p>
    {{#USER_HAS_NAME}}
        {{USERNAME}},
    {{/USER_HAS_NAME}}
    {{#NO_USER_NAME}}
        Hello,
    {{/NO_USER_NAME}}
</p>

<p>
    You have requested a password reset for your SOLAS Match account. You can reset
    your password by copying the link below and pasting it into the address bar of
    your web browser. If you did not request a password please ignore this email.
</p>
<p>{{URL}}</p>
