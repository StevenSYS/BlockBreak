#ifndef __SDL3INPUT__
#define __SDL3INPUT__

static inline void handleInput() {
	if (event.type == SDL_EVENT_KEY_DOWN) {
		switch (event.key.scancode) {
			case SDL_SCANCODE_UP:
				input(INPUT_UP);
				break;
			case SDL_SCANCODE_DOWN:
				input(INPUT_DOWN);
				break;
			case SDL_SCANCODE_LEFT:
				input(INPUT_LEFT);
				break;
			case SDL_SCANCODE_RIGHT:
				input(INPUT_RIGHT);
				break;
			case SDL_SCANCODE_RETURN:
				input(INPUT_RESET);
				break;
			case SDL_SCANCODE_ESCAPE:
				running = 0;
				break;
			#ifdef ENABLE_SCREENSHOT
			case SDL_SCANCODE_S:
				input(INPUT_SCREENSHOT);
				break;
			#endif
			default:
				input(INPUT_NONE);
				break;
		}
	}
	return;
}

#endif