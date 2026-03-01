/* GLUT Implementation */
#define IMPL_NAME "GLUT"
#include "glShared.h"

#ifdef __APPLE
	#include <glut.h>
#else
	#define GLUT_DISABLE_ATEXIT_HACK
	#include <GL/glut.h>
#endif

static void glutInput(
	unsigned char key,
	int x, int y
) {
	random_index++;
	switch (key) {
		case '\r': /* Enter */
			input(INPUT_RESET);
			break;
		default:
			input(INPUT_NONE);
			break;
	}
}

static void inputSpecial(
	int key,
	int x, int y
) {
	switch (key) {
		case GLUT_KEY_UP:
			input(INPUT_UP);
			break;
		case GLUT_KEY_DOWN:
			input(INPUT_DOWN);
			break;
		case GLUT_KEY_LEFT:
			input(INPUT_LEFT);
			break;
		case GLUT_KEY_RIGHT:
			input(INPUT_RIGHT);
			break;
		default:
			input(INPUT_NONE);
			break;
	}
	return;
}

static void drawLoop(int msecs) {
	glutPostRedisplay();
	glutTimerFunc(1000 / MAX_FPS, drawLoop, 0);
	return;
}

/* Misc. */
void impl_loopEnd() {
	glutSwapBuffers();
	return;
}

void impl_init(
	int argc, char *argv[],
	void (*draw)()
) {
	glutInit(&argc, argv);
	
	glutInitDisplayMode(GLUT_RGBA | GLUT_SINGLE);
	glutCreateWindow(PROGRAM_NAME " v" PROGRAM_VERSION " - " IMPL_NAME);
	glutReshapeWindow(RENDER_WIDTH, RENDER_HEIGHT);
	
	glSharedInit();
	
	glutKeyboardFunc(glutInput);
	glutSpecialFunc(inputSpecial);
	glutDisplayFunc(draw);
	glutTimerFunc(1000 / MAX_FPS, drawLoop, 0);
	
	glutMainLoop();
	return;
}