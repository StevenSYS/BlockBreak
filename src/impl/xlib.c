/* Xlib Implementation */
#include <X11/Xlib.h>
#include <X11/keysym.h>
#include <X11/XKBlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <random.h>

#include "entity.h"
#include "progInfo.h"

static void (*main_reset)();

static char running = 1;
static char buffer[11];
static char *main_timerStart;

static entity_t *main_player;

static clock_t lastTime;

static Display *display;
static Window window;
static XEvent event;
static GC gc;

static void handleInput() {
	if (event.type == KeyPress) {
		random_increase();
		switch (XkbKeycodeToKeysym(display, event.xkey.keycode, 0, event.xkey.state & ShiftMask ? 1 : 0)) {
			case XK_Up:
				*main_timerStart = 1;
				main_player->direction = ENTITY_DIR_UP;
				break;
			case XK_Down:
				*main_timerStart = 1;
				main_player->direction = ENTITY_DIR_DOWN;
				break;
			case XK_Left:
				*main_timerStart = 1;
				main_player->direction = ENTITY_DIR_LEFT;
				break;
			case XK_Right:
				*main_timerStart = 1;
				main_player->direction = ENTITY_DIR_RIGHT;
				break;
			case XK_Return:
				main_reset();
				break;
			case XK_Escape:
				running = 0;
				break;
		}
	}
	return;
}

/* Drawing */
void impl_setColor(
	unsigned char red,
	unsigned char green,
	unsigned char blue
) {
	XSetForeground(
		display,
		gc,
		(blue + (green << 8) + (red << 16))
	);
	return;
}

void impl_drawNumber(
	short x, short y,
	unsigned int number
) {
	sprintf(buffer, "%u", number);
	XDrawString(
		display,
		window,
		gc,
		x, y + FONT_HEIGHT,
		buffer,
		strlen(buffer)
	);
	return;
}

void impl_drawFillRect(
	short x, short y,
	unsigned short width, unsigned short height
) {
	XFillRectangle(
		display,
		window,
		gc,
		x, y,
		width, height
	);
	return;
}

/* Misc. */
void impl_loopStart() {
	XClearWindow(display, window);
	return;
}

void impl_loopEnd() {
	XFlush(display);
	return;
}

void impl_init(
	int argc, char *argv[],
	char *timerStart, entity_t *player,
	void (*reset)(), void (*draw)()
) {
	int screen;
	
	display = XOpenDisplay(NULL);
	
	if (display == NULL) {
		fprintf(stderr, "ERROR: Failed to open display\n");
		return;
	}
	
	screen = DefaultScreen(display);
	window = XCreateSimpleWindow(
		display,
		RootWindow(display, screen),
		0, 0,
		RENDER_WIDTH, RENDER_HEIGHT,
		1,
		WhitePixel(display, screen),
		BlackPixel(display, screen)
	);
	
	XStoreName(
		display,
		window,
		PROGRAM_NAME " v" PROGRAM_VERSION " - Xlib"
	);
	
	XSelectInput(display, window, ExposureMask | KeyPressMask);
	XMapWindow(display, window);
	gc = XCreateGC(display, window, 0, NULL);
	
	main_timerStart = timerStart;
	main_player = player;
	main_reset = reset;
	
	while (1) {
		XNextEvent(display, &event);
		if (
			event.type == Expose &&
			!event.xexpose.count
		) {
			break;
		}
	}
	
	while (running) {
		lastTime = clock();
		
		draw();
		
		while (XPending(display)) {
			XNextEvent(display, &event);
			if (event.type == KeyPress) {
				handleInput();
			}
		}
		
		while (clock() < lastTime + (CLOCKS_PER_SEC / MAX_FPS));
	}
	
	XCloseDisplay(display);
	return;
}