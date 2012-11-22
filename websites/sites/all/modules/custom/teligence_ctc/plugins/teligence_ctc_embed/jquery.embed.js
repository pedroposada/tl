var ctcHtml = "";

$(document).ready(function(){
	
	if(ctcHtml == ""){
		ctcHtml = $("#teligence-ctc-form-wrapper").html();
	}
	
	var ctc_response = function(data){
		var result = Drupal.parseJson(data);
		$("#teligence-ctc-form-wrapper").fadeOut("fast", function(){
			$(this).html(result['content']);
			$(this).fadeIn("fast");
			$("#try-again").bind('click', tryagain);
		});
	}
	
	var tryagain = function(){
		$("#teligence-ctc-form-wrapper").fadeOut("fast", function(){
			$(this).html(ctcHtml);
			$(this).fadeIn("fast");
			$("#edit-submit").bind('click', ctcCall);
		});
	}
	
	var ctcCall = function(){
		
		//alert($(this).attr("id"));
		
		var ctc_url = $("#edit-embed-ctc-url").val();
		
		$("#teligence-ctc-form-wrapper").fadeOut("fast", function(){
			$(this).html('<img src="/sites/all/modules/teligence_ctc/ajax-loader.gif" />')
			$(this).fadeIn("fast");
		});
		
		var values = {	
				area_code: $('input[@name=area_code]').val(),
    			phone_number: $('input[@name=phone_number]').val(),
    			partnerID: $('input[@name=partnerID]').val(),
				Source: $('input[@name=Source]').val(),
				Keyword: $('input[@name=Keyword]').val(),
				Campaign: $('input[@name=Campaign]').val(),
				LandingPage: $('input[@name=LandingPage]').val(),
				atid: $('input[@name=atid]').val(),
				language: $('input[@name=language]').val(),
				brand: $('input[@name=brand]').val()
			}
		$.post(ctc_url, values, ctc_response);
		
		return false;
	}
	
	$("#edit-submit").bind('click', ctcCall);
});