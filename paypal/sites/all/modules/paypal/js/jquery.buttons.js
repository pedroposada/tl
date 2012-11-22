var touched;
var t;
var disabler = function(){
    touched.css("display", "none");
    clearTimeout(t);
}

$(document).ready(function(){
	
	$("#paypal-loading").css("display", "none");
	
    $("input[@type=image]").click(function(){
    	$("#paypal-loading").css("display", "block");
    	$("<span>Processing...</span>").insertAfter($(this));
        touched = $(this);
        t = setTimeout(disabler, 1);
    });
});