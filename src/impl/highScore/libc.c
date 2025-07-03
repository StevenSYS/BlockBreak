/* libc Implementation */
#include <stdio.h>
#include <string.h>

#include "hssImpl.h"

static unsigned int readBuffer;

unsigned int fileSize;

unsigned int hssImpl_get() {
	char buffer[strlen(HSSIMPL_SIGNATURE) + sizeof(unsigned int)];
	if (fileRead != NULL) {
		switch (FMOD_OS_File_Read(
			fileRead,
			buffer,
			8,
			&readBuffer
		)) {
			case FMOD_ERR_FILE_EOF:
				fprintf(stderr, "ERROR: Tried to read high score file while at the end of the file\n");
				return 0;
			case FMOD_ERR_FILE_BAD:
				fprintf(stderr, "ERROR: Failed to read high score file\n");
				return 0;
			default:
				break;
		}
		printf("%s\n%s\n", HSSIMPL_SIGNATURE, buffer);
		if (strcmp(HSSIMPL_SIGNATURE, buffer) != 0) {
			fprintf(stderr, "ERROR: High score signature doesn't match\n");
			return 0;
		}
		printf("%s\n", buffer);
	}
	return 0;
}

void hssImpl_set(unsigned int highScore) {
	char buffer[strlen(HSSIMPL_SIGNATURE) + sizeof(unsigned int)];
	if (FMOD_OS_File_Open(
		HSSIMPL_FILENAME,
		1,
		&fileSize,
		&fileWrite
	) != FMOD_OK) {
		fprintf(stderr, "ERROR: Failed to open high score file in writing mode\n");
	}
	
	fwrite(
		&highScore,
		strlen(HSSIMPL_SIGNATURE) + sizeof(unsigned int),
		1,
		(FILE *)fileWrite
	);
	
	if (FMOD_OS_File_Write(
		fileWrite,
		buffer,
		strlen(buffer),
		true
	) != FMOD_OK) {
		fprintf(stderr, "ERROR: Failed to write to high score file\n");
	}
	return;
}

void hssImpl_open() {
	switch (FMOD_OS_File_Open(
		HSSIMPL_FILENAME,
		0,
		&fileSize,
		&fileRead
	)) {
		case FMOD_ERR_FILE_NOTFOUND:
			hssImpl_set(0);
			break;
		case FMOD_ERR_FILE_BAD:
			fprintf(stderr, "ERROR: Failed to open high score file in reading mode\n");
			break;
		default:
			break;
	}
	
	if (fileSize == 0) {
		hssImpl_set(0);
	}
	return;
}

void hssImpl_close() {
	if (fileRead != NULL) {
		if (FMOD_OS_File_Close(fileRead) != FMOD_OK) {
			fprintf(stderr, "ERROR: Failed to close high score file (Read Mode)\n");
		}
	}
	if (fileWrite != NULL) {
		if (FMOD_OS_File_Close(fileWrite) != FMOD_OK) {
			fprintf(stderr, "ERROR: Failed to close high score file (Write Mode)\n");
		}
	}
	return;
}