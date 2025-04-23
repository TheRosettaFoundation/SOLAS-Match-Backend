<div style="margin-top: 20px; padding: 20px ; font-family: 'Halcom', 'Helvetica Neue', Arial, sans-serif; background-color: #e7eaed;">
  <div style="width: 100%; max-width: 600px; margin: 20px auto; padding: 0;">
    <div style="background-color: #FFFFFF; border-radius: 10px; box-shadow: 0 4px 8px rgba(0, 0, 0, 0.1); overflow: hidden; padding: 20px;">
      
      <!-- Logo -->
      <div style="text-align: center; margin-bottom: 20px;">
        <img style="max-width: 250px; width: 80%; height: auto;" src="https://elearn.translatorswb.org/pluginfile.php/1/core_admin/logo/0x200/1733915613/merged-logos-main.png" alt="CLEAR Global Logo">
      </div>
      
      <!-- Header -->
      <div style="background-color: #ffffff; color: #343A40; padding: 15px; text-align: center;">
        <h1 style="color: #343A40; font-size: 24px; margin: 0;">New tasks available</h1>
        <hr style="border: 0; height: 1px; background-image: linear-gradient(to right, rgba(0, 0, 0, 0), rgba(0, 0, 0, 0.1), rgba(0, 0, 0, 0)); margin: 15px 0;">
      </div>
      
      <!-- Main Content -->
      <div style="padding: 0 15px; color:#344b5e;">
        
        <div style=" font-size: 18px; color: #576e82; margin-bottom: 15px;">
          Hello {{USERNAME}},
        </div>
        
        <div style="font-size: 16px; color: #576e82; margin-bottom: 20px;">
          Here's a summary of available tasks in the system. Ready to make a difference?
        </div>
        
        <p style="margin: 15px 0; color: #576e82; font-size:14px; ">
        These are volunteer tasks. Only claim them if you’re sure you can complete them. Please read all the task details first.
        </p>
         <!-- Important Information Section -->
         <div style="padding: 15px; background-color: #f8f9fa; border: 2px solid #e8991c; border-radius: 15px; box-shadow: 0 4px 8px rgba(0, 0, 0, 0.1); margin-bottom: 20px; position: relative; overflow: hidden;">
         <h3 style="text-align: center; margin: 0 0 10px 0; font-size: 18px;">Important Information</h3>
         <ul style="list-style: disc; padding-left: 20px; margin: 0; text-align: left;">
           <li style="margin-bottom: 10px; font-size: 14px; color: #343A40;">
             <strong><a href="https://drive.google.com/file/d/1E7t4BiFDkTi5r4orgteVzJy4QAiehiB3/view" style="color: #e8991c; text-decoration: none;" target="_blank">How to Claim a Task?</a></strong>
           </li>
           <li style="margin-bottom: 10px; font-size: 14px; color: #343A40;">
           Quality Assurance: Ensure your work meets our high standards by following the guidelines and running Phrase QA checks. <a href="https://community.translatorswb.org/t/post-editing-machine-translation-tips-and-best-practice/60046" target="_blank" style="color: #e8991c; text-decoration: underline;">More details here</a>
           </li>
           <li style="margin-bottom: 10px; font-size: 14px; color: #343A40;">
           Tasks can be claimed quickly, so they might no longer be available when you check them.
           </li>
         </ul>
       </div>
        
        <!-- Task Section (repeated for each task) -->
        {{#TASK_SECT}}
        <div style="background-color: #f8f9fa; border: 2px solid #e8991c; border-radius: 15px; box-shadow: 0 4px 8px rgba(0, 0, 0, 0.1); padding: 15px; margin-bottom: 20px; position: relative; overflow: hidden;">
          
          <h3 style="font-size: 18px; color: #343A40; text-align: center; margin-top: 0;">{{TASK_TYPE}} - {{TASK_TITLE}}</h3>
          
          <p style="margin: 8px 0; font-size: 14px;">
            <span style="color:#143878; font-weight:bold;">{{WORD_COUNT}} words</span> - in 
            <span style="color:#143878; font-weight:bold;">{{SOURCE_LANGUAGE}}</span> → 
            <span style="color:#143878; font-weight:bold;">{{TARGET_LANGUAGE}}</span>
          </p>
          
          <p style="margin: 8px 0; font-size: 14px;">
          <span style="color:#143878; font-weight:bold;">Due By: </span> {{DEADLINE_TIME}} UTC
          </p>
          <p> <span> Deliver by {{DESIRED_DEADLINE}} or earlier .You'll receive an email once you can start working on the task.</span></p>
         
          {{#PARTOF_SECT}}
          <p style="margin: 8px 0; font-size: 14px;">
          <span style="color:#143878; font-weight:bold;"> Project:</span> {{PROJECT_TITLE}}
          </p>
          {{/PARTOF_SECT}}
          
          <a href="{{TASK_VIEW}}" style="display: block; margin: 15px auto; padding: 10px; background: linear-gradient(135deg, #143878, #0056b3); color: #FFFFFF; text-decoration: none; border-radius: 25px; font-size: 16px; font-weight: bold; width: 100%; box-sizing: border-box; text-align: center;">View Task</a>
        </div>
        {{/TASK_SECT}}
        
        <!-- View More Tasks Button -->
        <a href="https://twbplatform.org/" target="_blank" style="display: block; padding: 15px; margin: 20px auto; background: linear-gradient(135deg, #e8991c, #a74116); color: #FFFFFF; text-decoration: none; border-radius: 25px; font-size: 16px; font-weight: bold; width: 100%; box-sizing: border-box; text-align: center;">View More Tasks</a>
        
       
        
        <!-- Additional Resources Section -->
        <div style="padding: 15px; background-color: #f8f9fa; border: 2px solid #e8991c; border-radius: 15px; box-shadow: 0 4px 8px rgba(0, 0, 0, 0.1); margin-bottom: 20px; position: relative; overflow: hidden;">
          <h3 style="text-align: center; margin: 0 0 10px 0; font-size: 18px;">Additional Resources</h3>
          <ul style="list-style: disc; padding-left: 20px; margin: 0; text-align: left;">
            <li style="margin-bottom: 10px; font-size: 14px; color: #343A40;">
              <strong>New to TWB?</strong> <a style="color: #e8991c; text-decoration: underline;" href="https://community.translatorswb.org/t/welcome-pack-for-kato-translators/3138" target="_blank">Click here</a>
            </li>
            <li style="margin-bottom: 10px; font-size: 14px; color: #343A40;">
              <strong>Have questions?</strong> <a href="https://community.translatorswb.org/latest" style="color: #e8991c; text-decoration: underline;" target="_blank">his is how you can ask questions about the task you claimed! </a>
            </li>
            <li style="margin-bottom: 10px; font-size: 14px; color: #343A40;">
              <strong>Want to expand your knowledge?</strong> <a href="https://elearn.translatorswb.org/auth/saml2/login.php?wants&idp=bd3eb3e6241260ee537b9a55145d852d&passive=off" style="color: #e8991c; text-decoration: underline;" target="_blank">Check our TWB Learning Center</a>
            </li>
            <li style="margin-bottom: 10px; font-size: 14px; color: #343A40;">
              <strong>Unsubscribe?</strong> <a href="{{CLAIMANT_ID}}" style="color: #e8991c; text-decoration: underline;" target="_blank">Visit your Profile Page</a>
            </li>
          </ul>
        </div>
        
        <!-- Footer -->
        <div style="background-color: #143878; color: #FFFFFF; padding: 15px; text-align: center; border-radius: 10px;">
          <p style="margin: 5px 0; font-size: 14px;">Thank you for your invaluable contribution to our mission!</p>
          <p style="margin: 5px 0; font-size: 14px;">The TWB Team</p>
          <p style="margin: 5px 0; font-size: 14px;">
            Follow Us: 
            <a style="color: #e8991c; text-decoration: underline;" href="https://twitter.com/CLEARGlobalOrg" target="_blank">X</a> | 
            <a style="color: #e8991c; text-decoration: underline;" href="https://www.linkedin.com/company/clear-global/" target="_blank">LinkedIn</a>
          </p>
          <p style="margin: 5px 0; font-size: 14px;">
            Visit Our Website: 
            <a style="color: #e8991c; text-decoration: underline;" href="https://translatorswithoutborders.org/" target="_blank">TWB</a> | 
            <a style="color: #e8991c; text-decoration: underline;" href="https://www.clearglobal.org" target="_blank">CLEAR Global</a>
          </p>
        </div>
        
      </div>
    </div>
  </div>
</div>