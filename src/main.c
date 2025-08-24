#include <impl.h>
#include <hssImpl.h>

#include "random.h"
#include "entity.h"
#include "input.h"
#include "progInfo.h"
#ifdef USE_BLOCKSIZELIST
	#include "blockSizeList.h"
#endif

#define LESSTHANSET(_var, _value) \
	if (_var < _value) { \
		_var = _value; \
	}

#define SAFEADD(_var, _value, _max) \
	if ((_var + _value) > _max) { \
		_var = _max; \
	} else { \
		_var += _value; \
	}

static unsigned char level = 1;
static const unsigned char colors[12][3] = {
	{ 0x00, 0x00, 0xAA },
	{ 0x00, 0xAA, 0x00 },
	{ 0x00, 0xAA, 0xAA },
	{ 0xAA, 0x00, 0x00 },
	{ 0xAA, 0x00, 0xAA },
	{ 0xAA, 0x55, 0x00 },
	{ 0x55, 0x55, 0xFF },
	{ 0x55, 0xFF, 0x55 },
	{ 0x55, 0xFF, 0xFF },
	{ 0xFF, 0x55, 0x55 },
	{ 0xFF, 0x55, 0xFF },
	{ 0xFF, 0xFF, 0x55 }
};

static unsigned short blockCount = 0;
static unsigned short timer = 0;

static unsigned int score = 0;
static unsigned int highScore;

static object_t blocks[MAX_BLOCKS][MAX_BLOCKS];

char timerStart = 0;

entity_t player;

void generateLevel(const unsigned char level) {
	unsigned char x, y;
	unsigned char prevRandomColor = 0;
	unsigned char randomColor = 13;
	unsigned short blockSize[2];
	
	blockCount = 0;
	
	if (level > 0) {
		#ifdef USE_BLOCKSIZELIST
		blockSize[0] = blockSizeList[level][0];
		blockSize[1] = blockSizeList[level][1];
		#else
		blockSize[0] = (unsigned short)(RENDER_WIDTH / level);
		blockSize[1] = (unsigned short)(RENDER_HEIGHT / (level * 1.5));
		#endif
		
		LESSTHANSET(blockSize[0], 1);
		LESSTHANSET(blockSize[1], 1);
		
		for (y = 0; y < level; y++) {
			prevRandomColor = randomColor;
			
			while (randomColor == prevRandomColor) {
				randomColor = random_get();
			}
			
			for (x = 0; x < level; x++) {
				if ((x * blockSize[0] < RENDER_WIDTH) && (y * blockSize[1] < RENDER_HEIGHT)) {
					blockCount++;
					object_init(
						&blocks[x][y],
						colors[randomColor][0], colors[randomColor][1], colors[randomColor][2],
						blockSize[0], blockSize[1],
						x * blockSize[0], y * blockSize[1],
						1
					);
				}
			}
		}
	}
	return;
}

void init() {
	SAFEADD(timer, level * 35, 0xFFFF);
	
	entity_init(
		&player,
		0xFF, 0xFF, 0xFF,
		ENTITY_DIR_NONE,
		PLAYER_WIDTH,
		PLAYER_HEIGHT,
		PLAYER_START_X,
		PLAYER_START_Y,
		PLAYER_SPEED,
		1
	);
	
	generateLevel(level);
	return;
}

void reset() {
	unsigned char x, y;
	
	timer = 0;
	level = 1;
	score = 0;
	timerStart = 0;
	for (y =  0; y < MAX_BLOCKS; y++) {
		for (x = 0; x < MAX_BLOCKS; x++) {
			blocks[x][y].visible = 0;
		}
	}
	init();
	return;
}

void draw() {
	unsigned char x, y;
	
	impl_loopStart();
	
	if (!blockCount) {
		SAFEADD(score, timer / 4, 0xFFFFFFFF);
		
		if (level < MAX_BLOCKS) {
			level++;
		}
		init();
	}
	
	if (player.object.position[1] <= SCREEN_EDGE_UP) {
		player.direction = ENTITY_DIR_DOWN;
		player.object.position[1] = SCREEN_EDGE_UP;
	} else if (player.object.position[1] >= SCREEN_EDGE_DOWN) {
		player.direction = ENTITY_DIR_UP;
		player.object.position[1] = SCREEN_EDGE_DOWN;
	} else if (player.object.position[0] <= SCREEN_EDGE_LEFT) {
		player.direction = ENTITY_DIR_RIGHT;
		player.object.position[0] = SCREEN_EDGE_LEFT;
	} else if (player.object.position[0] >= SCREEN_EDGE_RIGHT) {
		player.direction = ENTITY_DIR_LEFT;
		player.object.position[0] = SCREEN_EDGE_RIGHT;
	}
	
	entity_draw(&player);
	for (y =  0; y < level; y++) {
		for (x = 0; x < level; x++) {
			if (blocks[x][y].visible) {
				object_draw(blocks[x][y]);
				if (object_collision(player.object, blocks[x][y])) {
					blocks[x][y].visible = 0;
					blockCount--;
					SAFEADD(score, 10, 0xFFFFFFFF);
				}
			}
		}
	}
	
	if (timerStart) {
		timer--;
	}
	
	if (!timer) {
		if (score > highScore) {
			highScore = score;
			hssImpl_set(highScore);
		}
		reset();
	}
	
	impl_setColor(0xFF, 0xFF, 0xFF);
	impl_drawNumber(0, RENDER_HEIGHT - (FONT_HEIGHT * 4), timer);
	
	impl_drawNumber(0, RENDER_HEIGHT - (FONT_HEIGHT * 2), score);
	impl_drawNumber(0, RENDER_HEIGHT - FONT_HEIGHT, highScore);
	
	impl_loopEnd();
	return;
}

int
#ifdef CUSTOM_MAIN_NAME
CUSTOM_MAIN_NAME
#else
main
#endif
(
	int argc,
	char *argv[]
) {
	hssImpl_open();
	highScore = hssImpl_get();
	
	init();
	
	input_init(
		&reset,
		&timerStart,
		&player
	);
	
	impl_init(
		argc, argv,
		&draw
	);
	
	hssImpl_close();
	return 0;
}