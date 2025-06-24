/* SDL3 Implementation */
#ifdef __APPLE
	#include <SDL.h>
#else
	#include <SDL3/SDL.h>
#endif
#include <random.h>
#ifdef ENABLE_SCREENSHOT
	#include <sImpl.h>
#endif

#include "entity.h"
#include "progInfo.h"

static void (*main_reset)();

static char running = 1;
static char *main_timerStart;

static unsigned int lastTime;

static SDL_Event event;
static SDL_Window *window;
static SDL_Renderer *renderer;
static SDL_FRect rect;

static entity_t *main_player;

static void handleEvent() {
	SDL_PollEvent(&event);
	
	switch (event.type) {
		case SDL_EVENT_KEY_DOWN:
			random_increase();
			switch (event.key.scancode) {
				case SDL_SCANCODE_UP:
					main_player->direction = ENTITY_DIR_UP;
					*main_timerStart = 1;
					break;
				case SDL_SCANCODE_DOWN:
					main_player->direction = ENTITY_DIR_DOWN;
					*main_timerStart = 1;
					break;
				case SDL_SCANCODE_LEFT:
					main_player->direction = ENTITY_DIR_LEFT;
					*main_timerStart = 1;
					break;
				case SDL_SCANCODE_RIGHT:
					main_player->direction = ENTITY_DIR_RIGHT;
					*main_timerStart = 1;
					break;
				case SDL_SCANCODE_RETURN:
					main_reset();
					break;
				case SDL_SCANCODE_ESCAPE:
					running = 0;
					break;
				#ifdef ENABLE_SCREENSHOT
				case SDL_SCANCODE_S:
					screenshot_take = 1;
					break;
				#endif
				default:
					break;
			}
			break;
		case SDL_EVENT_QUIT:
			running = 0;
			break;
	}
	return;
}

/* Drawing */
void impl_setColor(
	unsigned char red,
	unsigned char green,
	unsigned char blue
) {
	SDL_SetRenderDrawColor(renderer, red, green, blue, SDL_ALPHA_OPAQUE);
	#ifdef ENABLE_SCREENSHOT
	screenshot_setColor(red, green, blue);
	#endif
	return;
}

void impl_drawNumber(
	signed short x, signed short y,
	unsigned int number
) {
	SDL_RenderDebugTextFormat(renderer, (float)x, (float)y, "%u", number);
	#ifdef ENABLE_SCREENSHOT
	screenshot_number(x, y, number);
	#endif
	return;
}

void impl_drawFillRect(
	signed short x, signed short y,
	unsigned short width, unsigned short height
) {
	rect.x = x;
	rect.y = y;
	rect.w = width,
	rect.h = height;
	SDL_RenderFillRect(renderer, &rect);
	#ifdef ENABLE_SCREENSHOT
	screenshot_fillRect(x, y, width, height);
	#endif
	return;
}

/* Misc. */
void impl_loopStart() {
	impl_setColor(0x00, 0x00, 0x00);
	SDL_RenderClear(renderer);
	#ifdef ENABLE_SCREENSHOT
	screenshot_start();
	#endif
	return;
}

void impl_loopEnd() {
	SDL_RenderPresent(renderer);
	#ifdef ENABLE_SCREENSHOT
	screenshot_end();
	#endif
	return;
}

void impl_init(
	int argc, char *argv[],
	char *timerStart, entity_t *player,
	void (*reset)(), void (*draw)()
) {
	window = SDL_CreateWindow(
		PROGRAM_NAME " v" PROGRAM_VERSION " - SDL3",
		RENDER_WIDTH, RENDER_HEIGHT,
		0
	);
	
	if (window == NULL) {
		SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Couldn't create window: %s\n", SDL_GetError());
		return;
	}
	
	renderer = SDL_CreateRenderer(
		window,
		NULL
	);
	
	if (renderer == NULL) {
		SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Couldn't create renderer: %s\n", SDL_GetError());
		return;
	}
	
	main_timerStart = timerStart;
	main_player = player;
	main_reset = reset;
	
	while (running) {
		lastTime = SDL_GetTicks();
		
		handleEvent();
		draw();
		
		while (SDL_GetTicks() < lastTime + (1000.0f / MAX_FPS)) {
			handleEvent();
			SDL_Delay(1);
		}
	}
	
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
	return;
}