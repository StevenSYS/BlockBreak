#include "impl.h"
#include "input.h"
#include "macros.h"
#include "random.h"
#include "entity.h"
#include "hssImpl.h"
#include "progInfo.h"

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

static object_t blocks[MAX_LEVEL][MAX_LEVEL];

char main_timerStart = 0;

entity_t main_player;

static void generateLevel(unsigned char level) {
	unsigned char x, y;
	unsigned char x2 = 0;
	unsigned char y2 = 0;
	unsigned char randomColor = 0;
	unsigned char prevRandomColor;
	unsigned short blockSize[2];
	
	blockCount = 0;
	
	if (level > 0 && level <= MAX_LEVEL) {
		blockSize[0] = (unsigned short)(RENDER_WIDTH / level);
		blockSize[1] = (unsigned short)(RENDER_HEIGHT / (level * 1.5));
		
		LESSTHANSET(blockSize[0], 1);
		LESSTHANSET(blockSize[1], 1);
		
		if (blockSize[0] < PLAYER_WIDTH) {
			x2 = PLAYER_WIDTH - blockSize[0];
		}
		
		if (blockSize[1] < PLAYER_HEIGHT) {
			y2 = PLAYER_HEIGHT - blockSize[1];
		}
		
		for (y = 0; y < level; y++) {
			prevRandomColor = randomColor;
			
			while (randomColor == prevRandomColor) {
				randomColor = random_get();
			}
			
			for (x = 0; x < level; x++) {
				if (
					(((x * blockSize[0]) + x2) < RENDER_WIDTH) &&
					(((y * blockSize[1]) + y2) < RENDER_HEIGHT)
				) {
					blockCount++;
					object_init(
						&blocks[x][y],
						colors[randomColor][0], colors[randomColor][1], colors[randomColor][2],
						blockSize[0], blockSize[1],
						(x * blockSize[0]) + x2, (y * blockSize[1]) + y2,
						1
					);
				}
			}
		}
	}
	return;
}

static void init() {
	unsigned char x, y;
	
	SAFEADD(timer, level * 35, 0xFFFF);
	
	for (y =  0; y < MAX_LEVEL; y++) {
		for (x = 0; x < MAX_LEVEL; x++) {
			blocks[x][y].visible = 0;
		}
	}
	
	entity_init(
		&main_player,
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

void main_reset() {
	timer = 0;
	level = 1;
	score = 0;
	main_timerStart = 0;
	init();
	return;
}

static void draw() {
	unsigned char x, y;
	
	impl_loopStart();
	
	if (!blockCount) {
		SAFEADD(score, timer / 4, 0xFFFFFFFF);
		SAFEADD(level, 1, MAX_LEVEL);
		init();
	}
	
	if (main_player.object.position[1] <= SCREEN_EDGE_UP) {
		main_player.direction = ENTITY_DIR_DOWN;
		main_player.object.position[1] = SCREEN_EDGE_UP;
	} else if (main_player.object.position[1] >= SCREEN_EDGE_DOWN) {
		main_player.direction = ENTITY_DIR_UP;
		main_player.object.position[1] = SCREEN_EDGE_DOWN;
	} else if (main_player.object.position[0] <= SCREEN_EDGE_LEFT) {
		main_player.direction = ENTITY_DIR_RIGHT;
		main_player.object.position[0] = SCREEN_EDGE_LEFT;
	} else if (main_player.object.position[0] >= SCREEN_EDGE_RIGHT) {
		main_player.direction = ENTITY_DIR_LEFT;
		main_player.object.position[0] = SCREEN_EDGE_RIGHT;
	}
	
	entity_draw(&main_player);
	for (y =  0; y < level; y++) {
		for (x = 0; x < level; x++) {
			if (blocks[x][y].visible) {
				object_draw(&blocks[x][y]);
				if (object_collision(
					&main_player.object,
					&blocks[x][y]
				)) {
					blocks[x][y].visible = 0;
					blockCount--;
					SAFEADD(score, 10, 0xFFFFFFFF);
				}
			}
		}
	}
	
	if (main_timerStart) {
		timer--;
	}
	
	if (!timer) {
		if (score > highScore) {
			highScore = score;
			hssImpl_set(highScore);
		}
		main_reset();
	}
	
	impl_setColor(0xFF, 0xFF, 0xFF);
	impl_drawNumber(0, RENDER_HEIGHT - (FONT_HEIGHT * 4), timer);
	
	impl_drawNumber(0, RENDER_HEIGHT - (FONT_HEIGHT * 2), score);
	impl_drawNumber(0, RENDER_HEIGHT - FONT_HEIGHT, highScore);
	
	impl_loopEnd();
	return;
}

int main(int argc, char *argv[]) {
	hssImpl_open();
	highScore = hssImpl_get();
	
	init();
	
	impl_init(
		argc, argv,
		&draw
	);
	
	hssImpl_close();
	return 0;
}