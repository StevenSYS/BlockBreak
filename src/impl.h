#ifndef __IMPL__
#define __IMPL__

#include "entity.h"

/* Draw */
void impl_setColor(
	unsigned char red,
	unsigned char green,
	unsigned char blue
);

void impl_drawNumber(
	signed short x,
	signed short y,
	unsigned int number
);

void impl_drawFillRect(
	signed short x,
	signed short y,
	unsigned short width,
	unsigned short height
);

/* Misc. */
void impl_loopStart();

void impl_loopEnd();

void impl_init(int argc, char *argv[]);

#endif