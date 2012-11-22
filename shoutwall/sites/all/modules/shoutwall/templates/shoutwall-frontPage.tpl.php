<div class="leftColumn">
	<div id="frontpageTop">
		SHOUTWALL FRONT PAGE CONTENT HERE
	</div>
	
	<div id="frontpageAudioPlayer">
		<?php print $audioPlayer ?>
	</div>
	
	<div id="frontpageContentTabs">
		<ul id="frontPageTabsList">
			<li><a class="frontPagetab active" name="whatis">WHAT IS SHOUTWALL</a></li>
			<li><a class="frontPagetab" name="howitworks">HOW IT WORKS</a></li>
			<li><a class="frontPagetab" name="faq">FAQ</a></li>
			<li><a class="frontPagetab" name="aboutus">ABOUT US</a></li>
		</ul>
	</div>
	
	<div id="tabsWrapper">
		<div id="whatis" class="tabContent active">
			WHAT IS SHOUTWALL
		</div>
		<div id="howitworks" class="tabContent">
			HOW IT WORKS
		</div>
		<div id="faq" class="tabContent">
			FAQ
		</div>
		<div id="aboutus" class="tabContent">
			ABOUT US
			<div>
				<?php print drupal_render($feedbackForm) ?>
			</div>
		</div>
	</div>
</div>

<div id="frontpageSideBlocks" class="rightColumn">
	SIDE BLOCKS
</div>