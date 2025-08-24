#ifdef ENABLE_SCREENSHOT
	#include <sImpl.h>
#endif

#include "random.h"
#include "entity.h"
#include "input.h"

static void (*main_reset)();

static char *main_timerStart;

static entity_t *main_player;

void input(const enum inputs input) {
	random_index++;
	switch (input) {
		case INPUT_UP:
		case INPUT_DOWN:
		case INPUT_LEFT:
		case INPUT_RIGHT:
			main_player->direction = input;
			if (!*main_timerStart) {
				*main_timerStart = 1;
			}
			break;
		case INPUT_RESET:
			main_reset();
			break;
		#ifdef ENABLE_SCREENSHOT
		case INPUT_SCREENSHOT:
			sImpl_setTake(1);
			break;
		#endif
		default:
			break;
	}
	return;
}

void input_init(
	void (*reset)(),
	char *timerStart,
	entity_t *player
) {
	main_reset = reset;
	main_timerStart = timerStart;
	main_player = player;
	return;
}