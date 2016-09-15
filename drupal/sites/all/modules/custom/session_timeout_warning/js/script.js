var promptAt;var logoutAt;var isPrompted=false;var isLoggedOut=false;(function($){Drupal.behaviors.sessionTimeoutPrompt={attach:function(context){$("body").once("session-timeout-prompt",function(){$("body").append('<div id="session-timeout-modal"></div>');promptAt=Drupal.settings.promptAt;logoutAt=Drupal.settings.logoutAt;setInterval(function(){var now=Math.floor(Date.now()/1e3);var userId=Drupal.settings.currentUser||0;var $sessionTimeoutModal=$("#session-timeout-modal");if(!isLoggedOut&&userId!=0){if(now>logoutAt){instantLogout()}else if(!isPrompted&&now>promptAt){$sessionTimeoutModal.html('<div>Due to inactivity, your session will expire in <span class="min-remaining">5 minutes</span>. Please click Continue Session to continue.</div><div><button class="logout button">Logout</button><button class="renew button">Continue Session</button></div>').dialog({dialogClass:"session-timeout-modal-content",title:"Session Timeout Warning",resizable:false,closeText:"Close",modal:true});isPrompted=true}else if(isPrompted){var minutesRemaining=Math.ceil((logoutAt-now)/60)+" minute";if(minutesRemaining!=1){minutesRemaining+="s"}$sessionTimeoutModal.find("span.min-remaining").html(minutesRemaining)}}},2e3);var instantLogout=function(){$.get(Drupal.settings.basePath+"instant-logout");$("#session-timeout-modal").html('<div>You have been timed out.</div><div><a href="'+Drupal.settings.basePath+'bridge-landing">Login</a></div>').dialog({dialogClass:"session-timeout-modal-content",title:"Session Timeout",resizable:false,closeText:"Close",modal:true});isLoggedOut=true;return false};$("#session-timeout-modal").on("click",".logout",instantLogout);$("#session-timeout-modal").on("click",".renew",function(){var now=Math.floor(Date.now()/1e3);promptAt=now+60*15;logoutAt=now+60*20;isPrompted=false;$.get(Drupal.settings.basePath+"renew-session");$("#session-timeout-modal").html("<div>Your session has been renewed.</div>").dialog({dialogClass:"session-timeout-modal-content",title:"Session Renewed",resizable:false,closeText:"Close",modal:true});return false})})}}})(jQuery);
//# sourceMappingURL=src/script.js.map