#!/bin/tcc -run
#include <stdio.h>
#include <stdlib.h>

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

/* - Max - */
#ifndef MAX_BLOCKS
	#define MAX_BLOCKS 255
#endif
/* Safe Guards */
#if MAX_BLOCKS < 1
	#undef MAX_BLOCKS
	#define MAX_BLOCKS 1
#endif

/* - Macro Functions - */
#define HEADER(_ptr, _name) fprintf(_ptr, "/* [AUTO GENERATED] */\n#ifndef __" _name "__\n#define __" _name "__\n\n")
#define FOOTER(_ptr) fprintf(_ptr, " #endif\n")
#define ADDENTRY(_ptr, _w, _h) fprintf(_ptr, "\t{ %u, %u }", _w, _h)
#define LESSTHANSET(_var, _value) if (_var < _value) { _var = _value; }

int main() {
	FILE *file = fopen("../blockSizeList.h", "w");
	
	if (file == NULL) {
		fprintf(stderr, "ERROR: Failed to open/make file\n");
		return 1;
	}
	
	HEADER(file, "BLOCKSIZELIST");
	
	fprintf(file, "static const unsigned short blockSizeList[%u][2] = {\n", MAX_BLOCKS);
	ADDENTRY(file, 0, 0);
	fprintf(file, ",\n");
	for (unsigned short i = 1; i < MAX_BLOCKS - 1; i++) {
		unsigned short blockSize[2];
		blockSize[0] = (unsigned short)(RENDER_WIDTH / i);
		blockSize[1] = (unsigned short)(RENDER_HEIGHT / (i * 1.5));
		
		LESSTHANSET(blockSize[0], 1);
		LESSTHANSET(blockSize[1], 1);
		
		ADDENTRY(file, blockSize[0], blockSize[1]);
		
		if (i < MAX_BLOCKS - 2) {
			fprintf(file, ",");
		}
		
		fprintf(file, "\n");
	}
	fprintf(file, "};\n\n");
	
	FOOTER(file);
	return 0;
}