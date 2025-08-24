/* PPM Implementation */
#define SIMPL_INCSTRING
#include "sImplMacros.h"
#include "numberSheet.h"
#include "progInfo.h"

#ifdef FILENAME83
	#define SIMPL_FILENAME "SCRNSHOT.PPM"
#else
	#define SIMPL_FILENAME "screenshot.ppm"
#endif

char sImpl_take = 0;

static char pixels[RENDER_WIDTH * RENDER_HEIGHT][3];
static char buffer[11];

static unsigned char i, j;
static unsigned char currentColor[3];

static unsigned short x2, y2;

/* Drawing */
void sImpl_setColor(
	const unsigned char red,
	const unsigned char green,
	const unsigned char blue
) {
	if (sImpl_take == 2) {
		currentColor[0] = red;
		currentColor[1] = green;
		currentColor[2] = blue;
	}
	return;
}

void sImpl_number(
	const signed short x, const signed short y,
	const unsigned int number
) {
	SIMPL_SNPRINTF(buffer, 11, "%u", number);
	if (sImpl_take == 2) {
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

void sImpl_fillRect(
	signed short x, signed short y,
	unsigned short width, unsigned short height
) {
	if (sImpl_take == 2) {
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
void sImpl_start(const char *impl) {
	if (sImpl_take == 1) {
		file = SIMPL_FOPEN(SIMPL_FILENAME, "wb");
		
		if (file == NULL) {
			SIMPL_ERROR("Failed to open/create screenshot file");
			return;
		}
		
		sImpl_take = 2;
		SIMPL_FPRINTF(file, "P6\n");
		SIMPL_FPRINTF(file, "# " PROGRAM_NAME " v" PROGRAM_VERSION "\n");
		SIMPL_FPRINTF(file, "# Implementation: %s\n", impl);
		SIMPL_FPRINTF(file, "# Screenshot Implementation: PPM (" SIMPL_NAME ")\n");
		SIMPL_FPRINTF(file, "%u %u\n", RENDER_WIDTH, RENDER_HEIGHT);
		SIMPL_FPRINTF(file, "255\n");
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

void sImpl_end() {
	if (sImpl_take == 2) {
		sImpl_take = 0;
		for (y2 = 0; y2 < RENDER_HEIGHT; y2++) {
			for (x2 = 0; x2 < RENDER_WIDTH; x2++) {
				for (i = 0; i < 3; i++) {
					SIMPL_FWRITE(
						&pixels[(y2 * RENDER_WIDTH) + x2][i],
						1,
						sizeof(unsigned char),
						file
					);
				}
			}
		}
		
		#if SIMPL == 2
		if (!SIMPL_FCLOSE(file)) {
		#else
		if (SIMPL_FCLOSE(file) != 0) {
		#endif
			SIMPL_ERROR("Failed to close screenshot file");
			return;
		}
	}
	return;
}