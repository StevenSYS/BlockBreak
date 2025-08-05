/* GLFW3 Implementation */
#define _DEFAULT_SOURCE
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

static void glfwInput(
	GLFWwindow *window,
	int key,
	int scancode,
	int action,
	int mods
) {
	if (action == GLFW_PRESS) {
		switch (key) {
			case GLFW_KEY_UP:
				input(INPUT_UP);
				break;
			case GLFW_KEY_DOWN:
				input(INPUT_DOWN);
				break;
			case GLFW_KEY_LEFT:
				input(INPUT_LEFT);
				break;
			case GLFW_KEY_RIGHT:
				input(INPUT_RIGHT);
				break;
			case GLFW_KEY_ENTER:
				input(INPUT_RESET);
				break;
			case GLFW_KEY_ESCAPE:
				glfwSetWindowShouldClose(window, GL_TRUE);
				break;
			#ifdef ENABLE_SCREENSHOT
			case GLFW_KEY_S:
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
	void(*draw)()
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
	glfwSetKeyCallback(window, glfwInput);
	
	glSharedInit();
	
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