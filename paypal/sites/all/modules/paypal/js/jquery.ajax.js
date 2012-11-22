$(document).ready(function(){
	
	// redirect to resulting page
	var redirection = function(data){
		var result = Drupal.parseJson(data);
		window.location = result['URL'];
	}
	
	// POST values
	var values = {some: $(this).val()};
	
	$.post('/paypal/return/' + , values, redirection);
});