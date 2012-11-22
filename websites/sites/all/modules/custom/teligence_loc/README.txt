This module provides an object that contains localization values as follows:

MarketId		EMS Market ID
Country			USA or Canada
Region	 		Region abbreviation
City	 		EMS Market Name (City); will default to 'Local'
Ani	 			Local number (999-999-9999); will default to toll free number

The Obejct can be straight from the $_SESSION as follows:

$city = $_SESSION['localization']->City;

Each value can be loaded as follows:

$_SESSION['localization']->MarketId;
$_SESSION['localization']->Country;
$_SESSION['localization']->City;
$_SESSION['localization']->Region;
$_SESSION['localization']->Ani;
$_COOKIE['flavor']


More info here:
http://wiki/doku.php?id=ep:nbi:200827:technical:getlocalaccessnumberbylonglat



AJAX TOKEN REPLACEMENT
----------------------
In order to allow pages to be cached and also have localization values
change dynamically, ajax handler was used. 

Ajax handler is located at /loc/locvals
This handler returns a json object with all localization values mentioned above.

Usage example inside a page:

	<span class="locCity">&nbsp;</span>

The contents of this span will be replaced with the City name or Local
if not city names was available.

The rest of the values can be accessed as follows:

	<span class="locRegion">&nbsp;</span>
	<span class="locPhone">&nbsp;</span>
	<span class="locCountry">&nbsp;</span>
	<span class="locMarketId">&nbsp;</span>
	<span class="locFlavor">&nbsp;</span>
 
Code snippet used in LLK home page to replace first section of a sentence.
In this code snippet you can see how ajaxComplete is used to evaluate 
if the City is not Local.

	<script>
	$(document).ready(function(){
		$("#notInCity").ajaxComplete(function(){
			if($("#bigCityName").html() != "Local"){
				$("#notInCity").html("Not in " + $(this).html() + "?")
			}
		});
	});
	</script>
	<div class="locEnterAreaCode"><span id="notInCity">&nbsp;</span>Enter your area code to get your local number:</div>