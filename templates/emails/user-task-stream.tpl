
<head>


<style>

.claim-task:hover {
            background: linear-gradient(135deg, #0056b3, #143878);
        }
        .task-card:hover {
            transform: translateY(-10px);
            box-shadow: 0 8px 16px rgba(0, 0, 0, 0.2);
        }

</style>
</head>
<body>

<div style="width: 100%; max-width: 900px; margin: 0 auto; padding: 20px; 
 background-color: #FFFFFF;
            border-radius: 10px;
            box-shadow: 0 4px 8px rgba(0, 0, 0, 0.1);
            overflow: hidden;">
<div style="background-color: #9eabb8;color: #343A40;
            padding: 20px;
            text-align: center;">

<img style="margin: 10px;
            vertical-align: middle;max-width:100%; overflow:visible" src="https://clearglobal.org/wp-content/uploads/2021/05/CG_Logo_horizontal_primary_RGB.svg" alt="CLEAR Global Logo">

<img style="margin: 10px;
            vertical-align: middle;width:120px;" src="https://clearglobal.org/wp-content/uploads/2021/09/TWB_Logo_horizontal_primary_RGB.png" alt="TWB Logo">
<h1>New tasks available</h1>
</div>

<div style="width: 100%; max-width: 600px; margin: 0 auto; padding: 20px; color:#272b2e">

<div style="padding: 20px;
            text-align: center;
            font-size: 18px;
            color: #343A40;">
Hello {{USERNAME}},
</div>

<div style="padding: 0 20px;
            font-size: 16px;
            color: #576e82;
            text-align: center;">
            Here's a summary of available tasks in the system. Ready to make a difference?
        </div>


<p>

{{#TASK_SECT}}
<div style="background-color: #f8f9fa; /* Light grey background */
border: 2px solid #e8991c; /* Frame color */
border-radius: 15px;
box-shadow: 0 4px 8px rgba(0, 0, 0, 0.1);
padding: 20px;
margin-bottom: 20px;
position: relative;
overflow: hidden;
transition: transform 0.3s ease, box-shadow 0.3s ease" class="task-card">

<h3>{{TASK_TYPE}} - {{TASK_TITLE}}</h3>
<p>{{WORD_COUNT}} words - {{SOURCE_LANGUAGE}} -> {{TARGET_LANGUAGE}}</p>
<p>Due By: {{DEADLINE_TIME}} UTC</p>
                <p>{{PROJECT_NAME}}</p>
                <a href={{TASK_VIEW}}  style="display: block;
            margin: 20px auto;
            padding: 10px 20px;
            background: linear-gradient(135deg, #143878, #0056b3); 
            color: #FFFFFF;
            text-decoration: none;
            border-radius: 25px;
            font-size: 18px;
            font-weight: bold;
            transition: background 0.3s ease;
            width: 100%;
            box-sizing: border-box;
            text-align: center; 
        " class="claim-task">View Task</a>
        <a href="#" style="display: block;
            margin: 20px auto;
            padding: 10px 20px;
            background: linear-gradient(135deg, #e8991c, #a74116); /* Translators without Borders Yellow Gradient */
            color: #FFFFFF;
            text-decoration: none;
            border-radius: 25px;
            font-size: 18px;
            font-weight: bold;
            transition: background 0.3s ease;
            width: 100%;
            box-sizing: border-box;
            text-align: center; /* Center the text */">View More Tasks</a>  
        <div style="position: absolute;
            
        bottom: -50px;
        right: -50px;
        width: 200px;
        height: 200px;
        background-color: #6e6edc; /* Clear Tech Purple */
        border-radius: 50%;
        opacity: 0.2;
        z-index: -1;
        content:''
        ">
        </div>    


</div>
{{/TASK_SECT}}

<div style="padding: 20px;
            background-color: #f8f9fa; /* Light grey background */
            border: 2px solid #e8991c; /* Frame color */
            border-radius: 15px;
            box-shadow: 0 4px 8px rgba(0, 0, 0, 0.1);
            margin-bottom: 20px;
            position: relative;
            overflow: hidden;
            transition: transform 0.3s ease, box-shadow 0.3s ease;" >
<h3 style="text-align: center;
            margin-bottom: 10px;">Important Information</h3>
<ul style=" list-style: disc;
            padding-left: 20px;
            margin: 0;
            text-align: left;">
    <li style="margin-bottom: 10px;
            font-size: 16px;
            color: #343A40;"><strong>How to Claim a Task?</strong> <a href="#" style=" color: #e8991c;
            text-decoration: underline;">[Link to the tutorial Video]</a></li>
    <li style="margin-bottom: 10px;
            font-size: 16px;
            color: #343A40;"><strong>Quality Assurance:</strong> Ensure your work meets our high standards by following the guidelines and running Phrase QA checks. More details here. <a href="#" style="color: #e8991c;
            text-decoration: underline;">[Link to Guidelines]</a></li>
</ul>

            
</div>
<div style="padding: 20px;
background-color: #f8f9fa; /* Light grey background */
border: 2px solid #e8991c; /* Frame color */
border-radius: 15px;
box-shadow: 0 4px 8px rgba(0, 0, 0, 0.1);
margin-bottom: 20px;
position: relative;
overflow: hidden;
transition: transform 0.3s ease, box-shadow 0.3s ease;">
            <h3 style="text-align: center;
            margin-bottom: 10px;">Additional Resources</h3>
            <ul style=" list-style: disc;
            padding-left: 20px;
            margin: 0;
            text-align: left;">
                <li style="margin-bottom: 10px;
                font-size: 16px;
                color: #343A40;"><strong>New to TWB?</strong> Click here <a style=" color: #e8991c;
                text-decoration: underline;" href="#">[Link to the Translator's Toolkit]</a></li>
                <li style="margin-bottom: 10px;
                font-size: 16px;
                color: #343A40;"><strong>Have questions?</strong> Check the task thread on our community forum <a href="#" style=" color: #e8991c;
                text-decoration: underline;">[Link to the task thread on the TWB Community Forum]</a>.</li>
                <li style="margin-bottom: 10px;
                font-size: 16px;
                color: #343A40;"><strong>Want to expand your knowledge?</strong> Check out our TWB Learning Center <a href="#" style=" color: #e8991c;
                text-decoration: underline;">[Link to the TWB LC]</a>.</li>
                <li style="margin-bottom: 10px;
                font-size: 16px;
                color: #343A40;"><strong>Unsubscribe?</strong> Visit your Profile Page <a href="#" style=" color: #e8991c;
                text-decoration: underline;">[Link to the linguist's profile page]</a> and update your settings.</li>
            </ul>
        </div>
</div>
        <div style=" background-color: #143878; /* Core Blue */
            color: #FFFFFF;
            padding: 20px;
            text-align: center;">
            <p>Thank you for your invaluable contribution to our mission!</p>
            <p>The TWB Team</p>
            <p>Follow Us: <a style=" color: #e8991c;
                text-decoration: underline;" href="https://twitter.com/CLEARGlobalOrg">X</a> | <a style=" color: #e8991c;
                text-decoration: underline;"href="https://www.linkedin.com/company/clear-global/">LinkedIn</a></p>
            <p>Visit Our Website: <a style=" color: #e8991c;
                text-decoration: underline;" href="https://www.twb.org">TWB</a> | <a href="https://www.clearglobal.org" style=" color: #e8991c;
                text-decoration: underline;">CLEAR Global</a></p>
        </div>

</div>
</body>
