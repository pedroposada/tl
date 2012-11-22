$(document).ready(function(){
	
	var showStates = function(data){
		var result = Drupal.parseJson(data);
		$("#edit-State").html(result['content']);
	}
	
	$("#edit-Country").change(function(){
	
		var values = {country: $(this).val()};
		$.post('/cart/state', values, showStates);
		
	});
	
});