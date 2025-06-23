#exe {
	Cd(__DIR__);
};

#include "random.HC"
#include "entity.HC"
#include "progInfo.HH"

Bool timerStart = FALSE;

U8 randomColors[12] = {
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
U8 i;
U8 j;
U8 oldRandomColor = 13;
U8 randomColor = 13;
U8 level = 1;

I16 sc;

U16 blockSize[2];
U16 blockCount = 0;
U16 timer = 0;

U32 score = 0;

CDC *dc = DCAlias;

entity_t player;
entity_t blocks[MAX_BLOCKS][MAX_BLOCKS];

RegDft(PROGRAM_NAME,"U32 highScore = 0;\n");
RegExe(PROGRAM_NAME);

U0 generateLevel(U8 level) {
	blockCount = 0;
	
	if (level) {
		blockSize[0] = RENDER_WIDTH / level;
		blockSize[1] = RENDER_HEIGHT / (level * 1.5);
		
		for (i = 0; i < level; i++) {
			oldRandomColor = randomColor;
			
			while (randomColor == oldRandomColor) {
				randomColor = randomColors[random_get()];
			}
			
			for (j = 0; j < level; j++) {
				if ((j * blockSize[0] < RENDER_WIDTH) && (i * blockSize[1] < RENDER_HEIGHT)) {
					blockCount++;
					entity_init(
						&blocks[j][i],
						randomColor,
						ENTITY_DIR_NONE,
						blockSize[0], blockSize[1],
						j * blockSize[0], i * blockSize[1],
						0,
						TRUE
					);
				}
			}
		
		}
	}
	return;
}

U0 init(
	U8 level,
	entity_t *player
) {
	timer += level * 35;
	
	entity_init(
		player,
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
	for (i = 0; i < MAX_BLOCKS; i++) {
		for (j = 0; j < MAX_BLOCKS; j++) {
			blocks[j][i].visible = FALSE;
		}
	}
	init(level, &player);
	return;
}

U0 draw(CTask *task, CDC *dc) {
	if (!blockCount) {
		score += timer / 4;
		if (level < MAX_BLOCKS) {
			level++;
		}
		init(level, &player);
	}
	
	if (player.position[1] <= SCREEN_EDGE_UP) {
		player.direction = ENTITY_DIR_DOWN;
		player.position[1] = SCREEN_EDGE_UP;
	} else if (player.position[1] >= SCREEN_EDGE_DOWN) {
		player.direction = ENTITY_DIR_UP;
		player.position[1] = SCREEN_EDGE_DOWN;
	} else if (player.position[0] <= SCREEN_EDGE_LEFT) {
		player.direction = ENTITY_DIR_RIGHT;
		player.position[0] = SCREEN_EDGE_LEFT;
	} else if (player.position[0] >= SCREEN_EDGE_RIGHT) {
		player.direction = ENTITY_DIR_LEFT;
		player.position[0] = SCREEN_EDGE_RIGHT;
	}
	
	entity_draw(dc, &player, TRUE);
	
	for (i = 0; i < level; i++) {
		for (j = 0; j < level; j++) {
			if (blocks[j][i].visible) {
				entity_draw(dc, &blocks[j][i], FALSE);	
				if (entity_collision(&player, &blocks[j][i])) {
					blocks[j][i].visible = FALSE;
					blockCount--;
					score += 10;
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
	init(level, &player);
	
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
	
	dc->color = WHITE;
	GrPrint(dc, 0, 0, PROGRAM_NAME " v" PROGRAM_VERSION);
	
	while (TRUE) {
		switch (GetKey(&sc)) {
			default:
				random_increase();
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
				goto uninit;
		}
	}
	
	uninit:
	DocClear();
	
	DCClear();
	DCFill();
	DCDel(dc);
	
	MenuPop();
	SettingsPop();
	return;
}

main();