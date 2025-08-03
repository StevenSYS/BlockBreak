#ifndef __HSSIMPL__
#define __HSSIMPL__

#ifdef FILENAME83
	#define HSSIMPL_FILENAME "HGHSCORE.1HS"
#else
	#define HSSIMPL_FILENAME "highScore.1hs"
#endif
#define HSSIMPL_SIGNATURE "1HS\x57\xE6\xE4\x56\x50"
#define HSSIMPL_LENGTH_BUFFER 20

unsigned int hssImpl_get();

void hssImpl_set(unsigned int highScore);

void hssImpl_open();

void hssImpl_close();

#endif