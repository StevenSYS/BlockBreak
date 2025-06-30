#ifndef __SIMPLMACROS__
#define __SIMPLMACROS__
	#if SIMPL == 1 /* libc */
		#include <stdio.h>
		#ifdef SIMPL_INCSTRING
			#include <string.h>
		#endif
		
		#ifndef NULL
			#define NULL 0
		#endif
		#define SIMPL_FPRINTF fprintf
		#define SIMPL_FOPEN fopen
		#define SIMPL_FCLOSE fclose
		#define SIMPL_SNPRINTF snprintf
		#define SIMPL_FWRITE(_ptr, _size, _nmemb, _stream) fwrite(_ptr, _size, _nmemb, _stream)
		#define SIMPL_NAME "libc"
		
		static FILE *file;
	#elif SIMPL == 2 /* SDL3 */
		#ifdef __APPLE
			#include <SDL.h>
		#else
			#include <SDL3/SDL.h>
		#endif
		
		#define SIMPL_FPRINTF SDL_IOprintf
		#define SIMPL_FOPEN SDL_IOFromFile
		#define SIMPL_FCLOSE SDL_CloseIO
		#define SIMPL_SNPRINTF SDL_snprintf
		#define SIMPL_FWRITE(_ptr, _size, _nmemb, _stream) SDL_WriteIO(_stream, _ptr, _size)
		#define SIMPL_SDL_LOGERROR SDL_LogError(SDL_LOG_CATEGORY_ERROR, "%s\n", SDL_GetError());
		#define SIMPL_NAME "SDL3"
		
		static SDL_IOStream *file;
	#else
		#error "SIMPL is not set or is invalid"
		
		#ifndef NULL
			#define NULL 0
		#endif
		
		void dummy1(...) {}
		char *dummy2(...) { return NULL; }
		int dummy3(...) { return 0; }
		
		#define SIMPL_FPRINTF dummy1
		#define SIMPL_FOPEN dummy2
		#define SIMPL_FCLOSE dummy3
		#define SIMPL_SNPRINTF dummy1
		#define SIMPL_NAME "Dummy"
		
		static void *file;
	#endif
#endif