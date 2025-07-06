/* Standard C Library Implementation */
#include <stdio.h>
#include <string.h>

#include "strings.h"
#include "hssImpl.h"
#include "progInfo.h"

typedef enum {
	FILE_NONE,
	FILE_NEWFILE,
	FILE_BROKEN
} FILE_STATUS;

static char fileStatus = 0;

static FILE *file;

unsigned int hssImpl_get() {
	char buffer[HSSIMPL_LENGTH_BUFFER];
	unsigned int newScore = 0;
	
	if (file == NULL) {
		printf(HSSIMPL_STRING_FILE_NOTINIT);
		return 0;
	} else if (fileStatus == 0) {
		if (fgets(buffer, HSSIMPL_LENGTH_BUFFER, file) == NULL && strlen(buffer) > 0) {
			perror(HSSIMPL_STRING_FILE_FAILREAD);
			return 0;
		} else if (strlen(buffer) <= 0) {
			fprintf(stderr, HSSIMPL_STRING_FILE_SMALL, strlen(buffer));
			return 0;
		} else {
			if (strncmp(buffer, HSSIMPL_SIGNATURE, strlen(HSSIMPL_SIGNATURE)) == 0) {
				for (unsigned char i = 0; i < 4; i++) {
					newScore += *(buffer + (strlen(HSSIMPL_SIGNATURE) + i)) << (i * 8);
				}
			} else {
				fprintf(stderr, HSSIMPL_STRING_FILE_NOTVALID);
				fileStatus = FILE_BROKEN;
			}
		}
	}
	return newScore;
}

void hssImpl_set(unsigned int highScore) {
	if (fileStatus == FILE_BROKEN) {
		fprintf(stderr, HSSIMPL_STRING_FILE_NOTVALID);
		return;
	}
	if (file == NULL) {
		printf(HSSIMPL_STRING_FILE_NOTINIT);
	} else {
		file = fopen(HSSIMPL_FILENAME, "w+");
		if (file == NULL) {
			perror(HSSIMPL_STRING_FILE_FAILOPEN_WPMODE);
			return;
		}
		fprintf(file, HSSIMPL_SIGNATURE);
		fwrite(
			&highScore,
			1,
			sizeof(unsigned int),
			file
		);
		fflush(file);
	}
	return;
}

void hssImpl_open() {
	if (fopen(HSSIMPL_FILENAME, "r") == NULL) {
		perror(HSSIMPL_STRING_FILE_FAILOPEN_RMODE);
		file = fopen(HSSIMPL_FILENAME, "w+");
		if (file == NULL) {
			perror(HSSIMPL_STRING_FILE_FAILOPEN_WPMODE);
		} else {
			fileStatus = FILE_NEWFILE;
			hssImpl_set(0);
		}
	} else {
		file = fopen(HSSIMPL_FILENAME, "r+");
	}
	return;
}

void hssImpl_close() {
	if (file == NULL) {
		printf(HSSIMPL_STRING_FILE_NOTINIT);
	} else {
		if (fclose(file) == EOF) {
			perror(HSSIMPL_STRING_FILE_FAILCLOSE);
		}
	}
	return;
}