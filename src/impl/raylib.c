/* raylib Implementation */
#include <raylib.h>
#include <random.h>
#ifdef ENABLE_SCREENSHOT
	#include <sImpl.h>
#endif

#include "entity.h"
#include "input.h"
#include "progInfo.h"

static Color currentColor;

static void raylibInput() {
	if (GetKeyPressed()) {
		random_index++;
		if (IsKeyPressed(KEY_UP)) {
			input(INPUT_UP);
		}
		if (IsKeyPressed(KEY_DOWN)) {
			input(INPUT_DOWN);
		}
		if (IsKeyPressed(KEY_LEFT)) {
			input(INPUT_LEFT);
		}
		if (IsKeyPressed(KEY_RIGHT)) {
			input(INPUT_RIGHT);
		}
		if (IsKeyPressed(KEY_ENTER)) {
			input(INPUT_RESET);
		}
		#ifdef ENABLE_SCREENSHOT
		if (IsKeyPressed(KEY_S)) {
			input(INPUT_SCREENSHOT);
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
	sImpl_setColor(red, green, blue);
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
	sImpl_number(x, y, number);
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
	sImpl_fillRect(x, y, width, height);
	#endif
	return;
}

/* Misc. */
void impl_loopStart() {
	BeginDrawing();
	ClearBackground(BLACK);
	#ifdef ENABLE_SCREENSHOT
	sImpl_start("raylib");
	#endif
	return;
}

void impl_loopEnd() {
	EndDrawing();
	#ifdef ENABLE_SCREENSHOT
	sImpl_end();
	#endif
	return;
}

void impl_init(
	int argc, char *argv[],
	void (*draw)()
) {
	InitWindow(RENDER_WIDTH, RENDER_HEIGHT, PROGRAM_NAME " v" PROGRAM_VERSION " - raylib");
	
	SetTargetFPS(MAX_FPS);
	
	while (!WindowShouldClose()) {
		raylibInput();
		draw();
	}
	
	CloseWindow();
	return;
}