<p>
    {{#USER_HAS_NAME}}
        {{USERNAME}},
    {{/USER_HAS_NAME}}
    {{#NO_USER_NAME}}
        Hello,
    {{/NO_USER_NAME}}
</p>
<p>
You started the process of creating an account on Kató Platform, but you have not completed your profile. Please Complete this at:<br />
<a href="{{PROFILE_URL}}">{{PROFILE_URL}}</a>
</p>
<p>
If the profile is not completed, the account will be deleted in 12 hours.
</p>
