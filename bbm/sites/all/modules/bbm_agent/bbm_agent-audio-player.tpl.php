<?php 
/**
 * VARIABLES
 * $audio_player_src		Path to the audio player swf file (no .swf at the end). Should be relative.	
 * $flashvar1				Path to the audio file. Can be absolute or relative. Has been tested with .mp3 format.
 * $form					The rest of the form elements. This is specific to Drupal FAPI
 */
?>


<script language="javascript">
	if (AC_FL_RunContent == 0) {
		alert("This page requires AC_RunActiveContent.js.");
	} else {
		AC_FL_RunContent(
			'codebase', 'http://download.macromedia.com/pub/shockwave/cabs/flash/swflash.cab#version=9,0,0,0',
			'width', '500',
			'height', '40',
			'src', '<?php print $audio_player_src ?>',
			'quality', 'high',
			'pluginspage', 'http://www.macromedia.com/go/getflashplayer',
			'align', 'middle',
			'play', 'true',
			'loop', 'true',
			'scale', 'showall',
			'wmode', 'opaque',
			'devicefont', 'false',
			'id', 'playback controller',
			'bgcolor', '#ffffff',
			'name', 'playback controller',
			'menu', 'true',
			'allowFullScreen', 'false',
			'allowScriptAccess','sameDomain',
			'movie', '<?php print $audio_player_src ?>',
			'FlashVars', '<?php print $flashvar1 ?>',
			'salign', ''
			); //end AC code
	}
</script>
<noscript>
	<object classid="clsid:d27cdb6e-ae6d-11cf-96b8-444553540000" codebase="http://download.macromedia.com/pub/shockwave/cabs/flash/swflash.cab#version=9,0,0,0" width="500" height="40" id="playback controller" align="middle">
	<param name="allowScriptAccess" value="sameDomain" />
	<param name="allowFullScreen" value="false" />
	<param name="FlashVars" value="<?php print $flashvar1 ?>" />
	<param name="movie" value="<?php print $audio_player_src ?>.swf" />
	<param name="quality" value="high" />
	<param name="wmode" value="opaque">
	<param name="bgcolor" value="#ffffff" />	
	<embed src="<?php print $audio_player_src ?>.swf" FlashVars="<?php print $flashvar1 ?>" wmode="opaque" quality="high" bgcolor="#ffffff" width="500" height="40" name="playback controller" align="middle" allowScriptAccess="sameDomain" allowFullScreen="false" type="application/x-shockwave-flash" pluginspage="http://www.macromedia.com/go/getflashplayer" />
	</object>
</noscript>

<?php print $form ?>
