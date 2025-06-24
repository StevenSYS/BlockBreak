/* raylib Implementation */
#include <raylib.h>
#include <random.h>
#ifdef ENABLE_SCREENSHOT
	#include <sImpl.h>
#endif

#include "entity.h"
#include "progInfo.h"

static void (*main_reset)();

static char *main_timerStart;

static Color currentColor;

static entity_t *main_player;

static void input() {
	if (GetKeyPressed()) {
		random_increase();
		if (IsKeyPressed(KEY_UP)) {
			main_player->direction = ENTITY_DIR_UP;
			*main_timerStart = 1;
		}
		if (IsKeyPressed(KEY_DOWN)) {
			main_player->direction = ENTITY_DIR_DOWN;
			*main_timerStart = 1;
		}
		if (IsKeyPressed(KEY_LEFT)) {
			main_player->direction = ENTITY_DIR_LEFT;
			*main_timerStart = 1;
		}
		if (IsKeyPressed(KEY_RIGHT)) {
			main_player->direction = ENTITY_DIR_RIGHT;
			*main_timerStart = 1;
		}
		if (IsKeyPressed(KEY_ENTER)) {
			main_reset();
		}
		#ifdef ENABLE_SCREENSHOT
		if (IsKeyPressed(KEY_S)) {
			screenshot_take = 1;
		}
		#endif
	}
	return;
}

/* Drawing */
void impl_setColor(
	unsigned char red,
	unsigned char green,
	unsigned char blue
) {
	currentColor = (Color){ red, green, blue, 0xFF };
	#ifdef ENABLE_SCREENSHOT
	screenshot_setColor(red, green, blue);
	#endif
	return;
}

void impl_drawNumber(
	signed short x, signed short y,
	unsigned int number
) {
	DrawText(
		TextFormat("%u", number),
		x, y,
		FONT_HEIGHT,
		currentColor
	);
	#ifdef ENABLE_SCREENSHOT
	screenshot_number(x, y, number);
	#endif
	return;
}

void impl_drawFillRect(
	signed short x, signed short y,
	unsigned short width, unsigned short height
) {
	DrawRectangle(
		x, y,
		width, height,
		currentColor
	);
	#ifdef ENABLE_SCREENSHOT
	screenshot_fillRect(x, y, width, height);
	#endif
	return;
}

/* Misc. */
void impl_loopStart() {
	BeginDrawing();
	ClearBackground(BLACK);
	#ifdef ENABLE_SCREENSHOT
	screenshot_start();
	#endif
	return;
}

void impl_loopEnd() {
	EndDrawing();
	#ifdef ENABLE_SCREENSHOT
	screenshot_end();
	#endif
	return;
}

void impl_init(
	int argc, char *argv[],
	char *timerStart, entity_t *player,
	void (*reset)(), void (*draw)()
) {
	InitWindow(RENDER_WIDTH, RENDER_HEIGHT, PROGRAM_NAME " v" PROGRAM_VERSION " - raylib");
	
	SetTargetFPS(MAX_FPS);
	
	main_timerStart = timerStart;
	main_player = player;
	main_reset = reset;
	
	while (!WindowShouldClose()) {
		input();
		draw();
	}
	
	CloseWindow();
	return;
}