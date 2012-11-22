$(document).ready(function(){
	
	var loadBalanceElementId = Drupal.settings.loadBalanceElementId[0];
	var loadBalanceUrl = Drupal.settings.loadBalanceUrl[0];
	
	// alert(loadBalanceElementId);
	// alert(loadBalanceUrl);
	
	$("#" + loadBalanceElementId).load(loadBalanceUrl);
	// $.get(loadBalanceUrl,function(data){
		// ("#" + loadBalanceElementId).html(data);
	// });
});