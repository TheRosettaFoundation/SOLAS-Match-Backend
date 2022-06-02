
<p>Dear {{DISPLAY_NAME}},</p>

<p>
    We would like to thank you for your dedication and enthusiastic support of our mission
    to increase access to information and knowledge across all languages.
</p>
<p>
    Below, you will find a record of your work on TWB Platform. We hope that you found
    your volunteering experience rewarding, and we thank you for your continued support.
</p>
<p>
    If you have any questions or suggestions, you can get in touch with us at
    <a href="mailto:translators@translatorswithoutborders.org">
    translators@translatorswithoutborders.org</a>
</p>

<p>Warm regards,</p>
<p>The TWB Community Management Team</p>

<h3>Tasks You Contributed To</h3>

{{#NO_TASKS}}
    <p>Sorry, we were unable to find any tasks that you contributed to in our system</p>
{{/NO_TASKS}}

{{#TASKS_AVAILABLE}}
    <table border="1">
        <thead>
            <th>Task Title</th>
            <th>Organisation</th>
            <th>Task Type</th>
            <th>Source</th>
            <th>Target</th>
            <th>Word Count</th>
            <th>Created Date</th>
        </thead>
        <tbody>
            {{#TASKS}}
                <tr>
                    <td>{{TASK_TITLE}}</td>
                    <td>{{ORG_NAME}}</td>
                    <td>{{TASK_TYPE}}</td>
                    <td>{{SOURCE}}</td>
                    <td>{{TARGET}}</td>
                    <td>{{WORD_COUNT}}</td>
                    <td>{{CREATED_TIME}}</td>
                </tr>
            {{/TASKS}}
        </tbody>
    </table>
{{/TASKS_AVAILABLE}}


{{>FOOTER}}
