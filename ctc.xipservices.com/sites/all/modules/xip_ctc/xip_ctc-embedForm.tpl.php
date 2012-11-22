<!-- Start CTC code snippet -->
<style>.ctcFormHidden{display: none;}.ctcFormVisible{display: block;}</style>
<script type="text/javascript" src="<?php print $scriptSource ?>"></script>
<div class="ctcFormHidden" id="ctcFormMessages" style="border: 1px solid #C4B700; background-color: #FFF787; padding: 5px;"></div>
<form id="ctcForm" accept-charset="UTF-8" onsubmit="return ctcSubmitForm()" >
<label for="RequestorPhone">Enter your phone number: </label>
<input type="text" value="" size="10" id="RequestorPhone" name="RequestorPhone" maxlength="10">
<label for="txtCaptcha">Enter these numbers: </label>
<div id="txtCaptcha" style="text-align:center; width:115px; background-image: url(<?php print $captchaImage ?>)"></div>
<label for="CaptchaValue">in this box: </label>
<input type="text" value="" size="10" id="txtInput" name="txtInput" maxlength="10">
<input type="submit" id="ctcSubmit" value="Call me now!">
<img src="" id="ctcCall" style="display: none" />
<input type="hidden" value="DESTINATIONPHONE" id="DestinationPhone" name="DestinationPhone">
<input type="hidden" value="PARTNERID" id="PartnerID" name="PartnerID">
<input type="hidden" value="SOURCE" id="Source" name="Source">
</form>
<!-- End CTC code snippet -->