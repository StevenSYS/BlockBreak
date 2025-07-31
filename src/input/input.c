#ifdef ENABLE_SCREENSHOT
	#include <sImpl.h>
#endif

#include "random.h"
#include "entity.h"
#include "input.h"

void reset();

extern char timerStart;

extern entity_t player;

void input(unsigned char key) {
	random_index++;
	switch (key) {
		case INPUT_UP:
		case INPUT_DOWN:
		case INPUT_LEFT:
		case INPUT_RIGHT:
			player.direction = key;
			if (!timerStart) {
				timerStart = 1;
			}
			break;
		case INPUT_RESET:
			reset();
			break;
		#ifdef ENABLE_SCREENSHOT
		case INPUT_SCREENSHOT:
			sImpl_take = 1;
			break;
		#endif
		default:
			break;
	}
	return;
}