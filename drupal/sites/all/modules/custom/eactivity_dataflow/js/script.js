(function($){Drupal.behaviors.widgetRefreshByAjax={attach:function(context){$("body").once("widget-refresh-by-ajax",function(){$("#gridstack-pane-views-to_do-block_1, #gridstack-pane-views-progress_tracker-block_1").on("click","a.refresh",function(ev){console.log("do not load link, perform ajax instead");var $refreshLink=$(this);$refreshLink.after('<div class="ajax-progress ajax-progress-throbber"><div class="throbber">&nbsp;</div> Refreshing...</div>');$.get("todo/refresh",function(){console.log("ajax complete, refresh the ctools forms to refresh the view");$refreshLink.parent().triggerHandler("RefreshView");$refreshLink.next("div.ajax-progress.ajax-progress-throbber").remove();$refreshLink.parent().find("div.view").first().children("div, ul").show()});return false})})}};$(window).load(function(){$("#gridstack-pane-views-to_do-block_1").find("div.view").first().children("div, ul").hide();$("#gridstack-pane-views-progress_tracker-block_1").find("div.view").first().children("div, ul").hide();$("#gridstack-pane-views-to_do-block_1").find("a.refresh").click();$("#gridstack-pane-views-progress_tracker-block_1").find("a.refresh").click()})})(jQuery);
//# sourceMappingURL=src/script.js.map