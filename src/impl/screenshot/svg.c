/* SVG Implementation */
#include "sImplMacros.h"
#include "progInfo.h"

#ifdef FILENAME83
	#define SIMPL_FILENAME "SCRNSHOT.SVG"
#else
	#define SIMPL_FILENAME "screenshot.svg"
#endif

char sImpl_take = 0;

static char colorHex[7];

/* Drawing */
void sImpl_setColor(
	const unsigned char red,
	const unsigned char green,
	const unsigned char blue
) {
	if (sImpl_take == 2) {
		SIMPL_SNPRINTF(colorHex, 7, "%02X%02X%02X", red, green, blue);
	}
	return;
}

void sImpl_number(
	const signed short x, const signed short y,
	const unsigned int number
) {
	if (sImpl_take == 2) {
		SIMPL_FPRINTF(file, "\t<text x=\"%i\" y=\"%i\" fill=\"#%s\">%u</text>\n", x, y + FONT_HEIGHT, colorHex, number);
	}
	return;
}

void sImpl_fillRect(
	const signed short x, const signed short y,
	const unsigned short width, const unsigned short height
) {
	if (sImpl_take == 2) {
		SIMPL_FPRINTF(file, "\t<rect width=\"%u\" height=\"%u\" x=\"%i\" y=\"%i\" fill=\"#%s\"/>\n", width, height, x, y, colorHex);
	}
	return;
}

/* Misc. */
void sImpl_start(const char *impl) {
	if (sImpl_take == 1) {
		file = SIMPL_FOPEN(SIMPL_FILENAME, "w");
		
		if (file == NULL) {
			SIMPL_ERROR("Failed to open/create screenshot file");
			return;
		}
		
		sImpl_take = 2;
		SIMPL_FPRINTF(file, "<svg width=\"%u\" height=\"%u\" xmlns=\"http://www.w3.org/2000/svg\">\n", RENDER_WIDTH, RENDER_HEIGHT);
		SIMPL_FPRINTF(file, "\t<!-- " PROGRAM_NAME " v" PROGRAM_VERSION " -->\n");
		SIMPL_FPRINTF(file, "\t<!-- Implementation: %s -->\n", impl);
		SIMPL_FPRINTF(file, "\t<!-- Screenshot Implementation: SVG (" SIMPL_NAME ") -->\n");
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

void sImpl_end() {
	if (sImpl_take == 2) {
		sImpl_take = 0;
		SIMPL_FPRINTF(file, "</svg>");
		
		#if SIMPL == 2
		if (!SIMPL_FCLOSE(file)) {
		#elif SIMPL == 3
		if (SIMPL_FCLOSE(file) != FMOD_OK) {
		#else
		if (SIMPL_FCLOSE(file) != 0) {
		#endif
			SIMPL_ERROR("Failed to close screenshot file");
			return;
		}
	}
	return;
}