(function($) {
	
	// play recording wrapper function
	function hitPlay(playerId, pathToMedia) {
		$(playerId).jPlayer("clearMedia");
		$(playerId).jPlayer("setMedia", {
			mp3 : pathToMedia, // Defines the mp3 url
		}).jPlayer("play");
	}
	
	// get list of shouts 
	function reloadShoutAndList(newurl,minLeftValue){
		$.post(newurl,
			function(data){
				var result = $.parseJSON(data);
				$("#shoutsList").html(result['list']);
				$("#headlinetext").html(result['headlinetext']);
				$("#shouttext").html(result['shouttext']);
				$("#createdate").html(result['createdate']);
				$("#prevShoutLink").html(result['prevShoutLink']);
				$("#nextShoutLink").html(result['nextShoutLink']);
				$("#prevCatLink").html(result['prevCatLink']);
				$("#nextCatLink").html(result['nextCatLink']);
				$('#shoutsCategories ul a.active').removeClass('active');
				$("#" + result['categoryElementId']).addClass('active');
				animateCategorySlider(minLeftValue);
			}
		);
	}
	
	// animate categories slider
	function animateCategorySlider(minLeftValue){
		var catUlPos = $("#categoryList").position();
		var activeCenter = $("#categoryList .active").position().left + ($("#categoryList .active").width()/2);
		var delta1 = activeCenter - catUlPos.left;
		var delta2 = 280 - catUlPos.left;
		var moveUlTo = delta2 - delta1;
		
		// move ul categories container to point
		if( moveUlTo > 0){
			moveUlTo = 0;
		}
		if(moveUlTo < minLeftValue){
			moveUlTo = minLeftValue;
		}
		
		// detect browser
		if($.browser.msie && parseInt($.browser.version, 10) === 8 || $.browser.msie  && parseInt($.browser.version, 10) === 7){
			$("#categoryList").css("left", moveUlTo + "px"); 
		}else{
			$("#categoryList").stop().animate({left: moveUlTo},"fast"); 
		}
	}
	
	// when document is completely loaded
	$(document).ready(function() {
	
		var swfCustomPath = Drupal.settings.shoutwall.swfCustomPath;
		var shoutsFolderPath = Drupal.settings.shoutwall.shoutsFolderPath;
		var firstShout = Drupal.settings.shoutwall.firstShout;
		var loadShoutsByCategoryUrl = Drupal.settings.shoutwall.loadShoutsByCategoryUrl;
		var loadShoutByIdUrl = Drupal.settings.shoutwall.loadShoutByIdUrl;
		var getShoutAndListUrl = Drupal.settings.shoutwall.getShoutAndListUrl;
		
		// position category inside slider 
		var minLeft = $("#maskCategories").width() - ($("#categoryList li.last a").position().left + $("#categoryList li.last a").width());
		animateCategorySlider(minLeft);
		
		// set default id of first shout
		if($.param.fragment()){
			firstShout = $.param.fragment();
		}
		
		// instance jPlayer
		$("#audioPlayer").jPlayer({
			ready : function() {
				$(this).jPlayer("setMedia", {
					mp3 : shoutsFolderPath + "/" + firstShout // Defines the mp3 url
				});
			},
			swfPath : swfCustomPath,
			wmode: "window",
			// cssSelectorAncestor : "", // Remove the ancestor css selector clause
			// cssSelector : {
				// play : "#audioPlay", 
				// stop : "#audioStop",
				// pause : "#audioPause",
			// }
		});
	
		/**
		 * BBQ
		 */
		// Bind an event to window.onhashchange that, when the history state changes,
		// gets the url from the hash and displays either our cached content or fetches
		// new content to be displayed.
		$(window).bind('hashchange', function(e) {
			// Get the hash (fragment) as a string, with any leading # removed. Note that
			// in jQuery 1.4, you should use e.fragment instead of $.param.fragment().
			var url = $.param.fragment();
			
			// path to recording
			var path = shoutsFolderPath + "/" + url;
			
			// play recording only if url isn't empty
			url && hitPlay('#audioPlayer', path);
			
			// reload list and shout info
			var newurl = getShoutAndListUrl + "/" + url;
			url && reloadShoutAndList(newurl,minLeft);
			
		});
		// Since the event is only triggered when the hash changes, we need to trigger
		// the event now, to handle the hash the page may have loaded with.
		$(window).trigger('hashchange');
		
		// bind action to category click
		$("#shoutsCategories ul a").bind('click',function(){
			$('#shoutsCategories ul a.active').removeClass('active');
			$(this).addClass('active');
		});
		
		// move categories when click on nextCategory and prevCategory arrows
		// $("#prevCatLink").bind('click',function(){
			// animateCategorySlider();
		// })
		// $("#nextCatLink").bind('click',function(){
			// animateCategorySlider();
		// })
		
	});
	
})(jQuery);
