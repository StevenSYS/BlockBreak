/* Dummy/Template Implementation */
char screenshot_take = 0;

/* Drawing */
void screenshot_setColor(
	unsigned char red,
	unsigned char green,
	unsigned char blue
) {
	if (screenshot_take == 2) {
	}
	return;
}

void screenshot_number(
	signed short x, signed short y,
	unsigned int number
) {
	if (screenshot_take == 2) {
	}
	return;
}

void screenshot_fillRect(
	signed short x, signed short y,
	unsigned short width, unsigned short height
) {
	if (screenshot_take == 2) {
	}
	return;
}

/* Misc. */
void screenshot_start() {
	if (screenshot_take == 1) {
		screenshot_take = 2;
	}
	return;
}

void screenshot_end() {
	if (screenshot_take == 2) {
		screenshot_take = 0;
	}
	return;
}