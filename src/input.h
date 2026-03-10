#ifndef __INPUT__
#define __INPUT__

#include "entity.h"

/* Enums */
enum inputs {
	INPUT_UP,
	INPUT_DOWN,
	INPUT_LEFT,
	INPUT_RIGHT,
	INPUT_RESET,
	INPUT_NONE
};

/* Functions */
void input(enum inputs input);

void input_init(
	void (*reset)(),
	char *timerStart,
	entity_t *player
);

#endif