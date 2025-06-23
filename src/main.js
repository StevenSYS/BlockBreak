const element_canvas = document.createElement("canvas");
const context = element_canvas.getContext("2d");

element_canvas.width = renderWidth;
element_canvas.height = renderHeight;
element_canvas.style.maxWidth = renderWidth + "px";
element_canvas.style.maxHeight = renderHeight + "px";

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
if (localStorage.getItem(programName + "_highScore") != undefined) {
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
			touch_deltaY < -touchDeadZone
			&&
			touch_deltaY < -touch_positiveX
		) {
			input({ keyCode: 38 }); /* Up */
		} else if (
			touch_deltaY > touchDeadZone
			&&
			touch_deltaY > touch_positiveX
		) {
			input({ keyCode: 40 }); /* Down */
		}
		
		if (
			touch_deltaX < -touchDeadZone
			&&
			touch_deltaX < -touch_positiveY
		) {
			input({ keyCode: 37 }); /* Left */
		} else if (
			touch_deltaX > touchDeadZone
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
	timer += level * 35;
	
	player = new entity(
		"F", "F", "F",
		directions.NONE,
		playerWidth, playerHeight,
		playerStartX, playerStartY,
		playerSpeed,
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
	init(level, player);
	return;
}

function draw() {
	context.clearRect(0, 0, element_canvas.width, element_canvas.height);
	
	context.fillStyle = "#000";
	context.fillRect(0, 0, element_canvas.width, element_canvas.height);
	
	if (!blockCount) {
		score += Math.round(timer / 4);
		if (level < maxBlocks) {
			level++;
		}
		init(level, player);
	}
	
	if (player.position[1] <= screenEdgeUp) {
		player.direction = directions.DOWN;
		player.position[1] = screenEdgeUp;
	} else if (player.position[1] >= screenEdgeDown) {
		player.direction = directions.UP;
		player.position[1] = screenEdgeDown;
	} else if (player.position[0] <= screenEdgeLeft) {
		player.direction = directions.RIGHT;
		player.position[0] = screenEdgeLeft;
	} else if (player.position[0] >= screenEdgeRight) {
		player.direction = directions.LEFT;
		player.position[0] = screenEdgeRight;
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
	
	context.fillStyle = "#FFF";
	context.fillText(timer, 0, (renderHeight - fontHeight * 3) - 1);
	context.fillText(score, 0, (renderHeight - fontHeight) - 1);
	context.fillText(highScore, 0, renderHeight - 1);
	
	if (timerStart) {
		timer--;
	}
	
	if (!timer) {
		if (score > highScore) {
			highScore = score;
			localStorage.setItem(programName + "_highScore", highScore);
		}
		reset();
	}
	return;
}

function main() {
	init();
	
	context.font = fontHeight + "px Fixedsys";
	
	loop = setInterval(draw, 1000 / maxFPS);
	return;
}

main();