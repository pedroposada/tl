var touched;
var t;
var disabler = function(){
    touched.attr("disabled", "disabled");
	touched.attr("value", "Processing...");
    clearTimeout(t);
}

$(document).ready(function(){
    $("input[@type=submit]").mouseup(function(){
        $(this).siblings("input[@type=submit]").hide();
        touched = $(this);
        
        if($(this).attr("id") == "edit-previous"){
        	//history.back();
        	//return false;
        	//alert($(this).attr("id"));
        }else{
        	t = setTimeout(disabler, 1);
        	$("#edit-previous").hide();
        }
        
    });
});