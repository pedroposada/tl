/*
 * trigger events for key combinations
 * see key numbers and code http://www.scottklarr.com/topic/126/how-to-create-ctrl-key-shortcuts-in-javascript/
 */
var isAlt = false;
var isAlte = false;
var isCtrl = false;

$(document).ready(function() {
	
	function enabled_save_button(){
		if(nontalk){
			$("#edit-next").removeAttr("disabled");
		}
		if(gender && language){
			$("#edit-next").removeAttr("disabled");
		}
	}
	
	$(this).keyup(function (e) {
		
		if(e.which == 18 || e.which == 17) isAlt=false;
		if(e.which == 18 ) isAlte=false;
		if(e.which == 17 ) isCtrl=false;
		
	}).keydown(function (e) {
		
		if(e.which == 18) isAlte=true;
		if(e.which == 17) isCtrl=true;
		if(isAlte == true && isCtrl == true) isAlt=true;
				
		/*
		 * ALT + M	Male	Gender 
		 */
		if(e.which == 77 && isAlt == true) {
			gender = true;
			enabled_save_button();
			$("#gender input:radio").each(function(){
				$(this).parent().removeClass("highlighted");
			});
			$("#edit-gender-M").attr('checked', true);
			$("#edit-gender-M").parent().addClass("highlighted");
		}
		/*
		 * ALT + F	Female	Gender  
		 */
		if(e.which == 70 && isAlt == true) {
			gender = true;
			enabled_save_button();
			$("#gender input:radio").each(function(){
				$(this).parent().removeClass("highlighted");
			});
			$("#edit-gender-F").attr('checked', true);
			$("#edit-gender-F").parent().addClass("highlighted");
		}
		/*
		 * ALT + A	Both	Gender  
		 */
		if(e.which == 65 && isAlt == true) {
			gender = true;
			enabled_save_button();
			$("#gender input:radio").each(function(){
				$(this).parent().removeClass("highlighted");
			});
			$("#edit-gender-B").attr('checked', true);
			$("#edit-gender-B").parent().addClass("highlighted");
		}
		/*
		 * ALT + O	Other	Gender  
		 */
		if(e.which == 79 && isAlt == true) {
			gender = true;
			enabled_save_button();
			$("#gender input:radio").each(function(){
				$(this).parent().removeClass("highlighted");
			});
			$("#edit-gender-U").attr('checked', true);
			$("#edit-gender-U").parent().addClass("highlighted");
		}
		/*
		 * ALT + N	English	Language  
		 */
		if(e.which == 78 && isAlt == true) {
			language = true;
			enabled_save_button();
			$("#language input:radio").each(function(){
				$(this).parent().removeClass("highlighted");
			});
			$("#edit-language-1").attr('checked', true);
			$("#edit-language-1").parent().addClass("highlighted");
		}
		/*
		 * ALT + H 	Spanish	Language  
		 */
		if(e.which == 72 && isAlt == true) {
			language = true;
			enabled_save_button();
			$("#language input:radio").each(function(){
				$(this).parent().removeClass("highlighted");
			});
			$("#edit-language-2").attr('checked', true);
			$("#edit-language-2").parent().addClass("highlighted");
		}
		/*
		 * ALT + T	Other	Language 
		 */
		if(e.which == 84 && isAlt == true) {
			language = true;
			enabled_save_button();
			$("#language input:radio").each(function(){
				$(this).parent().removeClass("highlighted");
			});
			$("#edit-language-0").attr('checked', true);
			$("#edit-language-0").parent().addClass("highlighted");
		}
		/*
		 * ALT + S	Silent	Attribute 
		 */
		if(e.which == 83 && isAlt == true) {	
			nontalk = true;
			enabled_save_button();
			$("#monitor-attributes input:radio").each(function(){
				$(this).parent().removeClass("highlighted");
				$(this).attr('checked', false);
			});
			$("#edit-attributes-no-talk-1").attr('checked', true);
			$("#edit-attributes-no-talk-1").parent().addClass("highlighted");
		}
		/*
		 * ALT + E	Intimate	Attribute 
		 */
		if(e.which == 69 && isAlt == true) {	
			nontalk = true;
			$("#monitor-attributes input:radio").each(function(){
				$(this).parent().removeClass("highlighted");
				$(this).attr('checked', false);
			});
			$("#edit-attributes-verbiage-intimate-content-16").attr('checked', true);
			$("#edit-attributes-verbiage-intimate-content-16").parent().addClass("highlighted");
			if(gender && language){
				// do nothing
			}else{
				$("#edit-next").attr("disabled","disabled");
				nontalk = false;
			}
		}
		/*
		 * ALT + U	Underage	Attribute 
		 */
		if(e.which == 85 && isAlt == true) {
			attribs = true;
			//enabled_save_button();
			$("#monitor-attributes input:radio").each(function(){
				$(this).parent().removeClass("highlighted");
				$(this).attr('checked', false);
			});
			$("#edit-attributes-verbiage-age-9").attr('checked', true);
			$("#edit-attributes-verbiage-age-9").parent().addClass("highlighted");
			if(gender && language){
				// do nothing
			}else{
				$("#edit-next").attr("disabled","disabled");
				nontalk = false;
			}
		}
		/*
		 * ALT + L	Prostitution	Attribute  
		 */
		if(e.which == 76 && isAlt == true) {
			attribs = true;
			//enabled_save_button();
			$("#monitor-attributes input:radio").each(function(){
				$(this).parent().removeClass("highlighted");
				$(this).attr('checked', false);
			});
			$("#edit-attributes-verbiage-prostitution-unacceptable-racism-10").attr('checked', true);
			$("#edit-attributes-verbiage-prostitution-unacceptable-racism-10").parent().addClass("highlighted");
			if(gender && language){
				// do nothing
			}else{
				$("#edit-next").attr("disabled","disabled");
				nontalk = false;
			}
		}
		/*
		 * ALT + R	Racism	Attribute  
		 */
		if(e.which == 82 && isAlt == true) {
			attribs = true;
			//enabled_save_button();
			$("#monitor-attributes input:radio").each(function(){
				$(this).parent().removeClass("highlighted");
				$(this).attr('checked', false);
			});
			$("#edit-attributes-verbiage-prostitution-unacceptable-racism-15").attr('checked', true);
			$("#edit-attributes-verbiage-prostitution-unacceptable-racism-15").parent().addClass("highlighted");
			if(gender && language){
				// do nothing
			}else{
				$("#edit-next").attr("disabled","disabled");
				nontalk = false;
			}
		}
		/*
		 * ALT + G	Negative/Unacceptable	Attribute  
		 */
		if(e.which == 71 && isAlt == true) {
			attribs = true;
			//enabled_save_button();
			$("#monitor-attributes input:radio").each(function(){
				$(this).parent().removeClass("highlighted");
				$(this).attr('checked', false);
			});
			$("#edit-attributes-verbiage-prostitution-unacceptable-racism-17").attr('checked', true);
			$("#edit-attributes-verbiage-prostitution-unacceptable-racism-17").parent().addClass("highlighted");
			if(gender && language){
				// do nothing
			}else{
				$("#edit-next").attr("disabled","disabled");
				nontalk = false;
			}
		}
		/*
		 * ALT + D	Drugs	Attribute  
		 */
		if(e.which == 68 && isAlt == true) {
			attribs = true;
			//enabled_save_button();
			$("#monitor-attributes input:radio").each(function(){
				$(this).parent().removeClass("highlighted");
				$(this).attr('checked', false);
			});
			$("#edit-attributes-verbiage-drugs-12").attr('checked', true);
			$("#edit-attributes-verbiage-drugs-12").parent().addClass("highlighted");
			if(gender && language){
				// do nothing
			}else{
				$("#edit-next").attr("disabled","disabled");
				nontalk = false;
			}
		}
		/*
		 * ALT + P	Personal	Attribute 
		 */
		if(e.which == 80 && isAlt == true) {
			attribs = true;
			//enabled_save_button();
			$("#monitor-attributes input:radio").each(function(){
				$(this).parent().removeClass("highlighted");
				$(this).attr('checked', false);
			});
			$("#edit-attributes-verbiage-personal-information-13").attr('checked', true);
			$("#edit-attributes-verbiage-personal-information-13").parent().addClass("highlighted");
			if(gender && language){
				// do nothing
			}else{
				$("#edit-next").attr("disabled","disabled");
				nontalk = false;
			}
		}
		/*
		 * ALT + I	Illegal/ Criminal	Attribute 
		 */
		if(e.which == 73 && isAlt == true) {
			attribs = true;
			//enabled_save_button();
			$("#monitor-attributes input:radio").each(function(){
				$(this).parent().removeClass("highlighted");
				$(this).attr('checked', false);
			});
			$("#edit-attributes-verbiage-criminal-hate-crimes-14").attr('checked', true);
			$("#edit-attributes-verbiage-criminal-hate-crimes-14").parent().addClass("highlighted");
			if(gender && language){
				// do nothing
			}else{
				$("#edit-next").attr("disabled","disabled");
				nontalk = false;
			}
		}
		/*
		 * ALT + Z	Clear Options	Attribute
		 */
		if(e.which == 90 && isAlt == true) {
			enabled_save_button();
			$("#bbm-agent-monitoring-form input:radio").clearForm();
			$("#edit-next").attr("disabled","disabled");
			nontalk = gender = language = attribs = false;
			$("#bbm-agent-monitoring-form input:radio").each(function(){
				$(this).parent().removeClass("highlighted");
			});
		}
	});
});
