/* Dummy/Template Implementation */
#include <random.h>
#ifdef ENABLE_SCREENSHOT
	#include <sImpl.h>
#endif

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
	#ifdef ENABLE_SCREENSHOT
	screenshot_setColor(red, green, blue);
	#endif
	return;
}

void impl_drawNumber(
	signed short x, signed short y,
	unsigned int number
) {
	#ifdef ENABLE_SCREENSHOT
	screenshot_number(x, y, number);
	#endif
	return;
}

void impl_drawFillRect(
	signed short x, signed short y,
	unsigned short width, unsigned short height
) {
	#ifdef ENABLE_SCREENSHOT
	screenshot_fillRect(x, y, width, height);
	#endif
	return;
}

/* Misc. */
void impl_loopStart() {
	#ifdef ENABLE_SCREENSHOT
	screenshot_start("Dummy");
	#endif
	return;
}

void impl_loopEnd() {
	#ifdef ENABLE_SCREENSHOT
	screenshot_end();
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