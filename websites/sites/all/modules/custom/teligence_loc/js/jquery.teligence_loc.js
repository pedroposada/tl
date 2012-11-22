
$(document).ready(function(){
	
	var tollFreeAccessNumber = Drupal.settings.teligence_loc.widgets.tollFreeAccessNumber[0];
	var locvals = new Array();
	
	// make one ajax call to the localization module
	var locGet = $.get('/loc/locvals', function(data){
		// locvals = $.parseJSON(data);
		locvals = Drupal.parseJson(data);
		// alert(locvals['City']);
		// city name
		$('span.locCity').html(locvals['City']);
	
		// local access number
		$('span.locPhone').html(locvals['Ani']);
	
		// region name
		$('span.locRegion').html(locvals['Region']);
		
		// country name
		$('span.locCountry').html(locvals['Country']);
	
		// market id
		$('span.locMarketId').html(locvals['MarketId']);
	
		// flavor
		$('span.locFlavor').html(locvals['Flavor']);
	})
	// .error(function(){
		// locvals['Ani'] = tollFreeAccessNumber;
		// locvals['City'] = 'Local';
		// locvals['Region'] = 'Local';
		// locvals['Country'] = 'Canada';
		// locvals['Flavor'] = 'DEFAULT';
	// });
	
	
	
});
