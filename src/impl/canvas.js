/* HTML Canvas (C-WASM) Implementation */
const context = element_canvas.getContext("2d");

function impl_init(fontSize, fontName) {
	context.font = fontSize + "px " + fontName;
	return;
}

imports.impl_loopStart = function () {
	context.clearRect(
		0, 0,
		element_canvas.width, element_canvas.height
	);
	
	context.fillStyle = "#000";
	context.fillRect(
		0, 0,
		element_canvas.width, element_canvas.height
	);
	sImpl_start("HTML Canvas");
	return;
}

/* Drawing */
imports.impl_setColor = function (red, green, blue) {
	context.fillStyle = "rgb(" + red + ", " + green + ", " + blue + ")";
	sImpl_setColor(red, green, blue);
	return;
}

imports.impl_drawNumber = function (
	x, y,
	number
) {
	context.fillText(number, x, y + (fontSize - 2));
	sImpl_number(x, y, number);
	return;
}

imports.impl_drawFillRect = function (
	x, y,
	width, height
) {
	context.beginPath();
	context.rect(x, y, width, height);
	context.fill();
	sImpl_fillRect(x, y, width, height);
	return;
}