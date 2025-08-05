/* Xlib Implementation */
#define _DEFAULT_SOURCE
#include <X11/Xlib.h>
#include <X11/keysym.h>
#ifndef XLIB_LEAGCY
	#include <X11/XKBlib.h>
#endif
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <random.h>
#include <input.h>
#ifdef ENABLE_SCREENSHOT
	#include <sImpl.h>
#endif

#include "entity.h"
#include "progInfo.h"

static char running = 1;
static char buffer[11];

static clock_t lastTime;
static clock_t sleepTime;

static Display *display;
static Window window;
static XEvent event;
static GC gc;

static void handleInput() {
	if (event.type == KeyPress) {
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
				input(INPUT_UP);
				break;
			case XK_Down:
				input(INPUT_DOWN);
				break;
			case XK_Left:
				input(INPUT_LEFT);
				break;
			case XK_Right:
				input(INPUT_RIGHT);
				break;
			case XK_Return:
				input(INPUT_RESET);
				break;
			case XK_Escape:
				running = 0;
				break;
			#ifdef ENABLE_SCREENSHOT
			case XK_s:
			case XK_S:
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
	sImpl_setColor(red, green, blue);
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
	sImpl_number(x, y, number);
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
	sImpl_fillRect(x, y, width, height);
	#endif
	return;
}

/* Misc. */
void impl_loopStart() {
	XClearWindow(display, window);
	#ifdef ENABLE_SCREENSHOT
	sImpl_start("Xlib");
	#endif
	return;
}

void impl_loopEnd() {
	XFlush(display);
	#ifdef ENABLE_SCREENSHOT
	sImpl_end();
	#endif
	return;
}

void impl_init(
	int argc, char *argv[],
	void (*draw)()
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
		
		sleepTime = (CLOCKS_PER_SEC / MAX_FPS) - (clock() - lastTime);
		if (sleepTime > 0) {
			usleep(sleepTime);
		}
		
		while (XPending(display)) {
			XNextEvent(display, &event);
			if (event.type == KeyPress) {
				handleInput();
			}
		}
	}
	
	XCloseDisplay(display);
	return;
}