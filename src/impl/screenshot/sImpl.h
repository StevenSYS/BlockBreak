#ifndef __SIMPL__
#define __SIMPL__

/* Drawing */
void screenshot_setColor(
	unsigned char red,
	unsigned char green,
	unsigned char blue
);

void screenshot_number(
	signed short x, signed short y,
	unsigned int number
);

void screenshot_fillRect(
	signed short x, signed short y,
	unsigned short width, unsigned short height
);

/* Misc. */
void screenshot_start();

void screenshot_end();

/* Externs */
extern char screenshot_take;

#endif