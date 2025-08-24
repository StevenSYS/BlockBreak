/* SDL3 Implementation */
#ifdef __APPLE
	#include <SDL.h>
#else
	#include <SDL3/SDL.h>
#endif
#ifdef ENABLE_SCREENSHOT
	#include <sImpl.h>
#endif

#include "entity.h"
#include "input.h"
#include "progInfo.h"

static char running = 1;

static int waitTime;

static unsigned int lastTime;

static SDL_Event event;
static SDL_Window *window;
static SDL_Renderer *renderer;
static SDL_FRect rect;

static void handleEvent() {
	SDL_PollEvent(&event);
	
	switch (event.type) {
		case SDL_EVENT_KEY_DOWN:
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
			break;
		case SDL_EVENT_QUIT:
			running = 0;
			break;
		default:
			break;
	}
	return;
}

/* Drawing */
void impl_setColor(
	const unsigned char red,
	const unsigned char green,
	const unsigned char blue
) {
	SDL_SetRenderDrawColor(renderer, red, green, blue, SDL_ALPHA_OPAQUE);
	#ifdef ENABLE_SCREENSHOT
	sImpl_setColor(red, green, blue);
	#endif
	return;
}

void impl_drawNumber(
	const signed short x, const signed short y,
	const unsigned int number
) {
	SDL_RenderDebugTextFormat(renderer, (float)x, (float)y, "%u", number);
	#ifdef ENABLE_SCREENSHOT
	sImpl_number(x, y, number);
	#endif
	return;
}

void impl_drawFillRect(
	const signed short x, const signed short y,
	const unsigned short width, const unsigned short height
) {
	rect.x = x;
	rect.y = y;
	rect.w = width,
	rect.h = height;
	SDL_RenderFillRect(renderer, &rect);
	#ifdef ENABLE_SCREENSHOT
	sImpl_fillRect(x, y, width, height);
	#endif
	return;
}

/* Misc. */
void impl_loopStart() {
	impl_setColor(0x00, 0x00, 0x00);
	SDL_RenderClear(renderer);
	#ifdef ENABLE_SCREENSHOT
	sImpl_start("SDL3");
	#endif
	return;
}

void impl_loopEnd() {
	SDL_RenderPresent(renderer);
	#ifdef ENABLE_SCREENSHOT
	sImpl_end();
	#endif
	return;
}

void impl_init(
	int argc, char *argv[],
	void (*draw)()
) {
	SDL_SetAppMetadata(PROGRAM_NAME, PROGRAM_VERSION, "com.stevensys.blockbreakc");
	
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
	
	while (running) {
		lastTime = SDL_GetTicksNS();
		
		handleEvent();
		draw();
		
		waitTime = (
			1000000000 / MAX_FPS
		) - (
			SDL_GetTicksNS() - lastTime
		);
		
		if (waitTime > 0) {
			SDL_DelayNS(waitTime);
		}
		
		handleEvent();
	}
	
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
	return;
}