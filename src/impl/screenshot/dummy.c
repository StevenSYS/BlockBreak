/* Dummy/Template Implementation */
char sImpl_take = 0;

/* Drawing */
void sImpl_setColor(
	unsigned char red,
	unsigned char green,
	unsigned char blue
) {
	if (sImpl_take == 2) {
	}
	return;
}

void sImpl_number(
	signed short x, signed short y,
	unsigned int number
) {
	if (sImpl_take == 2) {
	}
	return;
}

void sImpl_fillRect(
	signed short x, signed short y,
	unsigned short width, unsigned short height
) {
	if (sImpl_take == 2) {
	}
	return;
}

/* Misc. */
void sImpl_start() {
	if (sImpl_take == 1) {
		sImpl_take = 2;
	}
	return;
}

void sImpl_end() {
	if (sImpl_take == 2) {
		sImpl_take = 0;
	}
	return;
}