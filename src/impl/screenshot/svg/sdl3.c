/* SDL3 - SVG Implementation */
#ifdef __APPLE
	#include <SDL.h>
#else
	#include <SDL3/SDL.h>
#endif

#include "progInfo.h"

char screenshot_take = 0;

static char colorHex[7];

static SDL_IOStream *file;

/* Drawing */
void screenshot_setColor(
	unsigned char red,
	unsigned char green,
	unsigned char blue
) {
	if (screenshot_take == 2) {
		SDL_snprintf(colorHex, 7, "%02X%02X%02X", red, green, blue);
	}
	return;
}

void screenshot_number(
	signed short x, signed short y,
	unsigned int number
) {
	if (screenshot_take == 2) {
		SDL_IOprintf(file, "\t<text x=\"%i\" y=\"%i\" fill=\"#%s\">%u</text>\n", x, y + FONT_HEIGHT, colorHex, number);
	}
	return;
}

void screenshot_fillRect(
	signed short x, signed short y,
	unsigned short width, unsigned short height
) {
	if (screenshot_take == 2) {
		SDL_IOprintf(file, "\t<rect width=\"%u\" height=\"%u\" x=\"%i\" y=\"%i\" fill=\"#%s\"/>\n", width, height, x, y, colorHex);
	}
	return;
}

/* Misc. */
void screenshot_start(const char *impl) {
	if (screenshot_take == 1) {
		file = SDL_IOFromFile("screenshot.svg", "w");
		
		if (file == NULL) {
			SDL_LogError(SDL_LOG_CATEGORY_ERROR, "%s\n", SDL_GetError());
			return;
		}
		
		screenshot_take = 2;
		SDL_IOprintf(file, "<svg width=\"%u\" height=\"%u\" xmlns=\"http://www.w3.org/2000/svg\">\n", RENDER_WIDTH, RENDER_HEIGHT);
		SDL_IOprintf(file, "\t<!-- " PROGRAM_NAME " v" PROGRAM_VERSION " -->\n");
		SDL_IOprintf(file, "\t<!-- Implementation: %s -->\n", impl);
		SDL_IOprintf(file, "\t<!-- Screenshot Implementation: SDL3 - SVG -->\n");
		SDL_IOprintf(file, "\t<style>\n");
		SDL_IOprintf(file, "\t\ttext {\n");
		SDL_IOprintf(file, "\t\t\tfont-family: sans-serif;\n");
		SDL_IOprintf(file, "\t\t\tfont-size: %upx;\n", FONT_HEIGHT + 2);
		SDL_IOprintf(file, "\t\t}\n");
		SDL_IOprintf(file, "\t</style>\n");
		SDL_IOprintf(file, "\t<rect width=\"%u\" height=\"%u\" fill=\"#000\"/>\n", RENDER_WIDTH, RENDER_HEIGHT);
	}
	return;
}

void screenshot_end() {
	if (screenshot_take == 2) {
		screenshot_take = 0;
		SDL_IOprintf(file, "</svg>");
		
		if (!SDL_CloseIO(file)) {
			SDL_LogError(SDL_LOG_CATEGORY_ERROR, "%s\n", SDL_GetError());
			return;
		}
	}
	return;
}