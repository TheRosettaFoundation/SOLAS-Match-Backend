<p>Hello
{{#USER_HAS_NAME}}
    {{USERNAME}},
{{/USER_HAS_NAME}}
{{#NO_USER_NAME}}
    Hello,
{{/NO_USER_NAME}}
This is a summary of all tasks available for the Türkiye/Syria earthquake response in your language combinations.
Your support in translating these important resources will be highly welcome.
Please be mindful that these tasks are time sensitive, we ask you to claim them only if you are sure you will be able to deliver on time.
</p>
<p>
<strong>Please, do not work on the tasks until you have claimed them on the TWB Platform.
To claim a task, you just have to click on the blue heading, and then on the button “Claim task”.
After that, click on the button “Yes, I promise I will translate/revise this file”.
You can watch this <a href="https://drive.google.com/file/d/1E7t4BiFDkTi5r4orgteVzJy4QAiehiB3/view">2-minute tutorial</a>,
to learn how to claim a task.</strong>
</p>
<p>
Please note that TWB works with a community of volunteers and that these projects are pro-bono. Thank you for your contribution and for your continued support!
</p>
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
    <p>Added: <strong>{{CREATED_TIME}} UTC</strong></p>
    <p>Due by: <strong>{{DEADLINE_TIME}} UTC</strong></p>
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
