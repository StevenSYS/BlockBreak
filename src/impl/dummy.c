/* Dummy/Template Implementation */
#include <random.h>

#include "entity.h"
#include "progInfo.h"

static void (*main_reset)();

static char *main_timerStart;

static entity_t *main_player;

/* Drawing */
void impl_setColor(
	unsigned char red,
	unsigned char green,
	unsigned char blue
) {
	return;
}

void impl_drawNumber(
	short x, short y,
	unsigned int number
) {
	return;
}

void impl_drawFillRect(
	short x, short y,
	unsigned short width, unsigned short height
) {
	return;
}

/* Misc. */
void impl_loopStart() {
	return;
}

void impl_loopEnd() {
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