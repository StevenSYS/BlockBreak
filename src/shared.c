/* C Shared Stuff */
#include "input.h"
#include "progInfo.h"

void draw(); 

int main(int argc, char *argv[]);

void getMacros(
	char *ptrName,
	char *ptrVersion,
	int renderWidth,
	int renderHeight,
	int fps,
	int fontHeight
);

void jsInput(unsigned char key) {
	switch (key) {
		case 38: /* Up */
			input(INPUT_UP);
			break;
		case 40: /* Down */
			input(INPUT_DOWN);
			break;
		case 37: /* Left */
			input(INPUT_LEFT);
			break;
		case 39: /* Right */
			input(INPUT_RIGHT);
			break;
		case 13: /* Enter */
			input(INPUT_RESET);
			break;
		default:
			input(INPUT_NONE);
			break;
	}
	return;
}

void impl_loopEnd() {
	return;
}

void impl_init(int argc, char *argv[]) {
	getMacros(
		PROGRAM_NAME,
		PROGRAM_VERSION,
		RENDER_WIDTH,
		RENDER_HEIGHT,
		MAX_FPS,
		FONT_HEIGHT
	);
	return;
}

void _start() {
	main(0, 0);
	return;
}