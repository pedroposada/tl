$(document).ready(function() {	
// show calendar
	//$("#edit-fromdate", "#edit-todate").calendar();
	$(function() {
	    $('#edit-fromdate').datepicker({
	    	duration: '',
	        showTime: true,
	        constrainInput: false
	     });
	    $('#edit-todate').datepicker({
	    	duration: '',
	        showTime: true,
	        constrainInput: false
	     });
	});
	
	$('.field-suffix').click(function(){
		$(this).prev().focus();
	});
});