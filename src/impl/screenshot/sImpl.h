#ifndef __SIMPL__
#define __SIMPL__

/* Drawing */
void sImpl_setColor(
	unsigned char red,
	unsigned char green,
	unsigned char blue
);

void sImpl_number(
	signed short x, signed short y,
	unsigned int number
);

void sImpl_fillRect(
	signed short x, signed short y,
	unsigned short width, unsigned short height
);

/* Misc. */
void sImpl_start(const char *impl);

void sImpl_end();

/* Externs */
extern char sImpl_take;

#endif