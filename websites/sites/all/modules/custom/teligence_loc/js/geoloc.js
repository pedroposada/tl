$(document).ready(function(){
	function geo_success(p) {
		// alert("Found you at latitude " + p.coords.latitude +", longitude " + p.coords.longitude);
		// $.get(, function(data){
		// alert("data");
		// });
		$.get("/loc/mobile/" + p.coords.latitude +"/" + p.coords.longitude, function(data){
			// alert(data);
			window.location.reload();
		});
	}
	
	function geo_error() {
		alert("Could not find your location at the moment.");
	}
	
	if (geo_position_js.init()) {
		geo_position_js.getCurrentPosition(geo_success, geo_error);
	}
});

