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
		if (IsKeyPressed(KEY_UP)) {
			input(INPUT_UP);
		} else if (IsKeyPressed(KEY_DOWN)) {
			input(INPUT_DOWN);
		} else if (IsKeyPressed(KEY_LEFT)) {
			input(INPUT_LEFT);
		} else if (IsKeyPressed(KEY_RIGHT)) {
			input(INPUT_RIGHT);
		} else if (IsKeyPressed(KEY_ENTER)) {
			input(INPUT_RESET);
		}
		#ifdef ENABLE_SCREENSHOT
		else if (IsKeyPressed(KEY_S)) {
			input(INPUT_SCREENSHOT);
		}
		#endif
		else {
			input(INPUT_NONE);
		}
	}
	return;
}

/* Drawing */
void impl_setColor(
	const unsigned char red,
	const unsigned char green,
	const unsigned char blue
) {
	currentColor = (Color){ red, green, blue, 0xFF };
	#ifdef ENABLE_SCREENSHOT
	sImpl_setColor(red, green, blue);
	#endif
	return;
}

void impl_drawNumber(
	const signed short x, const signed short y,
	const unsigned int number
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
	const signed short x, const signed short y,
	const unsigned short width, const unsigned short height
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