/* Local Storage (JS) Implementation */
const hssImpl_itemName = PROGRAM_NAME + "_highScore";

function hssImpl_get() {
	return localStorage.getItem(hssImpl_itemName);
} 
 
function hssImpl_set(highScore) {
	localStorage.setItem(hssImpl_itemName, highScore);
	return;
}  
  
function hssImpl_open() {
	if (localStorage.getItem(hssImpl_itemName) == undefined) {
		hssImpl_set(0);
	} 
	return;
} 