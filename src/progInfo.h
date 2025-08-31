#ifndef __PROGINFO__
#define __PROGINFO__

/* - Program - */
#define PROGRAM_NAME "BlockBreakC"
#define PROGRAM_VERSION "1.2pre"

/* - Render - */
#ifndef RENDER_WIDTH
	#define RENDER_WIDTH 640
#endif
#ifndef RENDER_HEIGHT
	#define RENDER_HEIGHT 472
#endif
/* Safe Guards */
#if RENDER_WIDTH < 1
	#undef RENDER_WIDTH
	#define RENDER_WIDTH 1
#endif
#if RENDER_HEIGHT < 1
	#undef RENDER_HEIGHT
	#define RENDER_HEIGHT 1
#endif

/* - Player - */
#ifndef PLAYER_SPEED
	#define PLAYER_SPEED RENDER_HEIGHT / 59
#endif
#ifndef PLAYER_WIDTH
	#define PLAYER_WIDTH RENDER_WIDTH / 40
#endif
#ifndef PLAYER_HEIGHT
	#define PLAYER_HEIGHT RENDER_WIDTH / 40
#endif
/* Start */
#define PLAYER_START_X (RENDER_WIDTH / 2) - (PLAYER_WIDTH / 2)
#define PLAYER_START_Y RENDER_HEIGHT - (PLAYER_HEIGHT * 3)
/* Safe Guards */
#if PLAYER_SPEED < 1
	#undef PLAYER_SPEED
	#define PLAYER_SPEED 1
#endif
#if PLAYER_WIDTH < 1
	#undef PLAYER_WIDTH
	#define PLAYER_WIDTH 1
#elif PLAYER_WIDTH > RENDER_WIDTH
	#undef PLAYER_WIDTH
	#define PLAYER_WIDTH RENDER_WIDTH
#endif
#if PLAYER_HEIGHT < 1
	#undef PLAYER_HEIGHT
	#define PLAYER_HEIGHT 1
#elif PLAYER_HEIGHT > RENDER_HEIGHT
	#undef PLAYER_HEIGHT
	#define PLAYER_HEIGHT RENDER_HEIGHT
#endif

/* - Screen - */

/* Edge */
#define SCREEN_EDGE_UP 0
#define SCREEN_EDGE_DOWN RENDER_HEIGHT - PLAYER_HEIGHT
#define SCREEN_EDGE_LEFT 0
#define SCREEN_EDGE_RIGHT RENDER_WIDTH - PLAYER_WIDTH

/* - Max - */
#ifndef MAX_LEVEL
	#define MAX_LEVEL 255
#endif
#define MAX_FPS 30
/* Safe Guards */
#if MAX_LEVEL < 1
	#undef MAX_LEVEL
	#define MAX_LEVEL 1
#endif
#if MAX_FPS < 1
	#undef MAX_FPS
	#define MAX_FPS 1
#endif

#endif