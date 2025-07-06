implFile = "canvas";
hssImplFile = "localStorage";
sImplFile = "svg";

if (urlParams.has("impl")) {
	implFile = urlParams.get("impl");
}

if (urlParams.has("hssImpl")) {
	hssImplFile = urlParams.get("hssImpl");
}

if (urlParams.has("sImpl")) {
	sImplFile = urlParams.get("sImpl");
}