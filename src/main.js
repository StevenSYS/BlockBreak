const element_canvas = document.createElement("canvas");
const context = element_canvas.getContext("2d");

element_canvas.width = RENDER_WIDTH;
element_canvas.height = RENDER_HEIGHT;
element_canvas.style.maxWidth = RENDER_WIDTH + "px";
element_canvas.style.maxHeight = RENDER_HEIGHT + "px";
if (!urlParams.has("noBorder")) {
	element_canvas.classList.add("border");
}

document.body.appendChild(element_canvas);
document.addEventListener("keydown", input);
document.addEventListener("touchstart", touchStart);
document.addEventListener("touchend", touchEnd);

var oldRandomColor = 13;
var randomColor = 13;
var level = 1;
var blockCount = 0;
var timer = 0;
var score = 0;
var highScore = 0;
var timerStart = false;
var player;
var blocks = [];

const randomColors = [
	[ "0", "0", "A" ],
	[ "0", "A", "0" ],
	[ "0", "A", "A" ],
	[ "A", "0", "0" ],
	[ "A", "0", "A" ],
	[ "A", "5", "0" ],
	[ "5", "5", "F" ],
	[ "5", "F", "5" ],
	[ "5", "F", "F" ],
	[ "F", "5", "5" ],
	[ "F", "5", "F" ],
	[ "F", "F", "5" ]
];

/* Get High Score */
if (
	localStorage.getItem(programName + "_highScore") != undefined
	&&
	!customSettings
) {
	highScore = parseInt(localStorage.getItem(programName + "_highScore"));
}

/* Touch Input */
var touch_startX, touch_deltaX;
var touch_startY, touch_deltaY;

function toPositive(number) {
	if (number < 0) {
		return -number;
	} else {
		return number;
	}
}

function touchStart(event) {
	for (const touch of event.changedTouches) {
		touch_startY = touch.pageY;
		touch_startX = touch.pageX;
	}
	return;
}

function touchEnd(event) {
	event.preventDefault();
	for (const touch of event.changedTouches) {
		touch_deltaX = touch.pageX - touch_startX;
		touch_deltaY = touch.pageY - touch_startY;
		touch_positiveX = toPositive(touch_deltaX);
		touch_positiveY = toPositive(touch_deltaY);
		
		if (
			touch_deltaY < -TOUCH_DEAD_ZONE
			&&
			touch_deltaY < -touch_positiveX
		) {
			input({ keyCode: 38 }); /* Up */
		} else if (
			touch_deltaY > TOUCH_DEAD_ZONE
			&&
			touch_deltaY > touch_positiveX
		) {
			input({ keyCode: 40 }); /* Down */
		}
		
		if (
			touch_deltaX < -TOUCH_DEAD_ZONE
			&&
			touch_deltaX < -touch_positiveY
		) {
			input({ keyCode: 37 }); /* Left */
		} else if (
			touch_deltaX > TOUCH_DEAD_ZONE
			&&
			touch_deltaX > touch_positiveY
		) {
			input({ keyCode: 39 }); /* Right */
		}
	}
	return;
}

/* Keyboard Input */
function input(event) {
	random_increase();
	switch (event.keyCode) {
		case 38: /* Up */
			player.direction = directions.UP;
			timerStart = true;
			break;
		case 40: /* Down */
			player.direction = directions.DOWN;
			timerStart = true;
			break;
		case 37: /* Left */
			player.direction = directions.LEFT;
			timerStart = true;
			break;
		case 39: /* Right */
			player.direction = directions.RIGHT;
			timerStart = true;
			break;
		case 13: /* Enter */
			reset();
			break;
		default:
			break;
	}
}

