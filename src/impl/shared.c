/* C Shared Stuff */
#define SIMPL_NOEXTERNS
#include <random.h>

#include "sImpl.h"
#include "entity.h"
#include "progInfo.h"

int main(int argc, char *argv[]);

static void (*main_reset)();

static char *main_timerStart;

static entity_t *main_player;

void getMacros(
	char *memPos_programName, char *memPos_programVersion,
	int renderWidth, int renderHeight,
	int macro_maxFPS,
	int fontHeight
);

void input(unsigned char key) {
	random_index++;
	switch (key) {
		case 38: /* Up */
			main_player->direction = ENTITY_DIR_UP;
			*main_timerStart = 1;
			break;
		case 40: /* Down */
			main_player->direction = ENTITY_DIR_DOWN;
			*main_timerStart = 1;
			break;
		case 37: /* Left */
			main_player->direction = ENTITY_DIR_LEFT;
			*main_timerStart = 1;
			break;
		case 39: /* Right */
			main_player->direction = ENTITY_DIR_RIGHT;
			*main_timerStart = 1;
			break;
		#ifdef ENABLE_SCREENSHOT
		case 83: /* S */
			sImpl_setTake(1);
			break;
		#endif
		case 13: /* Enter */
			main_reset();
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
	char *timerStart, entity_t *player,
	void (*reset)(), void (*draw)()
) {
	main_timerStart = timerStart;
	main_player = player;
	main_reset = reset;
	return;
}

void _start() {
	getMacros(
		PROGRAM_NAME, PROGRAM_VERSION,
		RENDER_WIDTH, RENDER_HEIGHT,
		MAX_FPS,
		FONT_HEIGHT
	);
	main(0, 0);
	return;
}