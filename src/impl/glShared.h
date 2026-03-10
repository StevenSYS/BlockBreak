/* Shared OpenGL Stuff */
#ifdef __APPLE
	#include <gl.h>
#else
	#include <GL/gl.h>
#endif
#include <stdio.h>
#include <string.h>

#include "input.h"
#include "entity.h"
#include "random.h"
#include "progInfo.h"

#define LENGTH_STRINT 11

void main_draw();

static GLubyte numberSheetGL[10][(FONT_HEIGHT * 4) + 1];

static void glSharedInit() {
	unsigned char x, y;
	
	const GLubyte numberSheet[10][FONT_HEIGHT] = {
		{ 0x00, 0x78, 0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 0x78 }, /* 0 */
		{ 0x00, 0xFC, 0x30, 0x30, 0x30, 0xF0, 0x70, 0x30 }, /* 1 */
		{ 0x00, 0xFC, 0xC0, 0xC0, 0x78, 0x0C, 0xCC, 0x78 }, /* 2 */
		{ 0x00, 0x78, 0xCC, 0x0C, 0x38, 0x0C, 0xCC, 0x78 }, /* 3 */
		{ 0x00, 0x18, 0x18, 0xFC, 0xD8, 0x78, 0x38, 0x18 }, /* 4 */
		{ 0x00, 0xF8, 0x0C, 0x0C, 0xF8, 0xC0, 0xC0, 0xFC }, /* 5 */
		{ 0x00, 0x78, 0xCC, 0xCC, 0xF8, 0xC0, 0xCC, 0x78 }, /* 6 */
		{ 0x00, 0x30, 0x30, 0x18, 0x18, 0x0C, 0x0C, 0xFC }, /* 7 */
		{ 0x00, 0x78, 0xCC, 0xCC, 0x78, 0xCC, 0xCC, 0x78 }, /* 8 */
		{ 0x00, 0x78, 0xCC, 0x0C, 0x7C, 0xCC, 0xCC, 0x78 }  /* 9 */
	};
	
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glOrtho(0, RENDER_WIDTH, RENDER_HEIGHT, 0, -1, 1);
	
	for (x = 0; x < 10; x++) {
		for (y = 0; y <= FONT_HEIGHT * 4; y++) {
			numberSheetGL[x][y] = 0;
		}
		
		for (y = 0; y <= FONT_HEIGHT * 4; y += 4) {
			numberSheetGL[x][y] = numberSheet[x][y / 4];
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
	glColor3ub(red, green, blue);
	return;
}

void impl_drawNumber(
	signed short x,
	signed short y,
	unsigned int number
) {
	static char buffer[11];
	static unsigned char i;
	
	snprintf(
		buffer,
		LENGTH_STRINT,
		"%u",
		number
	);
	
	for (i = 0; i < strlen(buffer); i++) {
		glRasterPos2s(
			x + (i * FONT_WIDTH),
			y + FONT_HEIGHT
		);
		glBitmap(
			FONT_WIDTH, FONT_HEIGHT,
			0, 0,
			0, 0,
			numberSheetGL[buffer[i] - 48]
		);
	}
	return;
}

void impl_drawFillRect(
	signed short x,
	signed short y,
	unsigned short width,
	unsigned short height
) {
	glRects(
		x, y,
		x + width, y + height
	);
	return;
}

/* Misc. */
void impl_loopStart() {
	glClear(GL_COLOR_BUFFER_BIT);
	return;
}