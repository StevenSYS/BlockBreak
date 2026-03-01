#ifndef __SDL3EVENT__
#define __SDL3EVENT__

static inline void handleEvent() {
	while (SDL_PollEvent(&event)) {
		switch (event.type) {
			case SDL_EVENT_KEY_DOWN:
				switch (event.key.scancode) {
					case SDL_SCANCODE_UP:
						input(INPUT_UP);
						continue;
					case SDL_SCANCODE_DOWN:
						input(INPUT_DOWN);
						continue;
					case SDL_SCANCODE_LEFT:
						input(INPUT_LEFT);
						continue;
					case SDL_SCANCODE_RIGHT:
						input(INPUT_RIGHT);
						continue;
					case SDL_SCANCODE_RETURN:
						input(INPUT_RESET);
						continue;
					case SDL_SCANCODE_ESCAPE:
						running = 0;
						continue;
					default:
						input(INPUT_NONE);
						continue;
				}
				continue;
			case SDL_EVENT_QUIT:
				running = 0;
				continue;
			default:
				continue;
		}
	}
	return;
}

#endif