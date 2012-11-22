// clear form function
$.fn.clearForm = function() {
	return this.each(function() {
		var type = this.type;
		var tag = this.tagName.toLowerCase();
		if (tag == 'form')
			return $(':input', this).clearForm();
		if (type == 'text' || type == 'password' || tag == 'textarea')
			this.value = '';
		else if (type == 'checkbox' || type == 'radio')
			this.checked = false;
		else if (tag == 'select')
			this.selectedIndex = -1;
	});
};

var nontalk, gender, language, attribs  = false;

$(document).ready(function() {

	function enabled_save_button(){
		if(nontalk){
			$("#edit-next").removeAttr("disabled");
		}
		if(gender && language){
			$("#edit-next").removeAttr("disabled");
		}
	}
	
	$("#edit-next").attr("disabled","disabled");
	
	// clear forms
	$("#edit-deselect").click(function() {
		$("#bbm-agent-monitoring-form input:radio").clearForm();
		$("#edit-next").attr("disabled","disabled");
		nontalk = gender = language = attribs = false;
		$("#bbm-agent-monitoring-form input:radio").each(function(){
			$(this).parent().removeClass("highlighted");
		});
		return false;
	});
	
	
	/**
	 * toggle higlighted states
	 */
	$("#monitor-attributes input:radio").change(function(){
		attribs = true;
		if($(this).attr('id') !== "edit-attributes-no-talk-1"){
			if(gender && language){
				// do nothing
			}else{
				$("#edit-next").attr("disabled","disabled");
				nontalk = false;
			}
		}

		var selectedElementId = $(this).attr('id');		
		$("#monitor-attributes input:radio").each(function(){
			if($(this).attr('id') == selectedElementId){
				$(this).parent().addClass("highlighted");
			}else{
				this.checked = false;
				$(this).parent().removeClass("highlighted");
			}
		});
	});
	
	/**
	 * toggle higlighted states
	 */
	$("#gender input:radio").change(function(){
		gender = true;
		enabled_save_button();
		
		var selectedElementId = $(this).attr('id');
		$("#gender input:radio").each(function(){
			if($(this).attr('id') == selectedElementId){
				$(this).parent().addClass("highlighted");
			}else{
				$(this).parent().removeClass("highlighted");
			}
		});
	});
	
	/**
	 * toggle higlighted states
	 */
	$("#language input:radio").change(function(){
		language = true;
		enabled_save_button();
		
		var selectedElementId = $(this).attr('id');
		$("#language input:radio").each(function(){
			if($(this).attr('id') == selectedElementId){
				$(this).parent().addClass("highlighted");
			}else{
				$(this).parent().removeClass("highlighted");
			}
		});
	});
	$("#edit-attributes-no-talk-1").click(function(){
		nontalk = true;
		enabled_save_button();
	});
	
	
	if($('#edit-show-notes')){
		$('#edit-show-notes').click(function(){
			var url = $(this).attr('alt');
			window.open(url);
			return false;
		});
	}
	
});