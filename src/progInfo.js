const urlParams = new URLSearchParams(window.location.search);

const programName = "BlockBreakJS"

customSettings = false;

/* - Render - */
if (urlParams.has("width")) {
	RENDER_WIDTH = parseInt(urlParams.get("width"));
	customSettings = true;
} else {
	RENDER_WIDTH = 640;
}
if (urlParams.has("height")) {
	RENDER_HEIGHT = parseInt(urlParams.get("height"));
	customSettings = true;
} else {
	RENDER_HEIGHT = 472;
}
if (RENDER_WIDTH < 1) {
	RENDER_WIDTH = 1;
} else if (RENDER_WIDTH > screen.width) {
	RENDER_WIDTH = screen.width;
}
if (RENDER_HEIGHT < 1) {
	RENDER_HEIGHT = 1;
} else if (RENDER_HEIGHT > screen.height) {
	RENDER_HEIGHT = screen.height;
}

/* Player */
if (urlParams.has("PLAYER_SPEED")) {
	PLAYER_SPEED = parseInt(urlParams.get("PLAYER_SPEED"));
	customSettings = true;
} else {
	PLAYER_SPEED = Math.round(RENDER_HEIGHT / 59);
}
if (urlParams.has("PLAYER_WIDTH")) {
	PLAYER_WIDTH = parseInt(urlParams.get("PLAYER_WIDTH"));
	customSettings = true;
} else {
	PLAYER_WIDTH = Math.round(RENDER_WIDTH / 40);
}
if (urlParams.has("PLAYER_HEIGHT")) {
	PLAYER_HEIGHT = parseInt(urlParams.get("PLAYER_HEIGHT"));
	customSettings = true;
} else {
	PLAYER_HEIGHT = Math.round(RENDER_WIDTH / 40);
}
/* Start */
const PLAYER_START_X = Math.round((RENDER_WIDTH / 2) - (PLAYER_WIDTH / 2));
const PLAYER_START_Y = RENDER_HEIGHT - (PLAYER_HEIGHT * 3);
/* Safe Guards */
if (PLAYER_SPEED < 1) {
	PLAYER_SPEED = 1;
}
if (PLAYER_WIDTH < 1) {
	PLAYER_WIDTH = 1;
} else if (PLAYER_WIDTH > RENDER_WIDTH) {
	PLAYER_WIDTH = RENDER_WIDTH;
}
if (PLAYER_HEIGHT < 1) {
	PLAYER_HEIGHT = 1;
} else if (PLAYER_HEIGHT > RENDER_HEIGHT) {
	PLAYER_HEIGHT = RENDER_HEIGHT;
}

/* - Font - */
const FONT_HEIGHT = 16;

/* - Screen - */

/* Edge */
const SCREEN_EDGE_UP = 0;
const SCREEN_EDGE_DOWN = RENDER_HEIGHT - PLAYER_HEIGHT;
const SCREEN_EDGE_LEFT = 0;
const SCREEN_EDGE_RIGHT = RENDER_WIDTH - PLAYER_WIDTH;

/* - Touch - */
if (urlParams.has("TOUCH_DEAD_ZONE")) {
	TOUCH_DEAD_ZONE = parseFloat(urlParams.get("TOUCH_DEAD_ZONE"));;
} else {
	TOUCH_DEAD_ZONE = 32;
}

if (urlParams.has("TIMER_SPEED")) {
	TIMER_SPEED = parseFloat(urlParams.get("TIMER_SPEED"));;
	customSettings = true;
} else {
	TIMER_SPEED = 1;
}

/* - Max - */
if (urlParams.has("MAX_BLOCKS")) {
	MAX_BLOCKS = parseInt(urlParams.get("MAX_BLOCKS"));
	customSettings = true;
} else {
	MAX_BLOCKS = 255;
}
if (MAX_BLOCKS < 1) {
	MAX_BLOCKS = 1;
}

if (urlParams.has("fps")) {
	MAX_FPS = parseInt(urlParams.get("fps"));;
	customSettings = true;
} else {
	MAX_FPS = 30;
}