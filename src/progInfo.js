const urlParams = new URLSearchParams(window.location.search);

const programName = "BlockBreakJS"

customSettings = false;

if (urlParams.has("width")) {
	renderWidth = parseInt(urlParams.get("width"));
	customSettings = true;
} else {
	renderWidth = 640;
}
if (urlParams.has("height")) {
	renderHeight = parseInt(urlParams.get("height"));
	customSettings = true;
} else {
	renderHeight = 472;
}

const fontHeight = 16;

if (urlParams.has("playerSpeed")) {
	playerSpeed = parseInt(urlParams.get("playerSpeed"));
	customSettings = true;
} else {
	playerSpeed = Math.round(renderHeight / 59);
}
if (urlParams.has("playerWidth")) {
	playerWidth = parseInt(urlParams.get("playerWidth"));
	customSettings = true;
} else {
	playerWidth = Math.round(renderWidth / 40);
}
if (urlParams.has("playerHeight")) {
	playerHeight = parseInt(urlParams.get("playerHeight"));
	customSettings = true;
} else {
	playerHeight = Math.round(renderWidth / 40);
}
const playerStartX = Math.round((renderWidth / 2) - (playerWidth / 2));
const playerStartY = renderHeight - (playerHeight * 3);
if (playerSpeed < 1) {
	playerSpeed = 1;
}
if (playerWidth < 1) {
	playerWidth = 1;
}
if (playerHeight < 1) {
	playerHeight = 1;
}

const screenEdgeUp = 0;
const screenEdgeDown = renderHeight - playerHeight;
const screenEdgeLeft = 0;
const screenEdgeRight = renderWidth - playerWidth;

const touchDeadZone = 32;

if (urlParams.has("timerSpeed")) {
	timerSpeed = parseFloat(urlParams.get("timerSpeed"));;
	customSettings = true;
} else {
	timerSpeed = 1;
}

if (urlParams.has("maxBlocks")) {
	maxBlocks = parseInt(urlParams.get("maxBlocks"));
	customSettings = true;
} else {
	maxBlocks = 255;
}
if (maxBlocks < 1) {
	maxBlocks = 1;
}

if (urlParams.has("fps")) {
	maxFPS = parseInt(urlParams.get("fps"));;
	customSettings = true;
} else {
	maxFPS = 30;
}