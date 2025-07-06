const includePath = "src/";

function include(file) {
	const element_script = document.createElement("script");
	element_script.src = includePath + file;
	document.body.prepend(element_script);
	return;
}