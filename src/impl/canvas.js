/* HTML Canvas (JS) Implementation */
const context = element_canvas.getContext("2d");

function impl_init(FONT_HEIGHT, fontName) {
	context.font = FONT_HEIGHT + "px " + fontName;
	return;
}

function impl_loopStart() {
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
function impl_setColor(red, green, blue) {
	context.fillStyle = "rgb(" + red + ", " + green + ", " + blue + ")";
	sImpl_setColor(red, green, blue);
	return;
}

function impl_drawNumber(
	x, y,
	number
) {
	context.fillText(number, x, y + (FONT_HEIGHT - 1));
	sImpl_number(x, y, number);
	return;
}

function impl_drawFillRect(
	x, y,
	width, height
) {
	context.beginPath();
	context.rect(x, y, width, height);
	context.fill();
	sImpl_fillRect(x, y, width, height);
	return;
}