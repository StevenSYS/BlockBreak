#ifndef __INPUT__
#define __INPUT__

/* Enums */
enum inputs {
	INPUT_UP,
	INPUT_DOWN,
	INPUT_LEFT,
	INPUT_RIGHT,
	INPUT_RESET,
	#ifdef ENABLE_SCREENSHOT
	INPUT_SCREENSHOT,
	#endif
	INPUT_NONE
};

/* Functions */
void input(unsigned char key);

void input_init(
	void (*reset)(),
	char *timerStart,
	entity_t *player
);

#endif