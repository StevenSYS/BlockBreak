/* Xlib Implementation */
#include <X11/Xlib.h>
#include <X11/keysym.h>
#ifndef XLIB_LEAGCY
	#include <X11/XKBlib.h>
#endif
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <random.h>
#ifdef ENABLE_SCREENSHOT
	#include <sImpl.h>
#endif

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
		switch (
		#ifdef XLIB_LEGACY
			XKeycodeToKeysym(
				display,
				event.xkey.keycode,
				event.xkey.state & ShiftMask ? 1 : 0
			)
		#else
			XkbKeycodeToKeysym(
				display,
				event.xkey.keycode,
				0,
				event.xkey.state & ShiftMask ? 1 : 0
			)
		#endif
		) {
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
			#ifdef ENABLE_SCREENSHOT
			case XK_s:
			case XK_S:
				screenshot_take = 1;
				break;
			#endif
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
	#ifdef ENABLE_SCREENSHOT
	screenshot_setColor(red, green, blue);
	#endif
	return;
}

void impl_drawNumber(
	signed short x, signed short y,
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
	#ifdef ENABLE_SCREENSHOT
	screenshot_number(x, y, number);
	#endif
	return;
}

void impl_drawFillRect(
	signed short x, signed short y,
	unsigned short width, unsigned short height
) {
	XFillRectangle(
		display,
		window,
		gc,
		x, y,
		width, height
	);
	#ifdef ENABLE_SCREENSHOT
	screenshot_fillRect(x, y, width, height);
	#endif
	return;
}

/* Misc. */
void impl_loopStart() {
	XClearWindow(display, window);
	#ifdef ENABLE_SCREENSHOT
	screenshot_start("Xlib");
	#endif
	return;
}

void impl_loopEnd() {
	XFlush(display);
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
		
		while (XPending(display)) {
			XNextEvent(display, &event);
			if (event.type == KeyPress) {
				handleInput();
			}
		}
		
		draw();
		
		/* FIXME: "Processor: 24.7%" - GNOME System Monitor */
		while (clock() < lastTime + (CLOCKS_PER_SEC / MAX_FPS));
	}
	
	XCloseDisplay(display);
	return;
}