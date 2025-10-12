#!/bin/tcc -run
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
	unsigned char x, y;
	
	FILE *file = fopen("../shared/random.c", "w");
	
	srand(510);
	
	if (file == NULL) {
		perror("ERROR: Failed to open file");
		return 1;
	}
	
	fprintf(
		file,
		"/* [AUTO GENERATED] */\n"
		"static const unsigned char table[256] = {\n"
	);
	
	for (y = 0; y < 16; y++) {
		fprintf(file, "	");
		for (x = 0; x < 16; x++) {
			fprintf(file, "%u", (rand() % 255) % 12);
			if ((x != 15) || (y != 15)) {
				fprintf(file, ", ");
			}
		}
		fprintf(file, "\n");
	}
	
	fprintf(
		file,
		"};\n\n"
		"unsigned char random_index = 0;\n\n"
		"unsigned char random_get() {\n"
		"\t/*\n"
		"\t\tSince this is a unsigned char,\n"
		"\t\tit will loop back to 0 when it goes over 255\n"
		"\t*/\n"
		"\trandom_index++;\n"
		"\treturn table[random_index];\n"
		"}"
	);
	return 0;
}