/* GLUT Implementation */
#define IMPL_NAME "GLUT"
#include "glShared.h"

#ifdef __APPLE
	#include <glut.h>
#else
	#define GLUT_DISABLE_ATEXIT_HACK
	#include <GL/glut.h>
#endif
#ifdef ENABLE_SCREENSHOT
	#include <sImpl.h>
#endif

static void input(
	unsigned char key,
	int x, int y
) {
	random_increase();
	switch (key) {
		case '\r': /* Enter */
			main_reset();
			break;
		#ifdef ENABLE_SCREENSHOT
		case 's':
		case 'S':
			screenshot_take = 1;
			break;
		#endif
		default:
			break;
	}
}

static void inputSpecial(
	int key,
	int x, int y
) {
	random_increase();
	switch (key) {
		case GLUT_KEY_UP:
			main_player->direction  = ENTITY_DIR_UP;
			*main_timerStart = 1;
			break;
		case GLUT_KEY_DOWN:
			main_player->direction = ENTITY_DIR_DOWN;
			*main_timerStart = 1;
			break;
		case GLUT_KEY_LEFT:
			main_player->direction = ENTITY_DIR_LEFT;
			*main_timerStart = 1;
			break;
		case GLUT_KEY_RIGHT:
			main_player->direction = ENTITY_DIR_RIGHT;
			*main_timerStart = 1;
			break;
		default:
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
	glFlush();
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
	glutInit(&argc, argv);
	
	glutInitDisplayMode(GLUT_RGBA | GLUT_SINGLE);
	glutCreateWindow(PROGRAM_NAME " v" PROGRAM_VERSION " - GLUT");
	glutReshapeWindow(RENDER_WIDTH, RENDER_HEIGHT);
	
	glSharedInit(
		timerStart, player,
		reset
	);
	
	glutKeyboardFunc(input);
	glutSpecialFunc(inputSpecial);
	glutDisplayFunc(draw);
	glutTimerFunc(1000 / MAX_FPS, drawLoop, 0);
	
	glutMainLoop();
	return;
}