$(document).ready(function() {
// for links with a class of "no_click" disable the click
    $("a.no_click").click(function() { return false; });

// for div with class of "slideshow" rotate images - LLK video rotation - Home Page/Why Livelinks
	$('div.slideshow').cycle({fx: 'fade' });

// add remove focus bg from field
	$('input#cta_areaCode').focus().click(function() {$('input#cta_areaCode').addClass('focus')}).keydown(function() {$('input#cta_areaCode').addClass('focus')});

// auto focus for area code
	$('input.input-area-code').focus();
	$('input#edit-area-code').focus();
	$('input.cta-input').focus();
	$('input.cta-input-banner').focus();
	
// whats new page hide/reveal functionality
	$('div.whatsnew1').hide();
	$('div.whatsnew2').hide();
	$('div.whatsnew3').hide();

	$('span.whatsnew1').click(function(){
		$('div.whatsnew1').slideDown("slow");
	});
	$('span.whatsnew2').click(function(){
		$('div.whatsnew2').slideDown("slow");
	});
	$('span.whatsnew3').click(function(){
		$('div.whatsnew3').slideDown("slow");
	});
	$('p.hide1').click(function(){
		$('div.whatsnew1').slideUp("slow");
	});
	$('p.hide2').click(function(){
		$('div.whatsnew2').slideUp("slow");
	});
	$('p.hide3').click(function(){
		$('div.whatsnew3').slideUp("slow");
	});
	
// auto tab for CTC fields
	$('input#edit-area-code, #edit-phone-number, #edit-CaptchaValue').autotab_magic().autotab_filter('numeric');

// auto focus for Email
	$('input#edit-email').focus();
	
// LLK Home Page Ballons - EN
	$('div.bltTitle-01').click(function() {
		$('div[class*="bltContent"]').hide();
		$(this).parent().find('.bltContent-01').show().css("margin-bottom", "-200px");
		$('.llk-bubble-top-bg').show();
		$('.llk-bubble-content').show();
		$('.llk-bubble-bottom-bg').show();
	});
 
 	$('div.bltTitle-02').click(function() {
		$('div[class*="bltContent"]').hide();
		$(this).parent().find('.bltContent-02').show().css("margin-bottom", "-240px");
		$('.llk-bubble-top-bg').show();
		$('.llk-bubble-top-content').show();
		$('.llk-bubble-bottom-bg').show();
	});
 
  	$('div.bltTitle-03').click(function() {
		$('div[class*="bltContent"]').hide();
		$(this).parent().find('.bltContent-03').show().css("margin-bottom", "-198px");
		$('.llk-bubble-top-bg').show();
		$('.llk-bubble-top-content').show();
		$('.llk-bubble-bottom-bg').show();
	});
	
	 $('div.bltTitle-04').click(function() {
		$('div[class*="bltContent"]').hide();
		$(this).parent().find('.bltContent-04').show().css("margin-bottom", "-260px");
		$('.llk-bubble-top-bg').show();
		$('.llk-bubble-top-content').show();
		$('.llk-bubble-bottom-bg').show();

	});
	
	$('div.bltTitle-05').click(function() {
		$('div[class*="bltContent"]').hide();
		$(this).parent().find('.bltContent-05').show().css("margin-bottom", "-280px");
		$('.llk-bubble-top-bg').show();
		$('.llk-bubble-top-content').show();
		$('.llk-bubble-bottom-bg').show();
	});
 
 	$('div.bltTitle-06').click(function() {
		$('div[class*="bltContent"]').hide();
		$(this).parent().find('.bltContent-06').show().css("margin-bottom", "-280px");
		$('.llk-bubble-top-bg').show();
		$('.llk-bubble-top-content').show();
		$('.llk-bubble-bottom-bg').show();
	});
 
  	$('div.bltTitle-07').click(function() {
		$('div[class*="bltContent"]').hide();
		$(this).parent().find('.bltContent-07').show().css("margin-bottom", "-240px");
		$('.llk-bubble-top-bg').show();
		$('.llk-bubble-top-content').show();
		$('.llk-bubble-bottom-bg').show();
	});
	
	 $('div.bltTitle-08').click(function() {
		$('div[class*="bltContent"]').hide();
		$(this).parent().find('.bltContent-08').show().css("margin-bottom", "-240px");
		$('.llk-bubble-top-bg').show();
		$('.llk-bubble-top-content').show();
		$('.llk-bubble-bottom-bg').show();
	});
	
	$('div.bltTitle-09').click(function() {
		$('div[class*="bltContent"]').hide();
		$(this).parent().find('.bltContent-09').show().css("margin-bottom", "-330px");
		$('.llk-bubble-top-bg').show();
		$('.llk-bubble-top-content').show();
		$('.llk-bubble-bottom-bg').show();
	});
	
// LLK Home Page Ballons - SP
	$('div.bltTitle-sp-01').click(function() {
		$('div[class*="bltContent"]').hide();
		$(this).parent().find('.bltContent-01').show().css("margin-bottom", "-330px");
		$('.llk-bubble-top-bg').show();
		$('.llk-bubble-content').show();
		$('.llk-bubble-bottom-bg').show();
	});
 
 	$('div.bltTitle-sp-02').click(function() {
		$('div[class*="bltContent"]').hide();
		$(this).parent().find('.bltContent-02').show().css("margin-bottom", "-380px");
		$('.llk-bubble-top-bg').show();
		$('.llk-bubble-top-content').show();
		$('.llk-bubble-bottom-bg').show();
	});
 
  	$('div.bltTitle-sp-03').click(function() {
		$('div[class*="bltContent"]').hide();
		$(this).parent().find('.bltContent-03').show().css("margin-bottom", "-200px");
		$('.llk-bubble-top-bg').show();
		$('.llk-bubble-top-content').show();
		$('.llk-bubble-bottom-bg').show();
	});
	
	 $('div.bltTitle-sp-04').click(function() {
		$('div[class*="bltContent"]').hide();
		$(this).parent().find('.bltContent-04').show().css("margin-bottom", "-350px");
		$('.llk-bubble-top-bg').show();
		$('.llk-bubble-top-content').show();
		$('.llk-bubble-bottom-bg').show();

	});
	
	$('div.bltTitle-sp-05').click(function() {
		$('div[class*="bltContent"]').hide();
		$(this).parent().find('.bltContent-05').show().css("margin-bottom", "-340px");
		$('.llk-bubble-top-bg').show();
		$('.llk-bubble-top-content').show();
		$('.llk-bubble-bottom-bg').show();
	});
 
 	$('div.bltTitle-sp-06').click(function() {
		$('div[class*="bltContent"]').hide();
		$(this).parent().find('.bltContent-06').show().css("margin-bottom", "-280px");
		$('.llk-bubble-top-bg').show();
		$('.llk-bubble-top-content').show();
		$('.llk-bubble-bottom-bg').show();
	});
 
  	$('div.bltTitle-sp-07').click(function() {
		$('div[class*="bltContent"]').hide();
		$(this).parent().find('.bltContent-07').show().css("margin-bottom", "-300px");
		$('.llk-bubble-top-bg').show();
		$('.llk-bubble-top-content').show();
		$('.llk-bubble-bottom-bg').show();
	});
	
	 $('div.bltTitle-sp-08').click(function() {
		$('div[class*="bltContent"]').hide();
		$(this).parent().find('.bltContent-08').show().css("margin-bottom", "-260px");
		$('.llk-bubble-top-bg').show();
		$('.llk-bubble-top-content').show();
		$('.llk-bubble-bottom-bg').show();
	});
	
	$('div.bltTitle-sp-09').click(function() {
		$('div[class*="bltContent"]').hide();
		$(this).parent().find('.bltContent-09').show().css("margin-bottom", "-360px");
		$('.llk-bubble-top-bg').show();
		$('.llk-bubble-top-content').show();
		$('.llk-bubble-bottom-bg').show();
	});	
	
	//// HIDE THE DIVS ON PAGE LOAD	////
	$('div[class*="bltContent"]').hide().css("display", "none");
	
	//// CLOSE DIALOG BOX ////
	$('a.llk-close').click(function(e) {
		e.stopPropagation();
		$('div[class*="bltContent"]').css("margin-bottom", "0px").hide();
		//$(this).parent().parent().hide();
		//$('.llk-bubble-top-bg').hide();
		//$('.llk-bubble-content').hide();
		//$('.llk-bubble-bottom-bg').hide();
	});
	
// for IML rotate banner - Home Page
	 $('div#iml-slide').cycle({
		fx: 'scrollLeft', 
		speed:  1000,
		animSpeed: "fast",
        timeout: 5000,
        pager:  '#nav',
		prev:   '#prev1', 
        next:   '#next1', 
        before: function() { if (window.console) console.log(this.src); }
	 });	
	 
// for IML drop downs - Home Page		
	$('span.not-expanded-1').hide();
	$('a.link-not-expanded-1').click(function() {$('span.not-expanded-1').toggle('slow');});  
	$('span.not-expanded-2').hide();
	$('a.link-not-expanded-2').click(function() {$('span.not-expanded-2').toggle('slow');}); 
	$('span.not-expanded-3').hide();
	$('a.link-not-expanded-3').click(function() {$('span.not-expanded-3').toggle('slow');}); 
	$('span.not-expanded-4').hide();
	$('a.link-not-expanded-4').click(function() {$('span.not-expanded-4').toggle('slow');}); 
	$('span.not-expanded-5').hide();
	$('a.link-not-expanded-5').click(function() {$('span.not-expanded-5').toggle('slow');}); 
	$('span.not-expanded-6').hide();
	$('a.link-not-expanded-6').click(function() {$('span.not-expanded-6').toggle('slow');}); 
	$('span.not-expanded-7').hide();
	$('a.link-not-expanded-7').click(function() {$('span.not-expanded-7').toggle('slow');}); 
	$('span.not-expanded-8').hide();
	$('a.link-not-expanded-8').click(function() {$('span.not-expanded-8').toggle('slow');}); 
	$('span.not-expanded-9').hide();
	$('a.link-not-expanded-9').click(function() {$('span.not-expanded-9').toggle('slow');}); 

// for IML drop downs - cart/buy - what is payment info
	$('span.cc_secure_info').hide();
	$('a.paymentInfo').click(function() {$('span.cc_secure_info').toggle('slow');});
	
// for IML & LLK Quick Tips	
	$('a.button-1').click(function() {$('div#quick-tips-text').replaceWith('<div id="quick-tips-text"><h3>Request a Connection:</h3> <p>Hear a greeting that turns you on? Want to talk with a guy one on one? Press 1 to request a live connection while keeping 100% confidential.</p></div>');});
    $('a.button-2').click(function() {$('div#quick-tips-text').replaceWith('<div id="quick-tips-text"><h3>Send a Message:</h3> <p>This is a great way to let a guy know you are interested, just send him a message. Maybe you just like his greeting, maybe the sound of his voice.. or maybe you want to get to know more Press 2 to send a message and get the ball rolling.</p></div>');});  
	$('a.button-3').click(function() {$('div#quick-tips-text').replaceWith('<div id="quick-tips-text"><h3>Play Next Greeting:</h3> <p>By pressing 3, you can skip through greeting that you are listening to and jump right to the next guy!</p></div>');});  
	$('a.button-4').click(function() {$('div#quick-tips-text').replaceWith('<div id="quick-tips-text"><h3>Add / Remove Hot List:</h3> <p>You can add your favorite guy to your own personal hot list, just press 4 and you\'ll be notified when he\'s on the line.</p></div>');});  
	$('a.button-5').click(function() {$('div#quick-tips-text').replaceWith('<div id="quick-tips-text"><h3>Local Greetings:</h3><p>Local guys are just a \"press 5\" away. Begin to hear local greetings instantly by pressing 5 while listening to greetings.</p></div>');});  	
	$('a.button-6').click(function() {$('div#quick-tips-text').replaceWith('<div id="quick-tips-text"><h3>Previous Greeting:</h3> <p>Play the greeting you just listened to by pressing 6.</p></div>');});  
	$('a.button-7').click(function() {$('div#quick-tips-text').replaceWith('<div id="quick-tips-text"><h3>Block Caller:</h3> <p>Why waste your time with someone you are not interested in press 7 and you can block a caller. This means you will not hear their greeting as you listen and they cannot send you a message.</p></div>');});  
	$('a.button-8').click(function() {$('div#quick-tips-text').replaceWith('<div id="quick-tips-text"><h3>Location:</h3> <p>Find out the area of the guy is calling from perfect if you want to meet up.</p></div>');});  
	$('a.button-9').click(function() {$('div#quick-tips-text').replaceWith('<div id="quick-tips-text"><h3>Repeat Greeting:</h3><p>Like the greeting you just heard or want to hear it again? Press 9 will repeat the greeting from the beginning.</p></div>');});  
	$('a.button-help').click(function() {$('div#quick-tips-text').replaceWith('<div id="quick-tips-text"><h3>Help:</h3> <p>Press * to get help about our phone chat line, press star.</p></div>');});  	
	$('a.button-exit').click(function() {$('div#quick-tips-text').replaceWith('<div id="quick-tips-text"><h3>Exit:</h3> <p>Exit the menu.</p></div>');});  

// for IML & LLK Quick Tips	- ES
	$('a.button-es-1').click(function() {$('div#quick-tips-text').replaceWith('<div id="quick-tips-text"><h3>Solicitud de Conexi&oacute;n:</h3> <p>&iquest;Escuchas un saludo que te prende? &iquest;Quieres hablar en privado con algun chico? Marca 1 para solicitar una conexi&oacute;n en vivo que ser&aacute; totalmente confidencial.</p></div>');});
    $('a.button-es-2').click(function() {$('div#quick-tips-text').replaceWith('<div id="quick-tips-text"><h3>Enviar Mensaje:</h3> <p>Esta es una excelente forma de decirle a alg&uacute;n chico que estas  interesado as&iacute; que simplemente m&aacute;ndale un mensaje.  Quiz&aacute;s solamente te gusto su saludo o el sonido de su voz... o tal vez quieres saber m&aacute;s asi que Marca 2 para enviar un mensaje y que la bola empiece a rodar.</p></div>');});  
	$('a.button-es-3').click(function() {$('div#quick-tips-text').replaceWith('<div id="quick-tips-text"><h3>Tocar el Siguiente Saludo:</h3> <p>&iexcl;Al marcar 3, puedes saltarte al siguiente saludo y brincar justo donde est&aacute; el siguiente chico!</p></div>');});  
	$('a.button-es-4').click(function() {$('div#quick-tips-text').replaceWith('<div id="quick-tips-text"><h3>A&ntilde;adir/Quitar de la Lista Caliente:</h3> <p>Puedes a&ntilde;adir a tu chico favorito en tu propia lista caliente, solo marca 4 y ser&aacute;s notificado cuando el este en la l&iacute;nea.</p></div>');});  
	$('a.button-es-5').click(function() {$('div#quick-tips-text').replaceWith('<div id="quick-tips-text"><h3>Comenzar Los Saludos Locales:</h3><p>Los chicos locales esta a tan solo un Marca 5 de distancia.  Comienza a escuchar saludos locales de manera instant&aacute;nea marcando 5 mientras escuchas los saludos.</p></div>');});  	
	$('a.button-es-6').click(function() {$('div#quick-tips-text').replaceWith('<div id="quick-tips-text"><h3>Tocar el  Saludo Anterior:</h3> <p>Toca otra vez el saludo que acabas de escuchar marcando 6.</p></div>');});  
	$('a.button-es-7').click(function() {$('div#quick-tips-text').replaceWith('<div id="quick-tips-text"><h3>Bloquear Usuario:</h3> <p>Para que perder tu tiempo con alguien que no te interesa. Marcando 7 puedes bloquear a esa persona. Esto significa que no escucharas su saludo y no te podr&aacute; enviar un mensaje.</p></div>');});  
	$('a.button-es-8').click(function() {$('div#quick-tips-text').replaceWith('<div id="quick-tips-text"><h3>Localizaci&oacute;n:</h3> <p>Descubre de que &aacute;rea te esta llamando este chico. Esto es perfecto si lo que estan planeando es encontrarse.</p></div>');});  
	$('a.button-es-9').click(function() {$('div#quick-tips-text').replaceWith('<div id="quick-tips-text"><h3>Repetir Saludo:</h3><p>Te gusta el saludo que escuchaste o quieres escucharlo otra vez? Marcando 6 lo estar&aacute;s reproduciendo otra vez desde el principio.</p></div>');});  
	$('a.button-es-help').click(function() {$('div#quick-tips-text').replaceWith('<div id="quick-tips-text"><h3>Ayuda:</h3> <p>Marca * para obtener ayuda relacionada a nuestra l&iacute;nea chat por tel&eacute;fono.  Marca Estrella.</p></div>');});  	
	$('a.button-es-exit').click(function() {$('div#quick-tips-text').replaceWith('<div id="quick-tips-text"><h3>Salir:</h3> <p>Sal del men&uacute;.</p></div>');});  




//END//
});
  



