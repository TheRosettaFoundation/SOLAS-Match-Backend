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
    <p>Word Count: <strong>{{WORD_COUNT}}</strong></p>
    <p>Added: <strong>{{CREATED_TIME}}</strong></p>
    <p>Due by: <strong>{{DEADLINE_TIME}}</strong></p>
    {{#DESCRIPTION_SECT}}
    <p><strong>Project Description</strong>: <i>{{PROJECT_DESCRIPTION}}</i></p>
    <p><strong>Project Impact</strong>: <i>{{PROJECT_IMPACT}}</i></p>
    {{/DESCRIPTION_SECT}}
    {{#TAGS_SECT}}
        <p>
            Tags:
            {{#TAGS_LIST}}
                <a href="{{TAG_DETAILS}}"><i>{{TAG_LABEL}}</i></a>
            {{/TAGS_LIST}}
        </p>
    {{/TAGS_SECT}}
    {{#PARTOF_SECT}}
    <p>
        Part of: <a href="{{PROJECT_VIEW}}">{{PROJECT_TITLE}}</a>
        for <a href="{{ORG_VIEW}}">{{ORG_NAME}}</a>
    </p>
    {{/PARTOF_SECT}}
    {{#IMAGE_SECT}}
        <img src="{{PROJECT_IMAGE}}" width="300" />
    {{/IMAGE_SECT}}
    <p style="margin-bottom:40px;"/>
{{/TASK_SECT}}

New to TWB? Have a look at our <a href="https://community.translatorswb.org/t/welcome-pack-for-kato-translators/3138">Translator's Toolkit</a> to find out how to get started with us.


{{>FOOTER}}
