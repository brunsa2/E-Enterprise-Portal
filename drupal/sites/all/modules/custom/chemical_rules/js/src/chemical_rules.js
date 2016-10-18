function showElementOutOfMany($wrapper_to_show, $common_selector) {
  $common_selector.hide();
  $wrapper_to_show.show();
  resizeModal()
}

function resizeModal() {
  jQuery('#chemical-rules-modal').dialog({
    position: { 'my': 'center', 'at': 'center' }
  });
  if(jQuery('.chemical-rules-modal').css('top').replace('px', '') < 1){
    jQuery('.chemical-rules-modal').css('top', 0)
  }
}

function checkValues(previous, current, cIndex, keys) {
  var previousKeys = [];
  if(typeof previous[keys[cIndex]] == 'object'){
    previousKeys = Object.keys(previous[keys[cIndex]])
  }

  if ((previousKeys.indexOf('Value') > -1 && previous[keys[cIndex]].Value == "")) {
    delete previous[keys[cIndex]];
  }
  else if (['object'].indexOf(typeof previous[keys[cIndex]]) > -1) {
    previous[keys[cIndex]] = previousKeys.reduce(checkValues, previous[keys[cIndex]])
    if (Object.keys(previous[keys[cIndex]]).length == 0) {
      delete previous[keys[cIndex]];
    }
  }
  return previous
}

var sampleData = function() {};

/**
 * Clear form inputs and hide warning messages
 */
function resetCRForm() {
  var $form = $('#cr-search');
  //$form.find('input[type=text]').val('');
  $form.val('');
}

function populate_substance_modal(chemical_rules_response_json) {
  var $body = $('body');

  if(chemical_rules_response_json.data != null && chemical_rules_response_json.error == false){

    // popluate our modal
    $body.find('#user-chemical-name').text(chemical_rules_response_json.data.Substance.EPAChemicalRegistryName);

    var $list = $body.find('.cr-rules-regs_lists')
    $(chemical_rules_response_json.data.LawsRegs).each(function(index){
      $list.append('<li><a href="'+this.source+'" target="_blank">'+this.name+'</a></li>');
    })

    $('#chemical-rules-modal').dialog("open")
  }
  else {
    //@todo Add error msg for then there is bad data
  }



}

(function($) {
  var $body = $('body'),
      $cr_tabs = $('#cr-tabs').tabs(),
      sampleSetIndex = 0,
      num_chem_faves = 0,
      num_rules_faves = 0,
      $cr_empty = $('.cr-tabs_favorites_empty'),
      $cr_avail = $('.cr-tabs_favorites_available');
  
  //@TODO Add logic to count number of Chemical Favorites and Law / Rule Favorites
  //num_chem_faves = ...;
  //num_rules_faves = ...;
  
  // If no favorites exist, show Search tab
  if (num_chem_faves === 0 && num_rules_faves === 0) {
    $cr_empty.toggleClass('hidden', false);
    $cr_avail.toggleClass('hidden', true);
  }
  else {
    $cr_empty.toggleClass('hidden', false);
    $cr_avail.toggleClass('hidden', true);
    //@TODO Print Favorite Chemicals
    //
    //@TODO Print Favorite Laws/Regs    
    //count
    //ul
  }

  // Initialize and open dialog
  $('#chemical-rules-modal')
    .html(Drupal.settings.chemical_rules.modal)
    .dialog({
      title: 'chemicalNameOrNum',
      modal: true,
      width: "auto",
      position: { 'my': 'left top', 'at': 'left top' },
      dialogClass: 'chemical-rules-modal',
      draggable: false,
      autoOpen: false,
      create: function(event, ui) {

      },
      close: function(event, ui) {
        resetCRForm();
        //$('#chemical-rules-loading-wrapper').hide();
        //$(this).dialog('destroy');
      }
    });

  $body.on('click', '#cr-search-chems-btn', function(ev) {

    var chem_search_form_data = $('#chem_search_form').serialize();

    $.ajax({
      url: 'chemical_rules/form_submission',
      method: 'POST',
      data: chem_search_form_data,
      success: populate_substance_modal
    })

    //ev.preventDefault();
    //ev.stopPropagation();
    var chemicalNameOrNum = $body.find('#cr-search_input').val();
    if ($body.find('#chemical-error').length > 0) {
      $body.find('#chemical-error').remove();
      $body.find('#cr-search_input').removeAttr('aria-describedby');
    }
  
    //@TODO - Samuel's logic to handle chemical regex and lookup
    
    //////
    
    var is_valid_chemical = true;
    if (!is_valid_chemical) {
      error = true;
      var error_message = '<p class="has-error" id="chemical-error">No results were found for <b>' + chemicalNameOrNum + '</b>.  Please try another variation.</p>';
      $(error_message).insertBefore('#cr-search_description');
      $body.find('#cr-search_input').attr('aria-describedby', 'chemical-error');
    }  
    
    // Simulate the loading results block switching to results block
    // @TODO - Change this once Ajax / JSON success call returned - 
    else {
      var toc = $("#cr-modal-toc-icons").toc({ 
        selectors: "h2",
        container: "#chemical-rules-modal",
        'itemClass': function(i, heading, $heading, prefix) { // custom function for item class
          return $heading[0].tagName.toLowerCase();
        } 
      });
      // POST input field value to lookup service
      // Render out 

      resizeModal();
    }
  });    

  /**
   * Close Listener on Chemical Rules Modal
   * -  Remove Previous Results ?
   * -  Cancel Pending Form submission
   */
  $('#chemical-rules-modal').on('dialogclose', function() {
    var $chemical_loading = $('#chemical-rules-loading-wrapper');
    var $all_wrappers = $('.chemical-rules-modal-wrapper');

    showElementOutOfMany($chemical_loading, $all_wrappers);
    resizeModal();
  });

})(jQuery);
