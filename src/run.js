include("impls/" + implFile + ".js");
include("impls/highScore/" + hssImplFile + ".js");
// include("impls/screenshot/" + sImplFile + ".js");

if (urlParams.has("touchDeadZone")) {
	touchDeadZone = parseFloat(urlParams.get("touchDeadZone"));
} else {
	touchDeadZone = 32;
}

function toPositive(number) {
	if (number < 0) {
		return -number;
	} else {
		return number;
	}
}

WebAssembly.instantiateStreaming(
	fetch("build/BlockBreakC-WASM.wasm"),
	{ "env": importList }
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
			touch_positiveX = toPositive(touch_deltaX);
			touch_positiveY = toPositive(touch_deltaY);
			
			if (
				touch_deltaY < -touchDeadZone
				&&
				touch_deltaY < -touch_positiveX
			) {
				result.instance.exports.input(38); /* Up */
			} else if (
				touch_deltaY > touchDeadZone
				&&
				touch_deltaY > touch_positiveX
			) {
				result.instance.exports.input(40); /* Down */
			}
			
			if (
				touch_deltaX < -touchDeadZone
				&&
				touch_deltaX < -touch_positiveY
			) {
				result.instance.exports.input(37); /* Left */
			} else if (
				touch_deltaX > touchDeadZone
				&&
				touch_deltaX > touch_positiveY
			) {
				result.instance.exports.input(39); /* Right */
			}
		}
		return;
	}
	
	document.addEventListener("touchstart", touchStart);
	document.addEventListener("touchend", touchEnd);
	
	/* Keyboard Input */
	function input(event) {
		result.instance.exports.input(event.keyCode);
		return;
	}
	document.addEventListener("keydown", input);
	
	result.instance.exports._start();
	
	programName.init(result.instance.exports.memory.buffer);
	programVersion.init(result.instance.exports.memory.buffer);
	
	element_title.innerText = programName.string + "-WASM v" + programVersion.string;
	
	impl_init(fontSize, "Fixedsys");
	
	loop = setInterval(result.instance.exports.draw, 1000 / maxFPS);
});