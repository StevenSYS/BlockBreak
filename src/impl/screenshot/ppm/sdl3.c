/* SDL3 - PPM Implementation */
#ifdef __APPLE
	#include <SDL.h>
#else
	#include <SDL3/SDL.h>
#endif

#include "sImpl.h"
#include "numberSheet.h"
#include "progInfo.h"

char screenshot_take = 0;

static char pixels[RENDER_WIDTH * RENDER_HEIGHT][3];
static char buffer[11];

static unsigned char i, j;
static unsigned char currentColor[3];

static unsigned short x2, y2;

static SDL_IOStream *file;

/* Drawing */
void screenshot_setColor(
	unsigned char red,
	unsigned char green,
	unsigned char blue
) {
	if (screenshot_take == 2) {
		currentColor[0] = red;
		currentColor[1] = green;
		currentColor[2] = blue;
	}
	return;
}

void screenshot_number(
	signed short x, signed short y,
	unsigned int number
) {
	SDL_snprintf(buffer, 11, "%u", number);
	if (screenshot_take == 2) {
		for (i = 0; i < strlen(buffer); i++) {
			for (y2 = 0; y2 < 8; y2++) {
				for (x2 = 0; x2 < 8; x2++) {
					if (numberSheet[buffer[i] - 48][y2][x2]) {
						for (j = 0; j < 3; j++) {
							pixels[
								(y + y2) * RENDER_WIDTH + (
									(x + x2) + (i * 8)
								)
							][j] = numberSheet[buffer[i] - 48][y2][x2] * currentColor[j];
						}
					}
				}
			}
		}
	}
	return;
}

void screenshot_fillRect(
	signed short x, signed short y,
	unsigned short width, unsigned short height
) {
	if (screenshot_take == 2) {
		for (y2 = 0; y2 < height; y2++) {
			for (x2 = 0; x2 < width; x2++) {
				for (i = 0; i < 3; i++) {
					pixels[((y + y2) * RENDER_WIDTH) + (x + x2)][i] = currentColor[i];
				}
			}
		}
	}
	return;
}

/* Misc. */
void screenshot_start(const char *impl) {
	if (screenshot_take == 1) {
		file = SDL_IOFromFile("screenshot.ppm", "wb");
		
		if (file == NULL) {
			SDL_LogError(SDL_LOG_CATEGORY_ERROR, "%s\n", SDL_GetError());
			return;
		}
		
		screenshot_take = 2;
		SDL_IOprintf(file, "P6\n");
		SDL_IOprintf(file, "# " PROGRAM_NAME " v" PROGRAM_VERSION "\n");
		SDL_IOprintf(file, "# Implementation: %s\n", impl);
		SDL_IOprintf(file, "# Screenshot Implementation: libc - PPM\n");
		SDL_IOprintf(file, "%u %u\n", RENDER_WIDTH, RENDER_HEIGHT);
		SDL_IOprintf(file, "255\n");
		for (y2 = 0; y2 < RENDER_HEIGHT; y2++) {
			for (x2 = 0; x2 < RENDER_WIDTH; x2++) {
				for (i = 0; i < 3; i++) {
					pixels[(y2 * RENDER_WIDTH) + x2][i] = 0x00;
				}
			}
		}
	}
	return;
}

void screenshot_end() {
	if (screenshot_take == 2) {
		screenshot_take = 0;
		for (y2 = 0; y2 < RENDER_HEIGHT; y2++) {
			for (x2 = 0; x2 < RENDER_WIDTH; x2++) {
				for (i = 0; i < 3; i++) {
					SDL_WriteIO(
						file,
						&pixels[(y2 * RENDER_WIDTH) + x2][i],
						1
					);
				}
			}
		}
		
		if (!SDL_CloseIO(file)) {
			SDL_LogError(SDL_LOG_CATEGORY_ERROR, "%s\n", SDL_GetError());
			return;
		}
	}
	return;
}