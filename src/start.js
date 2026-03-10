var imports = {};
const urlParams = new URLSearchParams(window.location.search);

const element_canvas = document.getElementById("canvas");
const element_title = document.getElementById("title");

element_canvas.style.maxWidth = "0px";
element_canvas.style.maxHeight = "0px";

if (!urlParams.has("noBorder")) {
	element_canvas.classList.add("border");
}