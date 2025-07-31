/* citro2d Implementation */
#define _DEFAULT_SOURCE
#include <citro2d.h>
#include <unistd.h>
#include <random.h>
#include <input.h>
#ifdef ENABLE_SCREENSHOT
	#include <sImpl.h>
#endif

#include "entity.h"
#include "progInfo.h"

static char running = 1;

static unsigned int currentColor;
static unsigned int inputDown;

static unsigned long long lastTime;

static C3D_RenderTarget *renderTarget;

static void c2dInput() {
	hidScanInput();
	
	inputDown = hidKeysDown();
	if ((inputDown & KEY_UP) || (inputDown & KEY_X)) {
		input(INPUT_UP);
	}
	if ((inputDown & KEY_DOWN) || (inputDown & KEY_B)) {
		input(INPUT_DOWN);
	}
	if ((inputDown & KEY_LEFT) || (inputDown & KEY_Y)) {
		input(INPUT_LEFT);
	}
	if ((inputDown & KEY_RIGHT) || (inputDown & KEY_A)) {
		input(INPUT_RIGHT);
	}
	if (inputDown & KEY_SELECT) {
		input(INPUT_RESET);
	}
	#ifdef ENABLE_SCREENSHOT
	if (inputDown & (KEY_L |KEY_R)) {
		input(INPUT_SCREENSHOT);
	}
	#endif
	if (inputDown & KEY_START) {
		running = 0;
	}
	return;
}

/* Drawing */
void impl_setColor(
	unsigned char red,
	unsigned char green,
	unsigned char blue
) {
	currentColor = C2D_Color32(red, green, blue, 0xFF);
	#ifdef ENABLE_SCREENSHOT
	sImpl_setColor(red, green, blue);
	#endif
	return;
}

void impl_drawNumber(
	signed short x, signed short y,
	unsigned int number
) {
	printf("\x1b[%i;%iH", (y / FONT_HEIGHT) + 1, (x / FONT_WIDTH) + 1); /* Sets the cursor position */
	printf("\x1b[97m"); /* Sets the foreground color to bright white */
	printf("%u", number);
	printf("\x1b[K"); /* Clears the current line */
	#ifdef ENABLE_SCREENSHOT
	sImpl_number(x, y, number);
	#endif
	return;
}

void impl_drawFillRect(
	signed short x, signed short y,
	unsigned short width, unsigned short height
) {
	C2D_DrawRectSolid(
		x, y, 0,
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
	C3D_FrameBegin(C3D_FRAME_SYNCDRAW);
	C2D_TargetClear(
		renderTarget,
		C2D_Color32(0x00, 0x00, 0x00, 0xFF)
	);
	C2D_SceneBegin(renderTarget);
	#ifdef ENABLE_SCREENSHOT
	sImpl_start("citro2d");
	#endif
	return;
}

void impl_loopEnd() {
	C3D_FrameEnd(0);
	#ifdef ENABLE_SCREENSHOT
	sImpl_end();
	#endif
	return;
}

void impl_init(
	int argc, char *argv[],
	void (*draw)()
) {
	gfxInitDefault();
	C3D_Init(C3D_DEFAULT_CMDBUF_SIZE);
	C2D_Init(C2D_DEFAULT_MAX_OBJECTS);
	C2D_Prepare();
	consoleInit(GFX_BOTTOM, NULL);
	
	renderTarget = C2D_CreateScreenTarget(GFX_TOP, GFX_LEFT);
	
	while (aptMainLoop() && running) {
		lastTime = svcGetSystemTick();
		
		c2dInput();
		draw();
		
		while (svcGetSystemTick() < lastTime + (CPU_TICKS_PER_MSEC * MAX_FPS)) {
			c2dInput();
			usleep(1000);
		}
	}
	
	C2D_Fini();
	C3D_Fini();
	gfxExit();
	return;
}