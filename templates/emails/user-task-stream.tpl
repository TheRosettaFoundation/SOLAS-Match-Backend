<h3>Tasks available on {{SITE_NAME}}</h3>
<br />
<hr />

{{#TASK_SECT}}
    <h2>
        <a href="{{TASK_VIEW}}">{{TASK_TITLE}}</a>
    </h2>
    <p>Type: {{TASK_TYPE}}</p>
    <p>From: <strong>{{SOURCE_LANGUAGE}}</strong></p>
    <p>To: <strong>{{TARGET_LANGUAGE}}</strong></p>
    {{#TAGS_SECT}}
        <p>
            Tags:
            {{#TAGS_LIST}}
                <a href="{{TAG_DETAILS}}">{{TAG_LABEL}}</a>
            {{/TAGS_LIST}}
        </p>
    {{/TAGS_SECT}}
    <p>Word Count: <strong>{{WORD_COUNT}}</strong></p>
    <p>Added: <strong>{{CREATED_TIME}}</strong></p>
    <p>Due by: <strong>{{DEADLINE_TIME}}</strong></p>
    <p>
        Part of: <a href="{{PROJECT_VIEW}}">{{PROJECT_TITLE}}</a>
        for <a href="{{ORG_VIEW}}">{{ORG_NAME}}</a>
    </p>

    <p style="margin-bottom:40px;"/>
{{/TASK_SECT}}


{{>FOOTER}}
