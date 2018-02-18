
<p>Dear {{DISPLAY_NAME}},</p>

<p>
    On behalf of our partner organisations that have benefited from your work,
    I would like to thank you for your dedication and enthusiastic
    support in removing the price tag for access to information and knowledge across languages 
    for those who need it most.
</p>
<p>
    Below, you will find a record of your work on Kató Trommons. We hope that you found
    volunteering your skills rewarding and we look forward to continue working with you in future.
</p>
<p>
    Please do not hesitate to contact us with any queries or suggestions you may have.
</p>

<p>Kind Regards,</p>
<p>The Kató Trommons Team</p>

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
                <tr>
            {{/TASKS}}
        </tbody>
    </table>
{{/TASKS_AVAILABLE}}


{{>FOOTER}}
