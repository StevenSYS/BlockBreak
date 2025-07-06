/* Session Storage Implementation */
const hssImpl_itemName = "BlockBreakC-WASM_highScore";

importList["hssImpl_get"] = function() {
	return sessionStorage.getItem(hssImpl_itemName);
}

importList["hssImpl_set"] = function(highScore) {
	sessionStorage.setItem(hssImpl_itemName, highScore);
	return;
}

importList["hssImpl_open"] = function() {
	if (sessionStorage.getItem(hssImpl_itemName) == undefined) {
		importList["hssImpl_set"](0);
	}
	return;
}

importList["hssImpl_close"] = function() {
	return;
}