const element_canvas = document.createElement("canvas");

element_canvas.width = RENDER_WIDTH;
element_canvas.height = RENDER_HEIGHT;
element_canvas.style.maxWidth = RENDER_WIDTH + "px";
element_canvas.style.maxHeight = RENDER_HEIGHT + "px";
if (!urlParams.has("noBorder")) {
	element_canvas.classList.add("border");
}

document.body.appendChild(element_canvas);

const element_screenshotButton = document.createElement("div");
if (!urlParams.has("noSButton")) {
	element_screenshotButton.classList.add("button");
	element_screenshotButton.classList.add("buttonGray");
	element_screenshotButton.innerText = "Screenshot";
	element_screenshotButton.addEventListener(
		"click",
		function() {
			sImpl_take = 1;
		},
		false
	);
	element_screenshotButton.addEventListener(
		"touchstart",
		function() {
			sImpl_take = 1;
		},
		false
	);
	document.body.appendChild(document.createElement("br"));
	document.body.appendChild(element_screenshotButton);
}