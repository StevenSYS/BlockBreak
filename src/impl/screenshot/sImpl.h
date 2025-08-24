#ifndef __SIMPL__
#define __SIMPL__

/* Drawing */
void sImpl_setColor(
	const unsigned char red,
	const unsigned char green,
	const unsigned char blue
);

void sImpl_number(
	const signed short x, const signed short y,
	const unsigned int number
);

void sImpl_fillRect(
	const signed short x, const signed short y,
	const unsigned short width, const unsigned short height
);

/* Misc. */
void sImpl_start(const char *impl);

void sImpl_end();

/* This needs to be a function or else the WebAssembly version doesn't work */
void sImpl_setTake(const char newValue);

#endif