/* SVG (C-WASM) Implementation */
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
		colorHex = (
			padZero(red.toString(16)) +
			padZero(green.toString(16)) +
			padZero(blue.toString(16))
		).toUpperCase();
	}
	return;
}

function sImpl_number(
	x, y,
	number
) {
	if (sImpl_take == 2) {
		sImpl_svgData += (`\t<text x="${x}" y="${y + fontSize}" fill="#${colorHex}">${number}</text>\n`);
	}
	return;
}

function sImpl_fillRect(
	x, y,
	width, height
) {
	if (sImpl_take == 2) {
		sImpl_svgData += (`\t<rect width="${width}" height="${height}" x="${x}" y="${y}" fill="#${colorHex}"/>\n`);
	}
	return;
}

/* Misc. */
function sImpl_start(impl) {
	if (sImpl_take == 1) {
		sImpl_take = 2;
		sImpl_svgData = (`<svg width="${element_canvas.width}" height="${element_canvas.height}" xmlns="http://www.w3.org/2000/svg">\n`);
		sImpl_svgData += (`\t<!-- ${programName.string}-WASM v${programVersion.string} -->\n`);
		sImpl_svgData += (`\t<!-- Implementation: ${impl} -->\n`);
		sImpl_svgData += (`\t<!-- Screenshot Implementation: SVG (C-WASM) -->\n`);
		sImpl_svgData += (`\t<style>\n`);
		sImpl_svgData += (`\t\ttext {\n`);
		sImpl_svgData += (`\t\t\tfont-family: sans-serif;\n`);
		sImpl_svgData += (`\t\t\tfont-size: ${fontSize}px;\n`);
		sImpl_svgData += (`\t\t}\n`);
		sImpl_svgData += (`\t</style>\n`);
		sImpl_svgData += (`\t<rect width="${element_canvas.width}" height="${element_canvas.height}" fill="#000"/>\n`);
	}
	return;
}

importList["sImpl_end"] = function () {
	if (sImpl_take == 2) {
		sImpl_take = 0;
		sImpl_svgData += "</svg>";
		const blob = new Blob(
			[ sImpl_svgData ],
			{ type: "image/svg" }
		);
		const element_download = document.createElement("a");
		const url = window.URL.createObjectURL(blob);
		element_download.href = url;
		element_download.download = sImpl_fileName;
		element_download.click();
		window.URL.revokeObjectURL(url);
	}
	return;
}

importList["sImpl_setTake"] = function(newValue) {
	sImpl_take = newValue;
	return;
}