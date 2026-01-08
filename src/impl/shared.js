/* JavaScript Shared Stuff */
var maxFPS;
var fontSize;
var programName = new stringPointer;
var programVersion = new stringPointer;

importList["getMacros"] = function(
	memPos_programName, memPos_programVersion,
	renderWidth, renderHeight,
	macro_maxFPS,
	fontHeight
) {
	programName.memPos = memPos_programName;
	programVersion.memPos = memPos_programVersion;
	maxFPS = macro_maxFPS;
	element_canvas.width = renderWidth;
	element_canvas.height = renderHeight;
	element_canvas.style.maxWidth = renderWidth + "px";
	element_canvas.style.maxHeight = renderHeight + "px";
	fontSize = fontHeight;
	return;
}