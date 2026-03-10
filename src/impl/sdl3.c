/* SDL3 Implementation */
#ifdef __APPLE
	#include <SDL.h>
#else
	#include <SDL3/SDL.h>
#endif

#include "input.h"
#include "entity.h"
#include "progInfo.h"

static char running = 1;

static int waitTime;

static unsigned int lastTime;

static SDL_Event event;
static SDL_Window *window;
static SDL_Renderer *renderer;
static SDL_FRect rect;

#include "sdl3Event.h"

/* Drawing */
void impl_setColor(
	unsigned char red,
	unsigned char green,
	unsigned char blue
) {
	SDL_SetRenderDrawColor(
		renderer,
		red, green, blue,
		SDL_ALPHA_OPAQUE
	);
	return;
}

void impl_drawNumber(
	signed short x,
	signed short y,
	unsigned int number
) {
	SDL_RenderDebugTextFormat
		(renderer,
		(float)x,
		(float)y,
		"%u",
		number
	);
	return;
}

void impl_drawFillRect(
	signed short x,
	signed short y,
	unsigned short width,
	unsigned short height
) {
	rect.x = x;
	rect.y = y;
	rect.w = width,
	rect.h = height;
	SDL_RenderFillRect(renderer, &rect);
	return;
}

/* Misc. */
void impl_loopStart() {
	impl_setColor(0x00, 0x00, 0x00);
	SDL_RenderClear(renderer);
	return;
}

void impl_loopEnd() {
	SDL_RenderPresent(renderer);
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
		SDL_LogError(
			SDL_LOG_CATEGORY_ERROR,
			"Failed to create window: %s\n",
			SDL_GetError()
		);
		return;
	}
	
	renderer = SDL_CreateRenderer(
		window,
		NULL
	);
	
	if (renderer == NULL) {
		SDL_LogError(
			SDL_LOG_CATEGORY_ERROR,
			"Failed to create renderer: %s\n",
			SDL_GetError()
		);
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