<p>
    You have successfully submitted the "{{TASK_TYPE}}" task for "{{TASK_TITLE}}"
    from {{SOURCE_LANGUAGE}} into {{TARGET_LANGUAGE}}.
</p>
<p>
We would really appreciate it if you could provide some brief constructive feedback on the translation task {{TASK_TITLE}} you revised.
This will help fellow volunteers improve.
</p>
<p>
Please submit your feedback at this link: {LINK TO REVIEW PAGE}.
============
LIKE
uploadUrl += "task/" + QString::number(task->id()) + "/id";
dict.SetValue("TASK_UPLOAD", uploadUrl.toStdString());
So we need to upgrade this to have a link to the review e.g.: https://kato.translatorswb.org/task/133081/review/
============
</p>
<p>
You can find our guidelines on leaving constructive feedback here:<br />
<a href="https://community.translatorswb.org/t/what-is-translation-quality-for-translators-without-borders/10295">What is Translation Quality for TWB</a><br />
<a href="https://community.translatorswb.org/t/what-is-the-harmonized-dqf-mqm-error-typology/10827">The error typology you can follow</a><br />
<a href="https://community.translatorswb.org/t/giving-constructive-and-respectful-feedback/10825">Giving constructive and respectful feedback</a>
</p>
<p>
    After your submission is reviewed, you may receive feedback from the TWB team or the partner organization.
</p>
<p>
    If you have any questions about this task, please leave a comment in the Kató Community discussion thread associated with your project:<br />
    <a href="{{COMMUNITY}}">{{COMMUNITY}}</a>
</p>

<p>
    Thank you for your continued support!
</p>


{{>FOOTER}}
