importList["hssImpl_get"] = function() {
	ret = localStorage.getItem("BlockBreakC-WASM_highScore");
	if (ret == undefined) {
		localStorage.setItem("BlockBreakC-WASM_highScore", 0);
		ret = 0;
	}
	return ret;
}

importList["hssImpl_set"] = function(highScore) {
	localStorage.setItem("BlockBreakC-WASM_highScore", highScore);
	return;
}

importList["hssImpl_open"] = importList["hssImpl_close"] = function() {
	return;
}