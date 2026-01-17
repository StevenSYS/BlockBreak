/* C Shared Stuff */
#define SIMPL_NOEXTERNS
#include <random.h>
#include <input.h>

#include "sImpl.h"
#include "entity.h"
#include "progInfo.h"

int main(int argc, char *argv[]);

void getMacros(
	char *ptrName, char *ptrVersion,
	int renderWidth, int renderHeight,
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
		#ifdef ENABLE_SCREENSHOT
		case 83: /* S */
			input(INPUT_SCREENSHOT);
			break;
		#endif
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
	#ifdef ENABLE_SCREENSHOT
	sImpl_end();
	#endif
	return;
}

void impl_init(
	int argc, char *argv[],
	void (*draw)()
) {
	getMacros(
		PROGRAM_NAME, PROGRAM_VERSION,
		RENDER_WIDTH, RENDER_HEIGHT,
		MAX_FPS,
		FONT_HEIGHT
	);
	return;
}

void _start() {
	main(0, 0);
	return;
}