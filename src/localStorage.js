/* Local Storage (C-WASM) Implementation */
const hssImpl_itemName = "BlockBreakC-WASM_highScore";

imports.hssImpl_get = function () {
	return localStorage.getItem(hssImpl_itemName);
}

imports.hssImpl_set = function (highScore) {
	localStorage.setItem(hssImpl_itemName, highScore);
	return;
}

imports.hssImpl_open = function () {
	if (localStorage.getItem(hssImpl_itemName) == undefined) {
		imports.hssImpl_set(0);
	}
	return;
}

imports.hssImpl_close = function () {
	return;
}