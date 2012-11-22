HEADER ENGLISH ============================================================= 
<div id="llk-home-cta">
<div class="locBlockHomePageCityWrap">
<div class="locBlockHomePageCity">Meet [city] Singles Now</div>
<div class="locBlockHomePage">Call Livelinks, the hottest place to meet the coolest people.</div>
</div>
<div class="locFreeNow"><img alt="Call Free Now" src="/sites/all/themes/new_livelinks/css/images/2011/tryFreeNow_en.png" /></div>
<div class="locAni dropshadow">Call [ani]</div>
<div class="locEnterAreaCode"><?php if($_SESSION['localization']->City <> 'Local'){ ?>Not in [city]? <?php } ?>Enter your area code to get your local number:</div>
<div id="llk-home-form-cta">
<form method="post" enctype="application/x-www-form-urlencoded" action="/join-now/local-number-look-up" id="local_number_lookup">
    <input type="text" class="input-area-code" tabindex="1" size="3" name="area_code" maxlength="3" /> 			<input type="image" value="GO!" src="/sites/all/themes/new_livelinks/css/images/2011/llk-btn-go-73x32.png" name="submit_call_me_now" alt="GO!" class="button-go" />
</form>
</div>
</div>

HEADER SPANISH =============================================================
<div id="llk-home-cta">
<div class="locBlockHomePageCityWrap">
<div class="locBlockHomePageCity">Conoce Solteros <?php if($_SESSION['localization']->City == 'Local'){ ?>Locales Ahora<?php }else{ ?>en [city] Ahora<?php } ?></div>
<div class="locBlockHomePage">Llama a Livelinks,  El lugar m&aacute;s sexy para conectar a la gente m&aacute;s buena onda</div>
</div>
<div class="locFreeNow"><img alt="Llama Gratis Ahora" src="/sites/all/themes/new_livelinks/css/images/2011/tryFreeNow_es.png" /></div>
<div class="locAni dropshadow">Llama [ani]</div>
<div class="locEnterAreaCode"><?php if($_SESSION['localization']->City <> 'Local'){ ?>No est&Aacute;s en [city]? <?php } ?>Ingresa tu c&oacute;digo de &Aacute;rea:</div>
<div id="llk-home-form-cta">
<form id="local_number_lookup" action="/join-now/local-number-look-up" enctype="application/x-www-form-urlencoded" method="post">
    <input type="text" maxlength="3" name="area_code" size="3" tabindex="1" class="input-area-code" /> 			<input type="image" class="button-go" alt="GO!" name="submit_call_me_now" src="/sites/all/themes/new_livelinks/css/images/2011/llk-btn-go-73x32.png" value="GO!" />
</form>
</div>
</div>

===================================================== LAST TWO LINES FOR HOME PAGE NODE
<?php //$header=rand(1,4);?>
<div id="model-home" class="model-[flavor]">&nbsp;</div>
