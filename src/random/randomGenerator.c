#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
	srand(510);
	
	FILE *randFile = fopen("random.c", "w");
	
	if (randFile == NULL) {
		fprintf(stderr, "ERROR: Failed to make file\n");
		return 1;
	}
	
	fprintf(randFile, "static const unsigned char table[256] = {\n");
	for (unsigned char y = 0; y < 16; y++) {
		fprintf(randFile, "	");
		for (unsigned char x = 0; x < 16; x++) {
			fprintf(randFile, "%u", (rand() % 255) % 12);
			if ((x != 15) || (y != 15)) {
				fprintf(randFile, ", ");
			}
		}
		fprintf(randFile, "\n");
	}
	fprintf(randFile, "};\n");
	fprintf(randFile, "static unsigned char index = 0;\n\n"),
	fprintf(randFile, "void random_increase() {\n");
	fprintf(randFile, "	/*\n");
	fprintf(randFile, "		Since this is a unsigned char,\n");
	fprintf(randFile, "		it will loop back to 0 when it goes over 255\n");
	fprintf(randFile, "	*/\n");
	fprintf(randFile, "	index++;\n");
	fprintf(randFile, "	return;\n");
	fprintf(randFile, "}\n");
	fprintf(randFile, "\n");
	fprintf(randFile, "unsigned char random_get() {\n");
	fprintf(randFile, "	random_increase();\n");
	fprintf(randFile, "	return table[index];\n");
	fprintf(randFile, "}");
	return 0;
}