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
	[ 0x00, 0x00, 0xAA ],
	[ 0x00, 0xAA, 0x00 ],
	[ 0x00, 0xAA, 0xAA ],
	[ 0xAA, 0x00, 0x00 ],
	[ 0xAA, 0x00, 0xAA ],
	[ 0xAA, 0x55, 0x00 ],
	[ 0x55, 0x55, 0xFF ],
	[ 0x55, 0xFF, 0x55 ],
	[ 0x55, 0xFF, 0xFF ],
	[ 0xFF, 0x55, 0x55 ],
	[ 0xFF, 0x55, 0xFF ],
	[ 0xFF, 0xFF, 0x55 ]
];

function lessThanSet(vari, value) {
	if (vari < value) {
		return value;
	} else {
		return vari;
	}
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
		case 83: /* S */
			sImpl_take = 1;
			break;
		default:
			break;
	}
}

function generateLevel(level) {
	blockCount = 0;
	blocks = [];
	
	if (level > 0) {
		blockSize = [
			Math.round(element_canvas.width / level),
			Math.round(element_canvas.height / (level * 1.5))
		];
		
		blockSize[0] = lessThanSet(blockSize[0], 1);
		blockSize[1] = lessThanSet(blockSize[1], 1);
		
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
		0xFF, 0xFF, 0xFF,
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
	impl_loopStart();
	
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
	
	impl_setColor(0xFF, 0xFF, 0xFF);
	if (customSettings) {
		if (TIMER_SPEED > 0) {
			impl_drawNumber(0, (RENDER_HEIGHT - FONT_HEIGHT * 3) - 1, parseInt(timer));
		}
		impl_drawNumber(0, (RENDER_HEIGHT - FONT_HEIGHT) - 1, score);
		impl_setColor(0xFF, 0xFF, 0xC0);
		/* In the JavaScript version, `impl_drawNumber` can draw text as well */
		impl_drawNumber(0, 0, "Custom Settings");
	} else {
		impl_drawNumber(0, (RENDER_HEIGHT - FONT_HEIGHT * 4) - 1, timer);
		impl_drawNumber(0, (RENDER_HEIGHT - FONT_HEIGHT * 2) - 1, score);
		impl_drawNumber(0, (RENDER_HEIGHT - FONT_HEIGHT) - 1, highScore);
	}
	
	if (timerStart && TIMER_SPEED > 0) {
		timer -= TIMER_SPEED;
	}
	
	if (timer <= 0) {
		if (score > highScore && !customSettings) {
			highScore = score;
			hssImpl_set(highScore);
		}
		reset();
	}
	
	sImpl_end();
	return;
}

function main() {
	hssImpl_open();
	if (!customSettings) {
		highScore = hssImpl_get();
	}
	
	init();
	
	context.font = FONT_HEIGHT + "px Fixedsys";
	
	loop = setInterval(draw, 1000 / MAX_FPS);
	return;
}

main();