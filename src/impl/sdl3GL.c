/* SDL3/OpenGL Implementation */
#define IMPL_NAME "SDL3 + GL"
#include "glShared.h"

#ifdef __APPLE
	#include <SDL.h>
	#include <gl.h>
#else
	#include <SDL3/SDL.h>
	#include <GL/gl.h>
#endif

static char running = 1;

static int waitTime;

static unsigned int lastTime;

static SDL_Event event;
static SDL_Window *window;
static SDL_GLContext glContext;

#include "sdl3Input.h"

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
	void (*draw)()
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
	
	glSharedInit();
	
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
	
	SDL_GL_DestroyContext(glContext);
	SDL_DestroyWindow(window);
	SDL_Quit();
	return;
}