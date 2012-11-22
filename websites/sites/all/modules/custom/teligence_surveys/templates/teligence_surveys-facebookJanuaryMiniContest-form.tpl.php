<?php
/**
 * this page can be accessed via http://www.livelinks.com/surveys/facebook-jan
 * 
 * In order to theme this page, login to drupal as admin and go to the URL above
 * 
 * 
 */
?>
<?php print $scripts ?>
<div>
	BIG IMAGE HERE
</div>
<div>
	BLURB + LIKE BUTTONS HERE
</div>

<?php if($likeUsToEnter){ ?>
	<div>
		LIKE US TO ENTER THE CONTEST
	</div>
<?php } ?>

<?php if($alreadyEntered){ ?>
	<div>
		YOU ALREADY ENTERED THE CONTEST
	</div>
<?php } ?>

<?php if($noFacebookId){ ?>
	<div>
		Please allow us to access your basic information first.
		Please click <a href="<?php print $allowPermissionsURL ?>" target="_top">here</a>.
	</div>
<?php } ?>

<?php if($formStepOne){ ?>
	<div>
		FORM AND TERMS AND CONDITION LINK HERE	
		<?php print drupal_render($form); ?>
	</div>
<?php } ?>

<?php if($formStepTwo){ ?>
	<div>
		YOU ARE NOW ENTERED IN THE CONTEST
	</div>
<?php } ?>

<?php if($contestOver){ ?>
	<div>
		THIS CONTEST IS OVER, WE HAVE A WINNER
	</div>
<?php } ?>
