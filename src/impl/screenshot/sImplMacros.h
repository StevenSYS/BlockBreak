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
		
		#define SIMPL_FPRINTF(_fptr, ...) fprintf(_fptr, __VA_ARGS__)
		#define SIMPL_FOPEN(_filename, _mode) fopen(_filename, _mode)
		#define SIMPL_FCLOSE(_stream) fclose(_stream)
		#define SIMPL_SNPRINTF(_str, _size, ...) snprintf(_str, _size, __VA_ARGS__)
		#define SIMPL_FWRITE(_ptr, _size, _nmemb, _stream) fwrite(_ptr, _size, _nmemb, _stream)
		#define SIMPL_ERROR(_message) fprintf(stderr, "ERROR: " _message "\n");
		#define SIMPL_NAME "libc"
		
		static FILE *file;
	#elif SIMPL == 2 /* SDL3 */
		#ifdef __APPLE
			#include <SDL.h>
		#else
			#include <SDL3/SDL.h>
		#endif
		
		#define SIMPL_FPRINTF(_context, ...) SDL_IOprintf(_context, __VA_ARGS__)
		#define SIMPL_FOPEN(_file, _mode) SDL_IOFromFile(_file, _mode)
		#define SIMPL_FCLOSE(_context) SDL_CloseIO(_context)
		#define SIMPL_SNPRINTF(_text, _maxlen, ...) SDL_snprintf(_text, _maxlen, __VA_ARGS__)
		#define SIMPL_FWRITE(_ptr, _size, _unused, _context) SDL_WriteIO(_context, _ptr, _size)
		#define SIMPL_ERROR(_message) SDL_LogError(SDL_LOG_CATEGORY_ERROR, "ERROR: " _message ": %s\n", SDL_GetError())
		#define SIMPL_NAME "SDL3"
		
		static SDL_IOStream *file;
	#elif SIMPL == 3 /* FMOD */
		#include <fmod.h>
		#include <stdio.h>
		#include <stdarg.h>
		#include <string.h>
		
		typedef struct FMOD_OS_FILE FMOD_OS_FILE;
		
		FMOD_RESULT FMOD_OS_File_Open(const char *name, int mode, unsigned int *fileSize, FMOD_OS_FILE **handle);
		FMOD_RESULT FMOD_OS_File_Close(FMOD_OS_FILE *handle);
		FMOD_RESULT FMOD_OS_File_Read(FMOD_OS_FILE *handle, void *buf, unsigned int count, unsigned int *read);
		FMOD_RESULT FMOD_OS_File_Write(FMOD_OS_FILE *handle, const void *buffer, unsigned int bytesToWrite, bool flush);
		FMOD_RESULT FMOD_OS_File_Seek(FMOD_OS_FILE *handle, unsigned int offset);
		
		#define SIMPL_FPRINTF(_fptr, ...) fmod_fprintf(_fptr, __VA_ARGS__)
		#define SIMPL_FOPEN(_filename, _mode) fmod_fopen(_filename, _mode)
		#define SIMPL_FCLOSE(_stream) FMOD_OS_File_Close(_stream)
		#define SIMPL_SNPRINTF(_str, _size, ...) snprintf(_str, _size, __VA_ARGS__)
		#define SIMPL_FWRITE(_ptr, _size, _nmemb, _stream) FMOD_OS_File_Write(_stream, _ptr, _size, true)
		#define SIMPL_ERROR(_message) fprintf(stderr, "ERROR: " _message "\n")
		#define SIMPL_NAME "FMOD"
		
		/* Function Wrappers */
		static unsigned int fileSize;
		
		static FMOD_OS_FILE *fmod_fopen(
			const char *name,
			const char *mode
		) {
			FMOD_OS_FILE *ret;
			FMOD_OS_File_Open(
				name,
				1,
				&fileSize,
				&ret
			);
			return ret;
		}
		
		static void fmod_fprintf(
			FMOD_OS_FILE *handle,
			const char *format,
			...
		) {
			va_list args;
			va_start(args, format);
			vfprintf((FILE *)handle, format, args);
			va_end(args);
			return;
		}
		
		static FMOD_OS_FILE *file;
	#else
		#error "SIMPL is not set or is invalid"
		
		#ifndef NULL
			#define NULL 0
		#endif
		
		void dummy1(...) {}
		char *dummy2(...) { return NULL; }
		int dummy3(...) { return 0; }
		
		#define SIMPL_FPRINTF(_fptr, ...) dummy1()
		#define SIMPL_FOPEN(_filename, _mode) dummy2()
		#define SIMPL_FCLOSE(_stream) dummy3()
		#define SIMPL_SNPRINTF(_str, _size, ...) dummy1()
		#define SIMPL_FWRITE(_ptr, _size, _nmemb, _stream) dummy1()
		#define SIMPL_ERROR(_message) dummy1()
		#define SIMPL_NAME "Dummy"
		
		static void *file;
	#endif
#endif