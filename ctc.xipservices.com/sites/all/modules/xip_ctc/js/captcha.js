//Created / Generates the captcha function    
function DrawCaptcha()
{
    var a = Math.ceil(Math.random() * 10)+ '';
    var b = Math.ceil(Math.random() * 10)+ '';       
    var c = Math.ceil(Math.random() * 10)+ '';  
    var d = Math.ceil(Math.random() * 10)+ '';  
    var e = Math.ceil(Math.random() * 10)+ '';  
    var f = Math.ceil(Math.random() * 10)+ '';  
    var g = Math.ceil(Math.random() * 10)+ '';  
    var code = a + ' ' + b + ' ' + ' ' + c + ' ' + d + ' ' + e + ' '+ f + ' ' + g;
    document.getElementById("txtCaptcha").textContent = code
}

// Validate the Entered input aganist the generated security code function   
function ValidCaptcha()
{
    var str1 = removeSpaces(document.getElementById('txtCaptcha').textContent);
    var str2 = removeSpaces(document.getElementById('txtInput').value);
    if (str1 == str2) return true;        
    return false;
    
}

// Remove the spaces from the entered and generated code
function removeSpaces(string)
{
    return string.split(' ').join('');
}

// submit form
function ctcSubmitForm()
{
	var validform = true;
	
	// validate user's phone number
	if(document.getElementById('RequestorPhone').value == ""){
		validform = false;
	}
	
	// validate captcha
	var captcha = ValidCaptcha();
	if(ValidCaptcha()){
		// do nothing
	}else{
		validform = false;
	}
	
	// submit form
	if(validform){
		// build ctc call url
		var RequestorPhone = document.getElementById('RequestorPhone').value;
		var DESTINATIONPHONE = document.getElementById('DestinationPhone').value;
		var PARTNERID = document.getElementById('PartnerID').value;
		var SOURCE = document.getElementById('Source').value;
		var callURL = "http://ctc.xipservices.com/ctc/call?DESTINATIONPHONE=" + DESTINATIONPHONE + "&PARTNERID=" + PARTNERID + "&SOURCE=" + SOURCE + "&RequestorPhone=" + RequestorPhone;
		
		// make the call
		document.getElementById('ctcCall').setAttribute("src",callURL);
		
		// display message to user
		document.getElementById('ctcFormMessages').setAttribute("class","ctcFormVisible");
		document.getElementById('ctcFormMessages').textContent = "We are calling you right now!";
	}else{
		// display failure message to user
		document.getElementById('ctcFormMessages').setAttribute("class","ctcFormVisible");
		document.getElementById('ctcFormMessages').textContent = "Please fill out all the fields properly.";
	}
	
	// redraw cptcha to avoid abuse
	DrawCaptcha();
	
	return false;
}


// check that the document is ready and then execute the function 
window.addEventListener ? 
window.addEventListener("load",DrawCaptcha,false) : 
window.attachEvent && window.attachEvent("onload",DrawCaptcha);