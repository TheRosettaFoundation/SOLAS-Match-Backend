<h3>Score Calculation Complete</h3>

{{#ERROR}}
    <p>An error occured: {{ERROR_MESSAGE}}</p>
{{/ERROR}}

{{#SCORE_SECT}}
    <p>Updating user {{USER_ID}} task {{TASK_ID}} score to {{SCORE}}</p>
{{/SCORE_SECT}}

<hr />

{{#TIMING}}
    <p>Finished processing. It took {{TIME}} to complete</p>
{{/TIMING}}
