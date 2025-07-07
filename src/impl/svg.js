/* SVG (JS) Implementation */
const sImpl_fileName = "screenshot.svg";

var sImpl_colorHex = "000";
var sImpl_svgData = "";
var sImpl_take = 0;

function padZero(string) {
	if (string.length == 1) {
		return "0" + string;
	} else {
		return string;
	}
}

/* Drawing */
function sImpl_setColor(red, green, blue) {
	if (sImpl_take == 2) {
		colorHex = (padZero(red.toString(16)) + padZero(green.toString(16)) + padZero(blue.toString(16))).toUpperCase();
	}
	return;
}

function sImpl_number(
	x, y,
	number
) {
	if (sImpl_take == 2) {
		sImpl_svgData = sImpl_svgData.concat("\t<text x=\"" + x + "\" y=\"" + (y + FONT_HEIGHT) + "\" fill=\"#" + colorHex + "\">" + number + "</text>\n");
	}
	return;
}

function sImpl_fillRect(
	x, y,
	width, height
) {
	if (sImpl_take == 2) {
		sImpl_svgData = sImpl_svgData.concat("\t<rect width=\"" + width + "\" height=\"" + height + "\" x=\"" + x + "\" y=\"" + y + "\" fill=\"#" + colorHex + "\"/>\n");
	}
	return;
}

/* Misc. */
function sImpl_start(impl) {
	if (sImpl_take == 1) {
		sImpl_svgData = "";
		sImpl_take = 2;
		sImpl_svgData = sImpl_svgData.concat("<svg width=\"" + element_canvas.width  + "\" height=\"" + element_canvas.height + "\" xmlns=\"http://www.w3.org/2000/svg\">\n");
		sImpl_svgData = sImpl_svgData.concat("\t<!-- " + PROGRAM_NAME + " -->\n");
		sImpl_svgData = sImpl_svgData.concat("\t<!-- Screenshot Implementation: SVG (JS) -->\n");
		sImpl_svgData = sImpl_svgData.concat("\t<style>\n");
		sImpl_svgData = sImpl_svgData.concat("\t\ttext {\n");
		sImpl_svgData = sImpl_svgData.concat("\t\t\tfont-family: sans-serif;\n");
		sImpl_svgData = sImpl_svgData.concat("\t\t\tfont-size: " + FONT_HEIGHT + "px;\n");
		sImpl_svgData = sImpl_svgData.concat("\t\t}\n");
		sImpl_svgData = sImpl_svgData.concat("\t</style>\n");
		sImpl_svgData = sImpl_svgData.concat("\t<rect width=\"" + element_canvas.width  + "\" height=\"" + element_canvas.height + "\" fill=\"#000\"/>\n");
	}
	return;
}

function sImpl_end() {
	if (sImpl_take == 2) {
		sImpl_take = 0;
		sImpl_svgData = sImpl_svgData.concat("</svg>");
		const blob = new Blob([sImpl_svgData], { type: "image/svg" });
		const element_download = document.createElement("a");
		const url = window.URL.createObjectURL(blob);
		element_download.href = url;
		element_download.download = sImpl_fileName;
		element_download.click();
		window.URL.revokeObjectURL(url);
	}
	return;
}