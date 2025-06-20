/* MS-DOS (DJGPP) Implementation */
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <dpmi.h>
#include <pc.h>
#include <sys/movedata.h>
#include <random.h>

#include "entity.h"
#include "progInfo.h"

static void (*main_reset)();

static char running = 1;
static char frameBuffer[RENDER_WIDTH * RENDER_HEIGHT];
static char string[11];
static char increased = 0;
static char *main_timerStart;

static unsigned char k;
static unsigned char oldVideoMode;
static unsigned char keyCode;
static const unsigned char numberSheet[10][FONT_HEIGHT][FONT_WIDTH] = {
	{
		{ 0,0,0,0,0,0,0,0 },
		{ 0,1,1,1,1,0,0,0 },
		{ 1,1,0,0,1,1,0,0 },
		{ 1,1,0,0,1,1,0,0 },
		{ 1,1,0,0,1,1,0,0 },
		{ 1,1,0,0,1,1,0,0 },
		{ 1,1,0,0,1,1,0,0 },
		{ 0,1,1,1,1,0,0,0 },
	},
	{
		{ 0,0,0,0,0,0,0,0 },
		{ 0,0,1,1,0,0,0,0 },
		{ 0,1,1,1,0,0,0,0 },
		{ 1,1,1,1,0,0,0,0 },
		{ 0,0,1,1,0,0,0,0 },
		{ 0,0,1,1,0,0,0,0 },
		{ 0,0,1,1,0,0,0,0 },
		{ 1,1,1,1,1,1,0,0 },
	},
	{
		{ 0,0,0,0,0,0,0,0 },
		{ 0,1,1,1,1,0,0,0 },
		{ 1,1,0,0,1,1,0,0 },
		{ 0,0,0,0,1,1,0,0 },
		{ 0,1,1,1,1,0,0,0 },
		{ 1,1,0,0,0,0,0,0 },
		{ 1,1,0,0,0,0,0,0 },
		{ 1,1,1,1,1,1,0,0 },
	},
	{
		{ 0,0,0,0,0,0,0,0 },
		{ 0,1,1,1,1,0,0,0 },
		{ 1,1,0,0,1,1,0,0 },
		{ 0,0,0,0,1,1,0,0 },
		{ 0,0,1,1,1,0,0,0 },
		{ 0,0,0,0,1,1,0,0 },
		{ 1,1,0,0,1,1,0,0 },
		{ 0,1,1,1,1,0,0,0 },
	},
	{
		{ 0,0,0,0,0,0,0,0 },
		{ 0,0,0,1,1,0,0,0 },
		{ 0,0,1,1,1,0,0,0 },
		{ 0,1,1,1,1,0,0,0 },
		{ 1,1,0,1,1,0,0,0 },
		{ 1,1,1,1,1,1,0,0 },
		{ 0,0,0,1,1,0,0,0 },
		{ 0,0,0,1,1,0,0,0 },
	},
	{
		{ 0,0,0,0,0,0,0,0 },
		{ 1,1,1,1,1,1,0,0 },
		{ 1,1,0,0,0,0,0,0 },
		{ 1,1,0,0,0,0,0,0 },
		{ 1,1,1,1,1,0,0,0 },
		{ 0,0,0,0,1,1,0,0 },
		{ 0,0,0,0,1,1,0,0 },
		{ 1,1,1,1,1,0,0,0 },
	},
	{
		{ 0,0,0,0,0,0,0,0 },
		{ 0,1,1,1,1,0,0,0 },
		{ 1,1,0,0,1,1,0,0 },
		{ 1,1,0,0,0,0,0,0 },
		{ 1,1,1,1,1,0,0,0 },
		{ 1,1,0,0,1,1,0,0 },
		{ 1,1,0,0,1,1,0,0 },
		{ 0,1,1,1,1,0,0,0 },
	},
	{
		{ 0,0,0,0,0,0,0,0 },
		{ 1,1,1,1,1,1,0,0 },
		{ 0,0,0,0,1,1,0,0 },
		{ 0,0,0,0,1,1,0,0 },
		{ 0,0,0,1,1,0,0,0 },
		{ 0,0,0,1,1,0,0,0 },
		{ 0,0,1,1,0,0,0,0 },
		{ 0,0,1,1,0,0,0,0 },
	},
	{
		{ 0,0,0,0,0,0,0,0 },
		{ 0,1,1,1,1,0,0,0 },
		{ 1,1,0,0,1,1,0,0 },
		{ 1,1,0,0,1,1,0,0 },
		{ 0,1,1,1,1,0,0,0 },
		{ 1,1,0,0,1,1,0,0 },
		{ 1,1,0,0,1,1,0,0 },
		{ 0,1,1,1,1,0,0,0 },
	},
	{
		{ 0,0,0,0,0,0,0,0 },
		{ 0,1,1,1,1,0,0,0 },
		{ 1,1,0,0,1,1,0,0 },
		{ 1,1,0,0,1,1,0,0 },
		{ 0,1,1,1,1,1,0,0 },
		{ 0,0,0,0,1,1,0,0 },
		{ 1,1,0,0,1,1,0,0 },
		{ 0,1,1,1,1,0,0,0 },
	}
};
static const unsigned char colorPalette[16][3] = {
	{ 0x00, 0x00, 0x00 },
	{ 0x00, 0x00, 0xAA },
	{ 0x00, 0xAA, 0x00 },
	{ 0x00, 0xAA, 0xAA },
	{ 0xAA, 0x00, 0x00 },
	{ 0xAA, 0x00, 0xAA },
	{ 0xAA, 0x55, 0x00 },
	{ 0xAA, 0xAA, 0xAA },
	{ 0x55, 0x55, 0x55 },
	{ 0x55, 0x55, 0xFF },
	{ 0x55, 0xFF, 0x55 },
	{ 0x55, 0xFF, 0xFF },
	{ 0xFF, 0x55, 0x55 },
	{ 0xFF, 0x55, 0xFF },
	{ 0xFF, 0xFF, 0x55 },
	{ 0xFF, 0xFF, 0xFF }
};
static unsigned char colorPaletteMap[4][4][4];
static unsigned char currentColor;

