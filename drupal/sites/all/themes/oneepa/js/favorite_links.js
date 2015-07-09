(function ($) {

$(document).ready(function(){
	
	///SCRIPT FOR FAVORITE  LINKS BOX
	//collect urls already favored
	var favorite_urls;
	var url_id_mapping;
	var id_label_mapping;
	
	function load_links(index) {
		$('#load_more').hide();
		$.ajax({
			url:'/load_links/' + index,
			method: 'POST',
			success: function(data) {
				var data = $.parseJSON(data);
				if (data.url_data != 'false') {
					favorite_urls = data.urls;
					url_id_mapping = data.url_mapping;
					id_label_mapping = data.label_mapping;
					processPageAnchors();
				}
			}
		});	
	}
	// initial load links
	load_links();
	
	
	
	
	///////Script for Attached button functionality to links
	
	
	function createFavoriteButton(url, text_title) {
		if ($.inArray(url, favorite_urls) === -1) {
	 		var favorite_button = "<button id='" + url_id_mapping[url] + "favorite_link' class='btn  btn-success add_link favorite_hover' style='display:none'>Add</button>";	
		}
		else {
			var favorite_button = "<button id='" + url_id_mapping[url] + "favorite_link' class='btn btn-danger remove_link favorite_hover' style='display:none'>Remove</button>";	
		}
	 return favorite_button;
	} 
	
	function processPageAnchors() {
		// process anchor tags
		$('#main-content a').each(function () {
		if ($(this).text().length > 0 && $(this).attr('href') != '#') {
			var url = $(this).attr('href');
			var title = $(this).text();
			var favorite_button = createFavoriteButton(url, title);
			if ($('#' + url_id_mapping[url] + 'favorite_link').length > 0) {
				$('#' + url_id_mapping[url] + 'favorite_link').html(favorite_button);
			}
			else {
				$(this).after(favorite_button);
			}
			$(this).qtip({ // Grab some elements to apply the tooltip to
			    content: {
			        text: $(this).next('button')
			    },
				 hide: {
	                fixed: true,
	                delay: 300
	            	}
				});
			}
		});
		// process img links
		$('#main-content img').each(function () {
		if ($(this).attr('href') != '#' && $(this).attr('href')!= '') {
			var url = $(this).attr('href');
			var title = $(this).attr('alt');
			var favorite_button = createFavoriteButton(url, title);
			if ($('#' + url_id_mapping[url] + 'favorite_link').length > 0) {
				$('#' + url_id_mapping[url] + 'favorite_link').html(favorite_button);
			}
			else {
				$(this).after(favorite_button);
			}
			$(this).qtip({ // Grab some elements to apply the tooltip to
			    content: {
			        text: $(this).next('button')
			    },
				 hide: {
	                fixed: true,
	                delay: 300
	            	}
				});
			}
		});
	}
	
	
	
	// $('.favorite_hover').mouseover(function() {
	// 	$(this).show();	
	// });
	// $('.favorite_hover:not(.btn-default)').mouseout(function() {
	// 	$(this).hide();	
	// });
	
	$('body').on('click', '.add_link', function(){
		var string_array = $(this).attr('id').split('|');
		var url = string_array[0];
		var label = string_array[1];
		processFavoriteLink($(this), 'add', url, label );
	});
	
	$('body').on('click', '.remove_link', function() {
		var string_array = $(this).attr('id').split('|');
		var url = string_array[0];
		var label = string_array[1];
		processFavoriteLink($(this), 'remove', url, label );
	});
	
	// function removeRow(url) {
	// 	$.ajax({
	// 		url: '/user_add_favorite_link/' + url + '/remove'
	// 		});
	// };
	
	function processFavoriteLink(button, action, url, label) {
		url = encodeURIComponent(url);
		$.ajax({
			url: '/process_favorite_link',
			type: 'POST',
			async: false,
			data: {url: url, action: action, title: label},
			beforeSend: function() {
				button.removeClass("btn-success").removeClass("btn-danger");
				button.addClass("btn-default");
				button.text("Loading");
			},
			success: function(data) {
				// console.log(data);
				// console.log($.parseJSON(data));
				if (data == 'success') {
					button.unbind("click");
					if (action == 'add') {
						button.removeClass('add_link').removeClass('btn-default').removeClass('btn-success');
						button.text('Remove');
						button.addClass('remove_link btn-danger');
					}
					else{
						button.removeClass('remove_link').removeClass('btn-default').removeClass('btn-danger');
						button.text('Add');
						button.addClass('add_link btn-success');
					}
				}
			},
			failure: function() {
				alert('something went wrong');
			}
		});
	}
	///////////////////////////////////////////
	});

})(jQuery);