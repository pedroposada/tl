<!-- test url purchase/result/$id?LocalAccessNumber= -->
<!-- 3.1 Customers with no web account (not signed in) -->
<!-- 3.2 Customer with web account (signed in) but no active linked membership -->
<?php if($id == 'creditcardasu'){ ?>
	
	<p><?php print t('Local Access Number: !lan',array('!lan'=>$LocalAccessNumber)) ?></p>
	<p><?php print t('Total: $!tot',array('!tot'=>substr($TotalAmountCents,0,-2).'.'.substr($TotalAmountCents,-2))) ?></p>
	<p><?php print t('Package: !min minutes',array('!min'=>$PackageMinutes)) ?></p>
	<p><?php print t('Membership Number: !num',array('!num'=>$IvrMembershipNumber)) ?></p>
	<p><?php print t('Passcode: !pass',array('!pass'=>$IvrPasscode)) ?></p>
	<p><?php print t('City: !pass',array('!pass'=>$City)) ?></p>
	<p><?php print t('Email: !pass',array('!pass'=>$Email)) ?></p>
	
<?php } ?>

<!-- 3.3 Customer with web account (signed in) and active linked IVR memberships -->
<?php if($id == 'creditcardsr'){ ?>
	
	<p><?php print t('Local Access Number: !lan',array('!lan'=>$LocalAccessNumber)) ?></p>
	<p><?php print t('Total: $!tot',array('!tot'=>substr($TotalAmountCents,0,-2).'.'.substr($TotalAmountCents,-2))) ?></p>
	<p><?php print t('Package: !min minutes',array('!min'=>$PackageMinutes)) ?></p>
	<p><?php print t('Membership Number: !num',array('!num'=>$IvrMembershipNumber)) ?></p>
	<p><?php print t('Passcode: !pass',array('!pass'=>$IvrPasscode)) ?></p>
	<p><?php print t('City: !pass',array('!pass'=>$City)) ?></p>
	<p><?php print t('Email: !pass',array('!pass'=>$Email)) ?></p>
	
<?php } ?>

<!-- PAYPAL -->
<?php if($id == 'paypalasu'){ ?>
	
	<p><?php print t('Local Access Number: !lan',array('!lan'=>$LocalAccessNumber)) ?></p>
	<p><?php print t('Total: $!tot',array('!tot'=>$TotalAmountDollars)) ?></p>
	<p><?php print t('Package: !min minutes',array('!min'=>$PackageMinutes)) ?></p>
	<p><?php print t('Membership Number: !num',array('!num'=>$IvrMembershipNumber)) ?></p>
	<p><?php print t('Passcode: !pass',array('!pass'=>$IvrPasscode)) ?></p>
	<p><?php print t('City: !pass',array('!pass'=>$City)) ?></p>
	<p><?php print t('Email: !pass',array('!pass'=>$Email)) ?></p>
	
<?php } ?>
<?php if($id == 'paypalsr'){ ?>
	
	<p><?php print t('Local Access Number: !lan',array('!lan'=>$LocalAccessNumber)) ?></p>
	<p><?php print t('Total: $!tot',array('!tot'=>$TotalAmountDollars)) ?></p>
	<p><?php print t('Package: !min minutes',array('!min'=>$PackageMinutes)) ?></p>
	<p><?php print t('Membership Number: !num',array('!num'=>$IvrMembershipNumber)) ?></p>
	<p><?php print t('Passcode: !pass',array('!pass'=>$IvrPasscode)) ?></p>
	<p><?php print t('City: !pass',array('!pass'=>$City)) ?></p>
	<p><?php print t('Email: !pass',array('!pass'=>$Email)) ?></p>
	
<?php } ?>
<?php if($id == 'paypalfailure'){ ?>
	
	<p><?php print t('Error: !error',array('!error'=>$ErrorMessage)) ?></p>
	
<?php } ?>
