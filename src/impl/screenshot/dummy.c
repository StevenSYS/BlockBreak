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
	const signed short x, const signed short y,
	const unsigned int number
) {
	if (sImpl_take == 2) {
	}
	return;
}

void sImpl_fillRect(
	const signed short x, const signed short y,
	const unsigned short width, const unsigned short height
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