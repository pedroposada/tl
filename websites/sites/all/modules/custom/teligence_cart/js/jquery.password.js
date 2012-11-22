$(document).ready(function(){
	if($("#edit-password")){
		$('<div id="short-password"></div>').insertAfter($("#edit-password"));
		$("#edit-password").keyup(function(){
			var strlen = $(this).val();
			if(strlen.length < 6){
				$("#short-password").text(Drupal.settings.teligence_cart_short_password);
			}else{
				$("#short-password").text("");
			}
		});
	}
});