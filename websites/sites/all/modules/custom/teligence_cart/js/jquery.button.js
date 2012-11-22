var touched;
var t;
var disabler = function(){
    touched.attr("disabled", "disabled");
	//touched.attr("value", "Processing...");
    if(Drupal.settings.teligence_cart.button_processing[0]){
    	touched.attr("value", Drupal.settings.teligence_cart.button_processing[0]);
    }else{
    	touched.attr("value", "Processing...");
    }
    
    clearTimeout(t);
}

$(document).ready(function(){
    $("input[@type=submit]").mouseup(function(){
        $(this).siblings("input[@type=submit]").hide();
        touched = $(this);
        t = setTimeout(disabler, 1);
    });
    
    $("form").keypress(function(event) {
    	  if (event.keyCode == '13') {
    		  $("input[@type=submit]:first").siblings("input[@type=submit]").hide();
    	      touched = $("input[@type=submit]:first");
    	      t = setTimeout(disabler, 1);
    	  }
    });
	
    if($('#teligence-cart-add-time-form input:text')){
    	$('#teligence-cart-add-time-form input:text').each(function(){
    		if($(this).val() == ''){
    			$(this).attr("disabled","disabled");
    		}
    		if($(this).hasClass('error')){
    			$(this).removeAttr("disabled");
    		}
    	});
    	$('#teligence-cart-add-time-form input:text').blur(function(){
    		if($(this).val() == ''){
    			$(this).attr("disabled","disabled");
    		}
    	});
    	$('#teligence-cart-add-time-form input:text').focus(function(){
    		$(this).removeAttr("disabled");
    	});
    }
    
	$('.package-table tr').click(function(event) {
		if($(':radio', this)){
			$(':radio', this).trigger('click');
			if($(':text', this)){
				$(':text', this).trigger('focus');
			}
		}
		
		if (event.target.type !== 'radio') {
		  //$(':radio', this).trigger('click').trigger('focus');
		}
	});
});