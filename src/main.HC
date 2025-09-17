#exe {
	Cd(__DIR__);
};

#include "misc.HC"
#include "random.HC"
#include "entity.HC"
#include "progInfo.HH"

static Bool timerStart = FALSE;

static U8 randomColors[12] = {
	BLUE,
	GREEN,
	CYAN,
	RED,
	PURPLE,
	BROWN,
	LTBLUE,
	LTGREEN,
	LTCYAN,
	LTRED,
	LTPURPLE,
	YELLOW
};
static U8 level = 1;

static I16 sc;

static U16 blockCount = 0;
static U16 timer = 0;

static U32 score = 0;

static CDC *dc = DCAlias;

static object_t blocks[MAX_LEVEL][MAX_LEVEL];

static entity_t player;

RegDft(PROGRAM_NAME,"U32 highScore = 0;\n");
RegExe(PROGRAM_NAME);

U0 generateLevel(U8 level) {
	U8 x, y;
	U8 x2 = 0;
	U8 y2 = 0;
	U8 randomColor = 0;
	U8 prevRandomColor;
	U16 blockSize[2];
	
	blockCount = 0;
	
	if (level > 0 && level <= MAX_LEVEL) {
		blockSize[0] = RENDER_WIDTH / level;
		blockSize[1] = RENDER_HEIGHT / (level * 1.5);
		
		lessThanSetU16(&blockSize[0], 1);
		lessThanSetU16(&blockSize[1], 1);
		
		if (blockSize[0] < PLAYER_WIDTH) {
			x2 = PLAYER_WIDTH - blockSize[0];
		}
		
		if (blockSize[1] < PLAYER_HEIGHT) {
			y2 = PLAYER_HEIGHT - blockSize[1];
		}
		
		for (y = 0; y < level; y++) {
			prevRandomColor = randomColor;
			
			while (randomColor == prevRandomColor) {
				randomColor = randomColors[random_get()];
			}
			
			for (x = 0; x < level; x++) {
				if (
					(((x * blockSize[0]) + x2) < RENDER_WIDTH) &&
					(((y * blockSize[1]) + y2) < RENDER_HEIGHT)
				) {
					blockCount++;
					object_init(
						&blocks[y][x],
						randomColor,
						blockSize[0], blockSize[1],
						(x * blockSize[0]) + x2, (y * blockSize[1]) + y2,
						TRUE
					);
				}
			}
		
		}
	}
	return;
}

U0 init() {
	U8 x, y;
	
	safeAddU16(&timer, level * 35, 0xFFFF);
	
	for (y = 0; y < MAX_LEVEL; y++) {
		for (x = 0; x < MAX_LEVEL; x++) {
			blocks[x][y].visible = FALSE;
		}
	}
	
	entity_init(
		&player,
		WHITE,
		ENTITY_DIR_NONE,
		PLAYER_WIDTH,
		PLAYER_HEIGHT,
		PLAYER_START_X,
		PLAYER_START_Y,
		PLAYER_SPEED,
		TRUE
	);
	
	generateLevel(level);
	return;
}

U0 reset() {
	timer = 0;
	level = 1;
	score = 0;
	timerStart = FALSE;
	init();
	return;
}

U0 draw(CTask *, CDC *dc) {
	U8 x, y;
	
	if (!blockCount) {
		safeAddU32(&score, timer / 4, 0xFFFFFFFF);
		safeAddU8(&level, 1, MAX_LEVEL);
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
	
	entity_draw(dc, &player);
	for (y = 0; y < level; y++) {
		for (x = 0; x < level; x++) {
			if (blocks[x][y].visible) {
				object_draw(dc, &blocks[x][y]);
				if (object_collision(&player.object, &blocks[x][y])) {
					blocks[x][y].visible = FALSE;
					blockCount--;
					safeAddU32(&score, 10, 0xFFFFFFFF);
				}
			}
		}
	}
	
	dc->color = WHITE;
	GrPrint(dc, 0, RENDER_HEIGHT - (FONT_HEIGHT * 4), "%d", timer);
	GrPrint(dc, 0, RENDER_HEIGHT - (FONT_HEIGHT * 2), "%d", score);
	GrPrint(dc, 0, RENDER_HEIGHT - FONT_HEIGHT, "%d", highScore);
	
	if (timerStart) {
		timer--;
	}
	
	if (!timer) {
		if (score > highScore) {
			RegWrite(PROGRAM_NAME, "U32 highScore = %d;\n", score);
			highScore = score;
		}
		reset();
	}
	return;
}

U0 main() {
	init();
	
	SettingsPush();
	
	MenuPush(
		"File {"
		"	Abort(,CH_SHIFT_ESC);"
		"	Quit(,CH_ESC);"
		"}"
		"Controls {"
		"	Up(,,SC_CURSOR_UP);"
		"	Down(,,SC_CURSOR_DOWN);"
		"	Left(,,SC_CURSOR_LEFT);"
		"	Right(,,SC_CURSOR_RIGHT);"
		"	Restart(,,SC_ENTER);"
		"}"
	);
	
	WinMax();
	WinBorder();
	
	DocCursor();
	DocClear();
	
	Fs->text_attr = BLACK;
	Fs->draw_it = &draw;
	
	while (TRUE) {
		switch (GetKey(&sc)) {
			default:
				random_index++;
				switch (sc.u8[0]) {
					case SC_CURSOR_UP:
						player.direction = ENTITY_DIR_UP;
						timerStart = TRUE;
						break;
					case SC_CURSOR_DOWN:
						player.direction = ENTITY_DIR_DOWN;
						timerStart = TRUE;
						break;
					case SC_CURSOR_LEFT:
						player.direction = ENTITY_DIR_LEFT;
						timerStart = TRUE;
						break;
					case SC_CURSOR_RIGHT:
						player.direction = ENTITY_DIR_RIGHT;
						timerStart = TRUE;
						break;
					case SC_ENTER:
						reset();
						break;
				}
				break;
			case CH_ESC:
			case CH_SHIFT_ESC:
				goto unInit;
		}
	}
	
	unInit:
	DocClear();
	
	DCClear();
	DCFill();
	DCDel(dc);
	
	MenuPop();
	SettingsPop();

	Print(PROGRAM_NAME " v" PROGRAM_VERSION "\n");
	return;
}

main();