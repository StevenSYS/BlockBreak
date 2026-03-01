#ifdef ENABLE_SCREENSHOT
	#include <sImpl.h>
#endif

#include "random.h"
#include "entity.h"
#include "input.h"

void main_reset();

extern char main_timerStart;

extern entity_t main_player;

void input(const enum inputs input) {
	random_index++;
	
	switch (input) {
		case INPUT_UP:
		case INPUT_DOWN:
		case INPUT_LEFT:
		case INPUT_RIGHT:
			main_player.direction = (enum entity_directions)input;
			if (!main_timerStart) {
				main_timerStart = 1;
			}
			break;
		case INPUT_RESET:
			main_reset();
			break;
		default:
			break;
	}
	return;
}