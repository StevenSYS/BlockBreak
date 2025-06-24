/* C Standard Library - SVG Implementation */
#include <stdio.h>

#include "progInfo.h"

char screenshot_take = 0;

static char colorHex[7];

static FILE *file;

/* Drawing */
void screenshot_setColor(
	unsigned char red,
	unsigned char green,
	unsigned char blue
) {
	if (screenshot_take == 2) {
		snprintf(colorHex, 7, "%02X%02X%02X", red, green, blue);
	}
	return;
}

void screenshot_number(
	signed short x, signed short y,
	unsigned int number
) {
	if (screenshot_take == 2) {
		fprintf(file, "\t<text x=\"%i\" y=\"%i\" fill=\"#%s\">%u</text>\n", x, y + FONT_HEIGHT, colorHex, number);
	}
	return;
}

void screenshot_fillRect(
	signed short x, signed short y,
	unsigned short width, unsigned short height
) {
	if (screenshot_take == 2) {
		fprintf(file, "\t<rect width=\"%u\" height=\"%u\" x=\"%i\" y=\"%i\" fill=\"#%s\"/>\n", width, height, x, y, colorHex);
	}
	return;
}

/* Misc. */
void screenshot_start() {
	if (screenshot_take == 1) {
		file = fopen("screenshot.svg", "w");
		
		if (file == NULL) {
			fprintf(stderr, "Failed to open screenshot file\n");
			return;
		}
		
		screenshot_take = 2;
		fprintf(file, "<svg width=\"%u\" height=\"%u\" xmlns=\"http://www.w3.org/2000/svg\">\n", RENDER_WIDTH, RENDER_HEIGHT);
		fprintf(file, "\t<!-- Screenshot taken in " PROGRAM_NAME " v" PROGRAM_VERSION " with the libc - SVG screenshot implementation -->\n");
		fprintf(file, "\t<style>\n");
		fprintf(file, "\t\ttext {\n");
		fprintf(file, "\t\t\tfont-family: sans-serif;\n");
		fprintf(file, "\t\t\tfont-size: %upx;\n", FONT_HEIGHT + 2);
		fprintf(file, "\t\t}\n");
		fprintf(file, "\t</style>\n");
		fprintf(file, "\t<rect width=\"%u\" height=\"%u\" fill=\"#000\"/>\n", RENDER_WIDTH, RENDER_HEIGHT);
	}
	return;
}

void screenshot_end() {
	if (screenshot_take == 2) {
		screenshot_take = 0;
		fprintf(file, "</svg>");
		
		if (fclose(file) != 0) {
			fprintf(stderr, "Failed to close file\n");
			return;
		}
	}
	return;
}