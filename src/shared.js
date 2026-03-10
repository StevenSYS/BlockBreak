/* JavaScript Shared Stuff */
var maxFPS;
var fontSize;
var programName = new stringPointer;
var programVersion = new stringPointer;

imports.getMacros = function (
	ptrName,
	ptrVersion,
	renderWidth,
	renderHeight,
	fps,
	fontHeight
) {
	programName.memPos = ptrName;
	programVersion.memPos = ptrVersion;
	maxFPS = fps;
	element_canvas.width = renderWidth;
	element_canvas.height = renderHeight;
	element_canvas.style.maxWidth = renderWidth + "px";
	element_canvas.style.maxHeight = renderHeight + "px";
	fontSize = fontHeight;
	return;
}