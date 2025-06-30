/* SVG Implementation */
#include "sImplMacros.h"
#include "progInfo.h"

char screenshot_take = 0;

static char colorHex[7];


/* Drawing */
void screenshot_setColor(
	unsigned char red,
	unsigned char green,
	unsigned char blue
) {
	if (screenshot_take == 2) {
		SIMPL_SNPRINTF(colorHex, 7, "%02X%02X%02X", red, green, blue);
	}
	return;
}

void screenshot_number(
	signed short x, signed short y,
	unsigned int number
) {
	if (screenshot_take == 2) {
		SIMPL_FPRINTF(file, "\t<text x=\"%i\" y=\"%i\" fill=\"#%s\">%u</text>\n", x, y + FONT_HEIGHT, colorHex, number);
	}
	return;
}

void screenshot_fillRect(
	signed short x, signed short y,
	unsigned short width, unsigned short height
) {
	if (screenshot_take == 2) {
		SIMPL_FPRINTF(file, "\t<rect width=\"%u\" height=\"%u\" x=\"%i\" y=\"%i\" fill=\"#%s\"/>\n", width, height, x, y, colorHex);
	}
	return;
}

/* Misc. */
void screenshot_start(const char *impl) {
	if (screenshot_take == 1) {
		file = SIMPL_FOPEN("screenshot.svg", "w");
		
		if (file == NULL) {
			#if SIMPL == 1
			fprintf(stderr, "Failed to open/create screenshot file\n");
			#elif SIMPL == 2
			SIMPL_SDL_LOGERROR;
			#endif
			return;
		}
		
		screenshot_take = 2;
		SIMPL_FPRINTF(file, "<svg width=\"%u\" height=\"%u\" xmlns=\"http://www.w3.org/2000/svg\">\n", RENDER_WIDTH, RENDER_HEIGHT);
		SIMPL_FPRINTF(file, "\t<!-- " PROGRAM_NAME " v" PROGRAM_VERSION " -->\n");
		SIMPL_FPRINTF(file, "\t<!-- Implementation: %s -->\n", impl);
		SIMPL_FPRINTF(file, "\t<!-- Screenshot Implementation: SVG (" SIMPL_NAME ")-->\n");
		SIMPL_FPRINTF(file, "\t<style>\n");
		SIMPL_FPRINTF(file, "\t\ttext {\n");
		SIMPL_FPRINTF(file, "\t\t\tfont-family: sans-serif;\n");
		SIMPL_FPRINTF(file, "\t\t\tfont-size: %upx;\n", FONT_HEIGHT + 2);
		SIMPL_FPRINTF(file, "\t\t}\n");
		SIMPL_FPRINTF(file, "\t</style>\n");
		SIMPL_FPRINTF(file, "\t<rect width=\"%u\" height=\"%u\" fill=\"#000\"/>\n", RENDER_WIDTH, RENDER_HEIGHT);
	}
	return;
}

void screenshot_end() {
	if (screenshot_take == 2) {
		screenshot_take = 0;
		SIMPL_FPRINTF(file, "</svg>");
		
		#if SIMPL == 2
		if (!SIMPL_FCLOSE(file)) {
		#else
		if (SIMPL_FCLOSE(file) != 0) {
		#endif
			#if SIMPL == 1
			fprintf(stderr, "Failed to close screenshot file\n");
			#elif SIMPL == 2
			SIMPL_SDL_LOGERROR;
			#endif
			return;
		}
	}
	return;
}