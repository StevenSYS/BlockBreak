/* GLFW3 Implementation */
#define IMPL_NAME "GLFW3"
#include <unistd.h>

#include "glShared.h"

#ifdef __APPLE
	#include <glfw3.h>
#else
	#include <GLFW/glfw3.h>
#endif

static GLFWwindow *window;

static double lastTime;
static double sleepTime;

static void input(
	GLFWwindow *window,
	int key,
	int scancode,
	int action,
	int mods
) {
	if (action == GLFW_PRESS) {
		random_index++;
		switch (key) {
			case GLFW_KEY_UP:
				*main_timerStart = 1;
				main_player->direction = ENTITY_DIR_UP;
				break;
			case GLFW_KEY_DOWN:
				*main_timerStart = 1;
				main_player->direction = ENTITY_DIR_DOWN;
				break;
			case GLFW_KEY_LEFT:
				*main_timerStart = 1;
				main_player->direction = ENTITY_DIR_LEFT;
				break;
			case GLFW_KEY_RIGHT:
				*main_timerStart = 1;
				main_player->direction = ENTITY_DIR_RIGHT;
				break;
			case GLFW_KEY_ENTER:
				main_reset();
				break;
			case GLFW_KEY_ESCAPE:
				glfwSetWindowShouldClose(window, GL_TRUE);
				break;
			#ifdef ENABLE_SCREENSHOT
			case GLFW_KEY_S:
				sImpl_take = 1;
				break;
			#endif
			default:
				break;
		}
	}
	return;
}

/* Misc. */
void impl_loopEnd() {
	glfwSwapBuffers(window);
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
	if (!glfwInit()) {
		return;
	}
	
	window = glfwCreateWindow(
		RENDER_WIDTH, RENDER_HEIGHT,
		PROGRAM_NAME " v" PROGRAM_VERSION " - " IMPL_NAME,
		NULL, NULL
	);
	
	if (window == NULL) {
		glfwTerminate();
		return;
	}
	
	glfwSetWindowSizeLimits(
		window,
		RENDER_WIDTH, RENDER_HEIGHT,
		RENDER_WIDTH, RENDER_HEIGHT
	);
	
	glfwMakeContextCurrent(window);
	glfwSetKeyCallback(window, input);
	
	glSharedInit(
		timerStart, player,
		reset
	);
	
	while (!glfwWindowShouldClose(window)) {
		lastTime = glfwGetTime();
		
		glfwPollEvents();
		
		draw();
		
		sleepTime = ((1.0f / MAX_FPS) - (glfwGetTime() - lastTime)) * 1000000;
		if (sleepTime > 0) {
			usleep(sleepTime);
		}
		
		glfwPollEvents();
	}
	
	glfwTerminate();
	return;
}