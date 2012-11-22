$(document).ready(function(){
	
	var ctcResponse = function(data){
		var result = Drupal.parseJson(data);
		$("#edit-form-name").val(result['form_name']);
		$("#edit-step1").val(result['step1']);
		$("#edit-step2success").val(result['step2_success']);
		$("#edit-step2failure").val(result['step2_failure']);
	}
	
	var ctcCall = function(){
		var values = {	
			form_id: $('input[@name=selectform]').val(),
		}
		$.post(ctc_url, values, ctcResponse);
	}
	
	$("#edit-selectform").bind('change', ctcCall);
});