var touched;
var t;
function disabler(buttonId){
	document.getElementById(buttonId).disabled=true;
	document.getElementById(buttonId).value="Processing...";
    clearTimeout(t);
};