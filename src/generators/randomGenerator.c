#!/bin/tcc -run
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
	srand(510);
	
	FILE *file = fopen("../random/random.c", "w");
	
	if (file == NULL) {
		fprintf(stderr, "ERROR: Failed to open/make file\n");
		return 1;
	}
	
	fprintf(file, "static const unsigned char table[256] = {\n");
	for (unsigned char y = 0; y < 16; y++) {
		fprintf(file, "	");
		for (unsigned char x = 0; x < 16; x++) {
			fprintf(file, "%u", (rand() % 255) % 12);
			if ((x != 15) || (y != 15)) {
				fprintf(file, ", ");
			}
		}
		fprintf(file, "\n");
	}
	fprintf(file, "};\n");
	fprintf(file, "static unsigned char index = 0;\n\n"),
	fprintf(file, "void random_increase() {\n");
	fprintf(file, "\t/*\n");
	fprintf(file, "\t\tSince this is a unsigned char,\n");
	fprintf(file, "\t\tit will loop back to 0 when it goes over 255\n");
	fprintf(file, "\t*/\n");
	fprintf(file, "\tindex++;\n");
	fprintf(file, "\treturn;\n");
	fprintf(file, "}\n");
	fprintf(file, "\n");
	fprintf(file, "unsigned char random_get() {\n");
	fprintf(file, "\trandom_increase();\n");
	fprintf(file, "\treturn table[index];\n");
	fprintf(file, "}");
	return 0;
}