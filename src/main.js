document.addEventListener("keydown", input);
document.addEventListener("touchstart", touchStart);
document.addEventListener("touchend", touchEnd);

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

/* Touch Input */
var touch_startX, touch_deltaX;
var touch_startY, touch_deltaY;

function toPositive(num) {
	return num > 0 ? num : -num;
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
			player.direction = entity_directions.UP;
			timerStart = true;
			break;
		case 40: /* Down */
			player.direction = entity_directions.DOWN;
			timerStart = true;
			break;
		case 37: /* Left */
			player.direction = entity_directions.LEFT;
			timerStart = true;
			break;
		case 39: /* Right */
			player.direction = entity_directions.RIGHT;
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
	return;
}

function generateLevel(level) {
	var x2 = 0;
	var y2 = 0;
	var randomColor = 0;
	var prevRandomColor = 0;
	
	blockCount = 0;
	blocks = [];
	
	if (level > 0 && level <= MAX_LEVEL) {
		var blockSize = [
			Math.round(element_canvas.width / level),
			Math.round(element_canvas.height / (level * 1.5))
		];
		
		blockSize[0] = lessThan(blockSize[0], 1);
		blockSize[1] = lessThan(blockSize[1], 1);
		
		if (blockSize[0] < PLAYER_WIDTH) {
			x2 = PLAYER_WIDTH - blockSize[0];
		}
		
		if (blockSize[1] < PLAYER_HEIGHT) {
			y2 = PLAYER_HEIGHT - blockSize[1];
		}
		
		for (var y = 0; y < level; y++) {
			prevRandomColor = randomColor;
			
			while (randomColor == prevRandomColor) {
				randomColor = random_get();
			}
			
			for (var x = 0; x < level; x++) {
				if (
					(((x * blockSize[0]) + x2) < element_canvas.width) &&
					(((y * blockSize[1]) + y2) < element_canvas.height)
				) {
					blockCount++;
					blocks.push(new object(
						randomColors[randomColor][0], randomColors[randomColor][1], randomColors[randomColor][2],
						blockSize[0], blockSize[1],
						(x * blockSize[0]) + x2, (y * blockSize[1]) + y2,
						true
					));
				}
			}
		
		}
	}
	return;
}

function init() {
	timer = safeAdd(timer, level * 35, 0xFFFF);
	
	player = new entity(
		0xFF, 0xFF, 0xFF,
		entity_directions.NONE,
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
		score = safeAdd(score, Math.round(timer / 4), 0xFFFFFFFF);
		level = safeAdd(level, 1, MAX_LEVEL);
		init();
	}
	
	if (player.object.position[1] <= SCREEN_EDGE_UP) {
		player.direction = entity_directions.DOWN;
		player.object.position[1] = SCREEN_EDGE_UP;
	} else if (player.object.position[1] >= SCREEN_EDGE_DOWN) {
		player.direction = entity_directions.UP;
		player.object.position[1] = SCREEN_EDGE_DOWN;
	} else if (player.object.position[0] <= SCREEN_EDGE_LEFT) {
		player.direction = entity_directions.RIGHT;
		player.object.position[0] = SCREEN_EDGE_LEFT;
	} else if (player.object.position[0] >= SCREEN_EDGE_RIGHT) {
		player.direction = entity_directions.LEFT;
		player.object.position[0] = SCREEN_EDGE_RIGHT;
	}	
	
	player.draw(context, true);
	
	for (i in blocks) {
		if (blocks[i].visible) {
			blocks[i].draw();
			if (blocks[i].collision(player.object)) {
				blocks[i].visible = false;
				blockCount--;
				score = safeAdd(score, 10, 0xFFFFFFFF);
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
		/* In the JavaScript version, `impl_drawNumber` can draw letters as well */
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