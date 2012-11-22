$.fn.fix_radios = function() {
  function click() {
    // if this isn't checked then no option is yet selected. bail
    if ( !this.checked ) return;

    // if this wasn't already checked, manually fire a change event
    if ( !this.was_checked ) {
      $( this ).change();
    }
  }
  function focus() {
    // if this isn't checked then no option is yet selected. bail
    if ( !this.checked ) return;

    // if this wasn't already checked, manually fire a change event
    if ( !this.was_checked ) {
      $( this ).change();
    }
  }

  function change( e ) {
    // shortcut if already checked to stop IE firing again
    if ( this.was_checked ) {
      e.stopImmediatePropagation();
      return;
    }

    // reset all the was_checked properties
    $( "input[name=" + this.name + "]" ).each( function() {
      this.was_checked = this.checked;
    } );
  }

  // attach the handlers and return so chaining works
  return this.click( click ).focus( focus ).change( change );
}
// attach it to all radios on document ready
$( function() {
  $( "input[type=radio]" ).fix_radios();
} );

$(document).ready(function(){
	var ajaxLoaderImg = Drupal.settings.teligence_purchase.widgets.ajaxLoaderImg[0];
	var marketSelectId = Drupal.settings.teligence_purchase.widgets.marketSelectId[0];
	var regionSelectId = Drupal.settings.teligence_purchase.widgets.regionSelectId[0];
	var packagesWrapperId = Drupal.settings.teligence_purchase.widgets.packagesWrapperId[0];
	var getMarketsUrl = Drupal.settings.teligence_purchase.widgets.getMarketsUrl[0];
	var getPackagesByMarketUrl = Drupal.settings.teligence_purchase.widgets.getPackagesByMarketUrl[0];
	var getPackagesByMembershipUrl = Drupal.settings.teligence_purchase.widgets.getPackagesByMembershipUrl[0];

	// GetPackagesByBrandMarket	
	function getPackages(){
		var newGetPackagesUrl = getPackagesByMarketUrl + '/' + $('#' + marketSelectId).val();
		$('#' + packagesWrapperId).html(ajaxLoaderImg);
		$.get(newGetPackagesUrl, function(data){
			$('#' + packagesWrapperId).html(data);
		});
	}
	
	// populate markets dropdown
	$('#' + regionSelectId).bind('change', function(){
		var newGetMarketsUrl = getMarketsUrl + '/' + $(this).val();
		$.get(newGetMarketsUrl, function(data){
			$('#' + marketSelectId).html(data);
			getPackages();
		});
	});
	
	// populate packages radios
	$('#' + marketSelectId).bind('change', getPackages);
	
	// GetPackagesByMembership for 3.3
	if($('#membershipsTable .form-radio:radio'))
	{
		// show/hide region markets dropdowns
		if($("#selectRegionMarketSr")){
			if($('#membershipsTable input[value="newmarket"]').attr('checked')){
				$("#selectRegionMarketSr").show();
			}else{
				$("#selectRegionMarketSr").hide();
			}
		}
		
		// radios
		$('#membershipsTable .form-radio:radio').bind('change',function(){
			if($(this).val() == 'newmarket'){
				getPackages(); 
				$("#selectRegionMarketSr").show();
			}else{
				var newGetPackagesUrl = getPackagesByMembershipUrl + '/' + $(this).val();
				$('#' + packagesWrapperId).html(ajaxLoaderImg);
				$.get(newGetPackagesUrl, function(data){
					$('#' + packagesWrapperId).html(data);
				});
				$("#selectRegionMarketSr").hide();
			}
		});
		
	};
	
	
	
	// paymethods
	// creditcardslistTable, edit-paymethods-cc, edit-paymethods-pp, edit-paymethods-addcc, addNewCcFieldsWrapper
	
	// remove focus from cc list radios when paypal is selected
	$('#edit-paymethods-pp').bind('change',function(){
		if($('#creditcardslistTable')){
			$('#creditcardslistTable .form-radio:radio').removeAttr('checked');
		};
		if($('#ccFieldsWrapper')){
			$('#ccFieldsWrapper').hide();
		}
		if($('#ccFieldsWrapperAsu')){
			$('#ccFieldsWrapperAsu').hide();
		}
	});
	
	// add focus to "pay with existing credit card" radio button when any existing credit card is selected
	if($('#creditcardslistTable')){
		$('#creditcardslistTable .form-radio:radio').bind('change',function(){
			$('#edit-paymethods-cc').attr('checked','checked').change();
		});
		$('#edit-paymethods-cc').bind('change',function(){
			if($('#creditcardslistTable .form-radio:checked').length == 0){
				$('#creditcardslistTable .form-radio:first').attr('checked','checked');
			}
			$('#ccFieldsWrapper').hide();
		});
	};
	
	// add focus to "Add new credit card" radio button 
	if($('#edit-paymethods-addcc').attr('checked')){
		$('#ccFieldsWrapper').show();
	}else{
		$('#ccFieldsWrapper').hide();
	}
	if ($('#ccFieldsWrapper')) {
		$('#edit-paymethods-addcc').bind('change',function(){
			if($('#creditcardslistTable')){
				$('#creditcardslistTable .form-radio:radio').removeAttr('checked');
			};
			$('#ccFieldsWrapper').show();
			$('#ccFieldsWrapper input:first').focus();
		});
	};
	
	// add focus to "Credit Card" radio button 
	if ($('#ccFieldsWrapperAsu')) {
		if($('#edit-paymethods-cc').attr('checked')){
			$('#ccFieldsWrapperAsu').show();
		}else{
			$('#ccFieldsWrapperAsu').hide();
		}
		$('#edit-paymethods-cc').bind('change',function(){
			$('#ccFieldsWrapperAsu').show();
			$('#ccFieldsWrapperAsu input:first').focus();
		});
	};
	
	
});