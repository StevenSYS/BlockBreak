#ifndef __INPUT__
#define __INPUT__

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

extern void input(unsigned char key);

#endif