#ifndef CSDS_DEBUG_H
#define CSDS_DEBUG_H

/* flags to set in your programs */
/* #define __D_MEMORY_DEBUG_FULL */
/* #define __D_MEMORY_DEBUG */
/* #define __D_EXIT_ABORT */

#include "datatypes.h"
#include <stdlib.h>

/* length of debug_mem_arr, see debug.c */
#ifndef __D_MAX_ALLOCATIONS
#define __D_MAX_ALLOCATIONS 1024
#endif /* !__D_MAX_ALLOCATIONS */

#define __D_MAGIC_NUMBER 0xDEADBEEF

typedef struct {
	char alloc_file[256]; /* filename where the allocation occured */
	char dealloc_file[256]; /* filename where the deallocation occured */
	size_t alloc_size; /* total size allocated */
	size_t dealloc_size; /* total size deallocated */
	void* ptr; /* pointer to memory which was (de)allocated */
	uint alloc_line; /* the line number where the (de)allocation occured */
	uint dealloc_line; /* the line number where the dealloctaion occured */
} DebugMem;

/* global variables, see debug.c */
extern DebugMem debug_mem_arr[]; /* array of all allocations */
extern uint debug_mem_arr_len; /* length of array, serves as a counter for (de)allocations */
extern size_t bytes_allocated; /* number of bytes that were allocated */
extern size_t bytes_deallocated; /* number of bytes that were freed/deallocated */
extern void* debug_mem_mutex; /* mutual exclusion type */
extern int (*debug_mem_mutex_lock)(void* mutex); /* lock the debug_mutex */
extern int (*debug_mem_mutex_unlock)(void* mutex); /* unlock the debug_mutex */


/* initialize mutex values to ensure that struct has mutual exclusion access to the data */
extern void debug_mem_mutex_init(int (*lock)(void* mutex), int (*unlock)(void* mutex), void* mutex);
/* replaces malloc and records the c file and line where it was called */
extern void* debug_mem_malloc(size_t size, const char* file, uint line);
/* replaces calloc and records the c file and line where it was called */
extern void* debug_mem_calloc(size_t nmemb, size_t size, const char* file, uint line);
/* replaces realloc and records the c file and line where it was called */
extern void* debug_mem_realloc(void* ptr, size_t size, const char* file, uint line);
/* replaces free and records the c file and line where it was called */
extern void debug_mem_free(void* ptr, const char* file, uint line);
/* query the size, place and index of debug_mem_arr of an allocation of a pointer */
extern int debug_mem_query(void* ptr, uint* debug_mem_arr_idx, uint* line, char* file, size_t* size);
/* checks if any of the bounds of any allocation has been overwritten and reports where to stdout */
extern int debug_mem_check(void);
/* initialize debug_mem_arr[i] values, without incrementing the debug_mem_arr_len;
 * intended to be used by other functions; ignores NULL/0 values and does not initialize them */
extern int debug_mem_init(uint debug_mem_arr_idx, void* ptr, size_t alloc_size, size_t dealloc_size,
		const char* alloc_file, const char* dealloc_file, uint alloc_line, uint dealloc_line);
/* copies a string and ensures it is null-terminated */
extern char* debug_mem_strncpy(char* dest, const char* src, size_t dest_size);

/* function guaranteed to abort execution */
extern void debug_exit_abort(int status);

/* provides full memory debugging, i.e. more printing to the screen */
#ifdef __D_MEMORY_DEBUG_FULL
#define __D_MEMORY_DEBUG
#endif /* __D_MEMORY_DEBUG_FULL */

/* replaces functions */
#ifdef __D_MEMORY_DEBUG
#define malloc(n) debug_mem_malloc(n, __FILE__, __LINE__)
#define calloc(n, m) debug_mem_calloc(n, m, __FILE__, __LINE__)
#define realloc(n, m) debug_mem_realloc(n, m, __FILE__, __LINE__)
#define free(n) debug_mem_free(n, __FILE__, __LINE__)
#endif /* __D_MEMORY_DEBUG */

#ifdef __D_EXIT_ABORT
#define exit(n) debug_exit_abort(n)
#endif /* __D_EXIT_ABORT */

#endif /* !CSDS_DEBUG_H */