function generateLevel(level) {
	blockCount = 0;
	blocks = [];
	
	if (level) {
		blockSize = [
			Math.round(element_canvas.width / level),
			Math.round(element_canvas.height / (level * 1.5))
		];
		
		for (var y = 0; y < level; y++) {
			oldRandomColor = randomColor;
			
			while (randomColor == oldRandomColor) {
				randomColor = random_get();
			}
			
			for (var x = 0; x < level; x++) {
				if ((x * blockSize[0] < element_canvas.width) && (y * blockSize[1] < element_canvas.height)) {
					blockCount++;
					blocks.push(new entity(
						randomColors[randomColor][0], randomColors[randomColor][1], randomColors[randomColor][2],
						directions.NONE,
						blockSize[0], blockSize[1],
						x * blockSize[0], y * blockSize[1],
						0,
						true
					));
				}
			}
		
		}
	}
	return;
}

function init() {
	if (timer + (level * 35) > 0xFFFF) {
		timer = 0xFFFF;
	} else {
		timer += level * 35;
	}
	
	player = new entity(
		"F", "F", "F",
		directions.NONE,
		PLAYER_WIDTH, PLAYER_HEIGHT,
		PLAYER_START_X, PLAYER_START_Y,
		PLAYER_SPEED,
		true
	);
	
	generateLevel(level);
	return;
}

function reset() {
	timer = 0;
	level = 1;
	score = 0;
	timerStart = false;
	init();
	return;
}

function draw() {
	context.clearRect(0, 0, element_canvas.width, element_canvas.height);
	
	context.fillStyle = "#000";
	context.fillRect(0, 0, element_canvas.width, element_canvas.height);
	
	if (!blockCount) {
		if (score + (timer / 4) > 0xFFFFFFFF) {
			score = 0xFFFFFFFF;
		} else {
			score += Math.round(timer / 4);
		}
		
		if (level < MAX_BLOCKS) {
			level++;
		}
		init();
	}
	
	if (player.position[1] <= SCREEN_EDGE_UP) {
		player.direction = directions.DOWN;
		player.position[1] = SCREEN_EDGE_UP;
	} else if (player.position[1] >= SCREEN_EDGE_DOWN) {
		player.direction = directions.UP;
		player.position[1] = SCREEN_EDGE_DOWN;
	} else if (player.position[0] <= SCREEN_EDGE_LEFT) {
		player.direction = directions.RIGHT;
		player.position[0] = SCREEN_EDGE_LEFT;
	} else if (player.position[0] >= SCREEN_EDGE_RIGHT) {
		player.direction = directions.LEFT;
		player.position[0] = SCREEN_EDGE_RIGHT;
	}	
	
	player.draw(context, true);
	
	for (i in blocks) {
		if (blocks[i].visible) {
			blocks[i].draw(context, false);
			if (player.collision(blocks[i])) {
				blocks[i].visible = false;
				blockCount--;
				score += 10;
			}
		}
	}
	
	context.fillStyle = "#FFF";i
	if (customSettings) {
		if (TIMER_SPEED > 0) {
			context.fillText(parseInt(timer), 0, (RENDER_HEIGHT - FONT_HEIGHT) - 1);
		}
		context.fillText(score, 0, RENDER_HEIGHT - 1);
		context.fillStyle = "#FFFFC0";
		context.fillText("Custom Settings", 0, FONT_HEIGHT - 1);
	} else {
		context.fillText(parseInt(timer), 0, (RENDER_HEIGHT - FONT_HEIGHT * 3) - 1);
		context.fillText(score, 0, (RENDER_HEIGHT - FONT_HEIGHT) - 1);
		context.fillText(highScore, 0, RENDER_HEIGHT - 1);
	}
	
	if (timerStart && TIMER_SPEED > 0) {
		timer -= TIMER_SPEED;
	}
	
	if (timer <= 0) {
		if (score > highScore && !customSettings) {
			highScore = score;
			localStorage.setItem(programName + "_highScore", highScore);
		}
		reset();
	}
	return;
}

function main() {
	init();
	
	context.font = FONT_HEIGHT + "px Fixedsys";
	
	loop = setInterval(draw, 1000 / MAX_FPS);
	return;
}

main();