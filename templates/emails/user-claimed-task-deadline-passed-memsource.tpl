<p>
    {{#USER_HAS_NAME}}
        {{USERNAME}},
    {{/USER_HAS_NAME}}
    {{#NO_USER_NAME}}
        Hello,
    {{/NO_USER_NAME}}
</p>
<p>
   Thank you for claiming the {{TASK_TYPE}} task for "{{TASK_TITLE}}" from {{SOURCE_LANGUAGE}} into {{TARGET_LANGUAGE}}. The deadline for this task expired on {{DEADLINE}}.
</p>
{{#TRANSLATION}}
<p>
    Please translate this task in Memsource, our CAT tool:<br />
    <a href="{{MATECAT}}">{{MATECAT}}</a>
</p>
<p>
    When all segments are translated, click "Complete".
</p>
{{/TRANSLATION}}
{{#REVISING}}
<p>
    Please revise this task in Memsource, our CAT tool:<br />
    <a href="{{MATECAT}}">{{MATECAT}}</a>
</p>
<p>
    When all segments are revised, click "Complete".
</p>
{{/REVISING}}
<p>
    Please complete the task as soon as possible. If you need a deadline extension or are unable to deliver this work,
    please leave a comment in the Kató Community discussion thread associated with your project:<br />
    <a href="{{COMMUNITY}}">{{COMMUNITY}}</a><br />
    Please note that in some cases we are unable to extend task deadlines and would have to reassign the task to another translator.
    For more details please see <a href="https://community.translatorswb.org/t/deadlines-on-kato-platform/248">Deadlines on Kató Platform</a>
</p>


{{>FOOTER}}
