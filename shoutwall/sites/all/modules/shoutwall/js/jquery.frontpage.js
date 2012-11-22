(function($) {
	
	// when document is completely loaded
	$(document).ready(function() {
		
		// bind action to tabs list on click
		$("#frontpageContentTabs ul a").bind('click',function(){
			$('#frontpageContentTabs ul a.active').removeClass('active');
			$(this).addClass('active');
			var tabContentId = $(this).attr('name');
			$('div.tabContent').removeClass('active');
			$('#' + tabContentId).addClass('active');
		});		
		
	});
	
})(jQuery);