static unsigned short i, j;

static entity_t *main_player;

static uclock_t lastTime;

static unsigned char getVideoMode() {
	__dpmi_regs r;
	r.h.ah = 0x0F;
	__dpmi_int(0x10, &r);
	return r.h.al;
}

static void setVideoMode(unsigned char videoMode) {
	__dpmi_regs r;
	r.x.ax = videoMode;
	__dpmi_int(0x10, &r);
	return;
}

static void handleInput() {
	keyCode = inportb(0x60);
	
	if (keyCode & 0x80) {
		increased = 0;
	} else {
		if (!increased) {
			random_increase();
			increased = 1;
		}
		switch (keyCode & 0x7F) {
			case 72: /* Up */
				main_player->direction = ENTITY_DIR_UP;
				*main_timerStart = 1;
				break;
			case 80: /* Down */
				main_player->direction = ENTITY_DIR_DOWN;
				*main_timerStart = 1;
				break;
			case 75: /* Left */
				main_player->direction = ENTITY_DIR_LEFT;
				*main_timerStart = 1;
				break;
			case 77: /* Right */
				main_player->direction = ENTITY_DIR_RIGHT;
				*main_timerStart = 1;
				break;
			case 28: /* Reset */
				main_reset();
				break;
			case 1: /* Quit */
				running = 0;
				break;
			default:
				break;
		}
	}
	return;
}

/* Drawing */
void impl_setColor(
	unsigned char red,
	unsigned char green,
	unsigned char blue
) {
	currentColor = colorPaletteMap[
		red / 85
	][
		green / 85
	][
		blue / 85
	];
	return;
}

void impl_drawNumber(
	short x, short y,
	unsigned int number
) {
	sprintf(string, "%u", number);
	for (k = 0; k < strlen(string); k++) {
		for (i = 0; i < FONT_HEIGHT; i++) {
			for (j = 0; j < FONT_WIDTH; j++) {
				if (numberSheet[string[k] - 48][i][j]) {
					frameBuffer[(y + i) * RENDER_WIDTH + ((x + j) + (k * FONT_WIDTH))] = numberSheet[string[k] - 48][i][j] * currentColor;
				}
			}
		}
	}
	return;
}

void impl_drawFillRect(
	short x, short y,
	unsigned short width, unsigned short height
) {
	for (i = 0; i < height; i++) {
		for (j = 0; j < width; j++) {
			if ((x + j) > -1 && (y + i) > -1) {
				frameBuffer[(y + i) * RENDER_WIDTH + (x + j)] = currentColor;
			}
		}
	}
	return;
}

/* Misc. */
void impl_loopStart() {
	memset(frameBuffer, 0, sizeof(frameBuffer));
	return;
}

void impl_loopEnd() {
	dosmemput(frameBuffer, RENDER_WIDTH * RENDER_HEIGHT, 0xA0000);
	return;
}

void impl_init(
	int argc, char *argv[],
	char *timerStart, entity_t *player,
	void (*reset)(), void (*draw)()
) {
	oldVideoMode = getVideoMode();
	setVideoMode(0x13);
	
	memset(frameBuffer, 0, sizeof(frameBuffer));
	
	for (i = 0; i < 16; i++) {
		colorPaletteMap[
			colorPalette[i][0] / 85
		][
			colorPalette[i][1] / 85
		][
			colorPalette[i][2] / 85
		] = i;
	}
	
	main_timerStart = timerStart;
	main_player = player;
	main_reset = reset;
	while (running) {
		lastTime = uclock();
		
		draw();
		handleInput();
		
		while (uclock() < lastTime + (UCLOCKS_PER_SEC / MAX_FPS)) {
			handleInput();
		}
	}
	
	setVideoMode(oldVideoMode);
	printf(PROGRAM_NAME " v" PROGRAM_VERSION " - MS-DOS (DJGPP)\n");
	return;
}