<p>
    {{USERNAME}},
</p>


{{#TRACKING_USER}}
    <p>
        The volunteer, {{CLAIMANT_NAME}}, has provided feedback on a task you are tracking.
    </p>
{{/TRACKING_USER}}
    
{{#ORG_ADMIN}}
    <p>
        The volunteer, {{CLAIMANT_NAME}}, has provided feedback for a task uploaded by your organisation, {{ORG_NAME}}.
        No other members of the organisation were tracking the task so it got sent to you.
    </p>
{{/ORG_ADMIN}}

<p>
    Feedback:<br />
    {{FEEDBACK}}
</p>

<p>
    Sincerely,
    The {{SITE_NAME}} Team
</p>
