#ifndef __IMPL__
#define __IMPL__

#include "entity.h"

/* Draw */
void impl_setColor(
	const unsigned char red,
	const unsigned char green,
	const unsigned char blue
);

void impl_drawNumber(
	const signed short x, const signed short y,
	const unsigned int number
);

void impl_drawFillRect(
	const signed short x, const signed short y,
	const unsigned short width, const unsigned short height
);

/* Misc. */
void impl_loopStart();

void impl_loopEnd();

void impl_init(
	int argc, char *argv[],
	void (*draw)()
);

#endif