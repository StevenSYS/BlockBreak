/* SDL3 + GL Implementation */
#define IMPL_NAME "SDL3 + GL"
#include "glShared.h"

#ifdef __APPLE
	#include <SDL.h>
	#include <gl.h>
#else
	#include <SDL3/SDL.h>
	#include <GL/gl.h>
#endif
#ifdef ENABLE_SCREENSHOT
	#include <sImpl.h>
#endif

static char running = 1;

static unsigned int lastTime;

static SDL_Event event;
static SDL_Window *window;
static SDL_GLContext glContext;

static void handleEvent() {
	SDL_PollEvent(&event);
	
	switch (event.type) {
		case SDL_EVENT_KEY_DOWN:
			random_index++;
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
					sImpl_take = 1;
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

/* Misc. */
void impl_loopEnd() {
	SDL_GL_SwapWindow(window);
	#ifdef ENABLE_SCREENSHOT
	sImpl_end();
	#endif
	return;
}

void impl_init(
	int argc, char *argv[],
	char *timerStart, entity_t *player,
	void (*reset)(), void(*draw)()
) {
	window = SDL_CreateWindow(
		PROGRAM_NAME " v" PROGRAM_VERSION " - " IMPL_NAME,
		RENDER_WIDTH, RENDER_HEIGHT,
		SDL_WINDOW_OPENGL
	);
	
	if (window == NULL) {
		SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Couldn't create window: %s\n", SDL_GetError());
		return;
	}
	
	glContext = SDL_GL_CreateContext(window);
	
	if (glContext == NULL) {
		SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Couldn't create renderer: %s\n", SDL_GetError());
		return;
	}
	
	glSharedInit(
		timerStart, player,
		reset
	);
	
	while (running) {
		lastTime = SDL_GetTicks();
		
		handleEvent();
		draw();
		
		SDL_Delay(
			(
				/* This "(float)" needs to be here or else the compiler optimization breaks the program */
				((float)1000.0f) / MAX_FPS
			) - (
				SDL_GetTicks() - lastTime
			)
		);
		
		handleEvent();
	}
	
	SDL_GL_DestroyContext(glContext);
	SDL_DestroyWindow(window);
	SDL_Quit();
	return;
}