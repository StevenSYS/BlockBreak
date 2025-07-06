/* HTML Canvas Implementation */
const context = element_canvas.getContext("2d");

function impl_init(fontSize, fontName) {
	context.font = fontSize + "px " + fontName;
	return;
}

importList["impl_loopStart"] = function() {
	context.clearRect(
		0, 0,
		element_canvas.width, element_canvas.height
	);
	
	context.fillStyle = "#000";
	context.fillRect(
		0, 0,
		element_canvas.width, element_canvas.height
	);
	return;
}

importList["impl_setColor"] = function(red, green, blue) {
	context.fillStyle = "rgb(" + red + ", " + green + ", " + blue + ")";
	return;
}

/* Drawing */
importList["impl_drawNumber"] = function(
	x, y,
	number
) {
	context.fillText(number, x, y + (fontSize - 1));
	return;
}

importList["impl_drawFillRect"] = function(
	x, y,
	width, height
) {
	context.beginPath();
	context.rect(x, y, width, height);
	context.fill();
	return;
}