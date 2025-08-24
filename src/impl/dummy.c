/* Dummy/Template Implementation */
#include <random.h>
#ifdef ENABLE_SCREENSHOT
	#include <sImpl.h>
#endif

#include "entity.h"
#include "progInfo.h"

/* Drawing */
void impl_setColor(
	const unsigned char red,
	const unsigned char green,
	const unsigned char blue
) {
	#ifdef ENABLE_SCREENSHOT
	sImpl_setColor(red, green, blue);
	#endif
	return;
}

void impl_drawNumber(
	const signed short x, const signed short y,
	const unsigned int number
) {
	#ifdef ENABLE_SCREENSHOT
	sImpl_number(x, y, number);
	#endif
	return;
}

void impl_drawFillRect(
	const signed short x, const signed short y,
	const unsigned short width, const unsigned short height
) {
	#ifdef ENABLE_SCREENSHOT
	sImpl_fillRect(x, y, width, height);
	#endif
	return;
}

/* Misc. */
void impl_loopStart() {
	#ifdef ENABLE_SCREENSHOT
	sImpl_start("Dummy");
	#endif
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
	return;
}