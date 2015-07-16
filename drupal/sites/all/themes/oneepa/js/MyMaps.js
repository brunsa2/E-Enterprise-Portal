(function($) {


  $(function() {

    var jcarousel = $('.jcarousel').jcarousel();


    jcarousel
      .on('jcarousel:reload jcarousel:create', function() {
        var carousel = $(this),
          width = carousel.innerWidth();

        //add rudimentary responsiveness
        if (width >= 1100) {
          width = (width / 5) - 4;
        } else if (width >= 850) {
          width = (width / 4) - 4;
        } else if (width >= 600) {
          width = (width / 3) - 4;
        } else if (width >= 350) {
          width = (width / 2) - 4;
        }

        carousel.jcarousel('items').css('width', Math.ceil(width) + 'px');

        //need to add event listeners after items have been added to the DOM, not on page load
        /*
        still testing - another ticket
        $(".thumb a").on("click", function(e) {
          e.preventDefault();
          var iframe = $('<iframe frameborder="0" marginwidth="0" marginheight="0" allowfullscreen></iframe>');
          var dialog = $("<div></div>").append(iframe).appendTo("body").dialog({
            autoOpen: true,
            modal: true,
      resizable: true,
      width: "100%",
            height: "100%",
            close: function() {
              iframe.attr("src", "");
            }
          });

          var src = $(this).attr("href");
          var title = $(this).attr("title");
          var width = '100%';
          var height = '100%';
          iframe.attr({
            width: +width,
            height: +height,
            src: src
          });
          dialog.dialog("option", "title", title).dialog("open");
        });
      */

      })
      .jcarousel({
        //could use circular here
        wrap: ''
      });

    $('.jcarousel-control-prev')
      .on('jcarouselcontrol:active', function() {
        $(this).removeClass('inactive');
      })
      .on('jcarouselcontrol:inactive', function() {
        $(this).addClass('inactive');
      })
      .jcarouselControl({
        target: '-=1'
      });

    $('.jcarousel-control-next')
      .on('jcarouselcontrol:active', function() {
        $(this).removeClass('inactive');
      })
      .on('jcarouselcontrol:inactive', function() {
        $(this).addClass('inactive');
      })
      .jcarouselControl({
        target: '+=1'
      });


    api_call();


    //create the thumbnail gallery from the API query results
    function setupGallery(data) {
      var html = '<ul class="thumb">';
      var numGoodResults = 0;
      var thumbnailNum = 0;
      //generate each thumbnail and only load it if non-default thumbnail image and a good hyperlink
      $.each(shuffle(data.results), function() {
        if (this.thumbnail != 'thumbnail/ago_downloaded.png' && this.thumbnail !== null && this.url.indexOf('http') > -1) {
          thumbnailNum += 1
          numGoodResults += 1
          var thumbnailURL = "https://epa.maps.arcgis.com/sharing/rest/content/items/" + this.id + "/info/" + this.thumbnail;
          //Descriptions can contain or not contain HTML markup, to let JQuery's .text() work, we just add the p tags to all descriptions
          //and all tags are remove with .text(), including descriptions which has no HTML markup which would normally throw an error
          var desc = "<p>" + this.description + "</p>"
          var hyperlinkURL = this.url;
          html += '<li>';
          html += '<a class="" href="' + hyperlinkURL + '" title="' + this.title + '" target="_blank">';
          html += '<img class="thumbnailImg" src="' + thumbnailURL + '" alt="' + this.title + '" title="' + this.title + '" aria-describedby="thumbnail-desc-' + thumbnailNum + '"/></a>';
          html += '<div class="mapAppTitle ellipsis" title="' + this.title + '">' + this.title + '</div>';
          //the description element can contain HTML markup so use .text to un-format the string
          html += '<div class="mapAppDesc ellipsis" id="thumbnail-desc-' + thumbnailNum + '" title="' + $(desc).text() + '">' + $(desc).text() + '</div>';
          html += '</li>';
        }
      });
      html += '</ul>';

      jcarousel
        .html(html);

      jcarousel
        .jcarousel('reload');

      $(".ellipsis").dotdotdot({
        watch: "window"
      });
      $(".ellipsis").trigger("update.dot");
      //Update DOM with the number of displayed results/thumbnails
      $("#numThumbnails").prepend(numGoodResults.toString() + ' Maps  - ');



    };


    //query the EPA GPO REST API for publicly shared web mapping applications
    function api_call(successCallback) {
      $.ajax({
        type: 'GET',
        url: 'https://epa.maps.arcgis.com/sharing/rest/search',
        async: true,
        //hardcoded string for EPA  GPO (AGOL) query - hardcoded query for empty string (wildcard) - later to implement tag search or similar for filtering based on dynamic criteria
        data: {
          q: ' orgid:cJ9YHowT8TU7DUyn orgid:cJ9YHowT8TU7DUyn (type:"Web Mapping Application" OR type:"Mobile Application" OR type:"Application" OR type:"Desktop Application Template" OR type:"Desktop Application" OR type:"Operation View") -type:"Code Attachment" -type:"Featured Items" -type:"Symbol Set" -type:"Color Set" -type:"Windows Viewer Add In" -type:"Windows Viewer Configuration" -type:"Code Attachment" -type:"Featured Items" -type:"Symbol Set" -type:"Color Set" -type:"Windows Viewer Add In" -type:"Windows Viewer Configuration"',
          f: 'json',
          num: '100'
        },
        success: function(data, status, xhr) {
          var resultJson = JSON.parse(data);
          setupGallery(resultJson);
        }
      }).fail(function(xhr, status) {
        if (status == "error") {
          console.log("Error in API request.");
          return "Sorry but there was an error: " + xhr.status + " " + xhr.statusText;
        }
      });

    }

    //Fisher-Yates shuffle just to randomize thumbnail order,
    //Makes it less boring on page relaod until we implement tag filtering, recommendation engine, etc.
    function shuffle(array) {
      var currentIndex = array.length,
        temporaryValue, randomIndex;
      while (0 !== currentIndex) {
        randomIndex = Math.floor(Math.random() * currentIndex);
        currentIndex -= 1;
        temporaryValue = array[currentIndex];
        array[currentIndex] = array[randomIndex];
        array[randomIndex] = temporaryValue;
      }
      return array;
    }

    //better beyboard accessibility, allow keyboard left and right arrows to navigate gallery
    $(document).on('keyup', function(e) {
      var key = e.which || e.keyChar || e.keyCode;
      if (key == 37) {
        $('.jcarousel').jcarousel('scroll', '-=1');
      } else if (key == 39) {
        $('.jcarousel').jcarousel('scroll', '+=1');
      }
    });



  });
})(jQuery);