include("impl/" + implFile + ".js");
include("impl/highScore/" + hssImplFile + ".js");
include("impl/screenshot/" + sImplFile + ".js");

if (urlParams.has("touchDeadZone")) {
	touchDeadZone = parseFloat(urlParams.get("touchDeadZone"));
} else {
	touchDeadZone = 32;
}

WebAssembly.instantiateStreaming(
	fetch("build/BlockBreakC-WASM.wasm"),
	{ env: importList }
).then(result => {
	/* Touch Input */
	var touch_startX, touch_deltaX, touch_positiveX;
	var touch_startY, touch_deltaY, touch_positiveY;
	
	function touchStart(event) {
		for (const touch of event.changedTouches) {
			touch_startX = touch.pageX;
			touch_startY = touch.pageY;
		}
		return;
	}
	
	function touchEnd(event) {
		event.preventDefault();
		for (const touch of event.changedTouches) {
			touch_deltaX = touch.pageX - touch_startX;
			touch_deltaY = touch.pageY - touch_startY;
			touch_positiveX = Math.abs(touch_deltaX);
			touch_positiveY = Math.abs(touch_deltaY);
			
			if (
				touch_deltaY < -touchDeadZone
				&&
				touch_deltaY < -touch_positiveX
			) {
				result.instance.exports.jsInput(38); /* Up */
			} else if (
				touch_deltaY > touchDeadZone
				&&
				touch_deltaY > touch_positiveX
			) {
				result.instance.exports.jsInput(40); /* Down */
			}
			
			if (
				touch_deltaX < -touchDeadZone
				&&
				touch_deltaX < -touch_positiveY
			) {
				result.instance.exports.jsInput(37); /* Left */
			} else if (
				touch_deltaX > touchDeadZone
				&&
				touch_deltaX > touch_positiveY
			) {
				result.instance.exports.jsInput(39); /* Right */
			}
		}
		return;
	}
	
	document.addEventListener("touchstart", touchStart);
	document.addEventListener("touchend", touchEnd);
	
	/* Keyboard Input */
	function input(event) {
		result.instance.exports.jsInput(event.keyCode);
		return;
	}
	
	document.addEventListener("keydown", input);
	if (!urlParams.has("noSButton")) {
		element_screenshotButton.addEventListener(
			"click",
			function() {
				result.instance.exports.jsInput(83);
			},
			false
		);
		element_screenshotButton.addEventListener(
			"touchstart",
			function() {
				result.instance.exports.jsInput(83);
			},
			false
		);
	}
	
	result.instance.exports._start();
	
	programName.init(result.instance.exports.memory.buffer);
	programVersion.init(result.instance.exports.memory.buffer);
	
	element_title.innerText = programName.string + "-WASM v" + programVersion.string;
	
	impl_init(fontSize, "Fixedsys");
	
	loop = setInterval(result.instance.exports.draw, 1000 / maxFPS);
});