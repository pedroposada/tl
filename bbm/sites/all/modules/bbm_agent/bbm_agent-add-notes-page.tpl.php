<div>
	<?php print $form ?>
</div>


<script type="text/javascript">
<!--
	//loads notes into textarea if any
	$('#edit-notes').attr({value: $('#edit-call-notes').val()});
	
	var touched;
	var t;
	var disabler = function(){
    	touched.attr("disabled", "disabled");
		touched.attr("value", "Loading... Please wait.");
    	clearTimeout(t);
	}
	var values = {
	    	CallNoteText: $('input[@name=notes]').val(),
	    	command: $('input[@name=command]').val(),
	    	RecordingType: $('input[@name=RecordingType]').val(),
	    	HubId: $('input[@name=HubId]').val(),
	    	Ani: $('input[@name=Ani]').val(),
	    	BrandId: $('input[@name=BrandId]').val(),
	    	AgentId: $('input[@name=AgentId]').val(),
	   	};
	$("#edit-save").attr("disabled", "disabled");
    $("#edit-save").mouseup(function(){
        $(this).siblings("input[@type=submit]").hide();
        touched = $(this);
        t = setTimeout(disabler, 1);
    });
    $("#edit-save").click(function(){
    	//$.post("/bbm/add-notes-save", values, saveNote);
    	var callnotes = $('#edit-notes').val();
    	$('#edit-call-notes').attr({value: callnotes});
    	//alert(callnotes);
    	tb_remove();
		return false;
    });
    
    $("#edit-notes").keypress(function(event){
	  if($(this).val())
	  {
		  $("#edit-save").removeAttr("disabled");
	  }
	  else
	  {
		  $("#edit-save").attr("disabled", "disabled");
	  }
    });

	// ajax call
    var saveNote = function(data){
        var result = Drupal.parseJson(data);
        //$("#edit-notes-wrapper").fadeOut("fast", function(){
			//$(this).html(result['content']);
			//$(this).fadeIn("fast");
		//});
		//$("#edit-notes-wrapper").html(result['content']);
    }
//-->
</script>