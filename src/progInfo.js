const urlParams = new URLSearchParams(window.location.search);

const programName = "BlockBreakJS"

highScoreSave = true;

if (urlParams.has("width")) {
	renderWidth = parseInt(urlParams.get("width"));
	highScoreSave = false;
} else {
	renderWidth = 640;
}
if (urlParams.has("height")) {
	renderHeight = parseInt(urlParams.get("height"));
	highScoreSave = false;
} else {
	renderHeight = 472;
}

const fontHeight = 16;

if (urlParams.has("playerSpeed")) {
	playerSpeed = parseInt(urlParams.get("playerSpeed"));
	highScoreSave = false;
} else {
	playerSpeed = Math.round(renderHeight / 59);
}
if (urlParams.has("playerWidth")) {
	playerWidth = parseInt(urlParams.get("playerWidth"));
	highScoreSave = false;
} else {
	playerWidth = Math.round(renderWidth / 40);
}
if (urlParams.has("playerHeight")) {
	playerHeight = parseInt(urlParams.get("playerHeight"));
	highScoreSave = false;
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

if (urlParams.has("maxBlocks")) {
	maxBlocks = parseInt(urlParams.get("maxBlocks"));
	highScoreSave = false;
} else {
	maxBlocks = 255;
}
if (maxBlocks < 1) {
	maxBlocks = 1;
}
const maxFPS = 30;