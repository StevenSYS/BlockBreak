#ifndef __HSSIMPL__
#define __HSSIMPL__

#define HSSIMPL_FILENAME "highScore.5hs"
#define HSSIMPL_SIGNATURE "5HS\x57\xE6\xE4\x56\x50"

unsigned int hssImpl_get();

void hssImpl_set(unsigned int highScore);

void hssImpl_open();

void hssImpl_close();

#endif