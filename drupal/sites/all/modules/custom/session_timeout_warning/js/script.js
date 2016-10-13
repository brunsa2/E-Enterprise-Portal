var promptAt;var logoutAt;var isPrompted=false;var isLoggedOut=false;(function($){Drupal.behaviors.sessionTimeoutPrompt={attach:function(context){$("body").once("session-timeout-prompt",function(){var $sessionTimeoutModal=$('<div id="session-timeout-modal"></div>');$("body").append($sessionTimeoutModal);promptAt=Drupal.settings.promptAt;logoutAt=Drupal.settings.logoutAt;setInterval(function(){var now=Math.floor(Date.now()/1e3);var userId=Drupal.settings.currentUser||0;if(!isLoggedOut&&userId!=0){if(now>logoutAt){instantLogout();isLoggedOut=true}else if(!isPrompted&&now>promptAt){$sessionTimeoutModal.html('<div>Due to inactivity, your session will expire in <span class="min-remaining">5 minutes</span>. Please click Continue Session to continue.</div><div class="actions"><button class="logout button">Logout</button><button class="renew button">Continue Session</button></div>').dialog({dialogClass:"session-timeout-modal-content",title:"Session Timeout Warning",resizable:false,closeText:"Close",modal:true});isPrompted=true}else if(isPrompted){var minutesRemaining=Math.ceil((logoutAt-now)/60)+" minute";if(minutesRemaining!="1 minute"){minutesRemaining+="s"}$sessionTimeoutModal.find("span.min-remaining").html(minutesRemaining)}}},2e3);var instantLogout=function(){$sessionTimeoutModal.find(".actions").html("Logging Out...");$.get("eebridge-auth/logout").always(function(){window.location.href=Drupal.settings.basePath+"bridge-landing"})};$sessionTimeoutModal.on("click",".logout",instantLogout);$sessionTimeoutModal.on("click",".renew",function(){var now=Math.floor(Date.now()/1e3);promptAt=now+60*15;logoutAt=now+60*20;isPrompted=false;$.get(Drupal.settings.basePath+"renew-session");$sessionTimeoutModal.dialog("close");return false})})}}})(jQuery);
//# sourceMappingURL=src/script.js.map