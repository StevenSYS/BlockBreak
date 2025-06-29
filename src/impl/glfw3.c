/* GLFW3 Implementation */
#define IMPL_NAME "GLFW3"
#include "glShared.h"

#ifdef __APPLE
	#include <glfw3.h>
#else
	#include <GLFW/glfw3.h>
#endif

static GLFWwindow *window;

static double lastTime;

static void input(
	GLFWwindow *window,
	int key,
	int scancode,
	int action,
	int mods
) {
	if (action == GLFW_PRESS) {
		random_increase();
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
				screenshot_take = 1;
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
	glFlush();
	glfwSwapBuffers(window);
	#ifdef ENABLE_SCREENSHOT
	screenshot_end();
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
		PROGRAM_NAME " v" PROGRAM_VERSION " - GLFW3",
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
		
		/* FIXME: "Processor: 24.7%" - GNOME System Monitor */
		while (glfwGetTime() < lastTime + (1.0f / MAX_FPS));
	}
	
	glfwTerminate();
	return;
}