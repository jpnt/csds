#ifndef CSDS_DEBUG_H
#define CSDS_DEBUG_H

/* flags to set in your programs */
/* #define __D_MEMORY_DEBUG */
/* #define __D_ASSERT_DEBUG */
/* #define __D_EXIT_CRASH */

#include <stddef.h> /* for malloc, calloc, realloc, free, etc */
#include <assert.h>
#include "datatypes.h"

/* required for memory debugger to be thread-safe */
extern void debug_mem_init(void (*lock)(void* mutex), void (*unlock)(void* mutex), void* mutex);
/* replaces malloc and records the c file and line where it was called */
extern void* debug_mem_malloc(size_t nmemb, size_t size, const char* file, uint line);
/* replaces calloc and records the c file and line where it was called */
extern void* debug_mem_calloc(size_t size, const char* file, uint line);
/* replaces realloc and records the c file and line where it was called */
extern void* debug_mem_realloc(void* ptr, size_t size, const char* file, uint line);
/* replaces free and records the c file and line where it was called */
extern void debug_mem_free(void* buf, const char* file, uint line);
/* add a comment to an allocation that can help identify its use */
extern int debug_mem_comment(void* buf, const char* comment);
/* print a list of all allocations made, their location, how much memory each has allocated,
 * freed, and how many allocations have been made. the min_allocs parameter can be set to avoid
 * printing any allocations that have been made fewer times than min_allocs */
extern void debug_mem_print(uint min_allocs);
/* allows you to clear all memory stored in the debugging system if you only want to record allocations after a specific point in your code */
extern void debug_mem_reset(void);
/* add up all memory consumed by mallocs and reallocs covered by the memory debugger */
extern size_t debug_mem_consumption(void);
/* query the size and place of allocation of a pointer */
extern int debug_mem_query(void* ptr, uint* line, const char** file, size_t* size);
/* query if a bit of memory is safe to access */
extern int debug_mem_test(void* ptr, size_t size, int ignore_not_found);
/* checks if any of the bounds of any allocation has been overwritten and reports where to stdout. the function returns -1 if any error was found */
extern int debug_mem_check(void);
/* replaces fopen and records the c file and line where it was called */
extern void* debug_mem_fopen(const char* filename, const char* mode, const char* file, uint line);
/* replaces fclose and records the c file and line where it was called */
extern void debug_mem_fclose(void* f, const char* file, uint line);
/* replaces assert and records the file and line where it was called */
extern int debug_assert(const char* condition, const char* file, uint line);
/* function guaranteed to crash, writes to address 0 */
extern void exit_crash(int status);

/* replace functions */
#ifdef __D_MEMORY_DEBUG
#define malloc(n) debug_mem_malloc(n, __FILE__, __LINE__)
#define calloc(n, m) debug_mem_calloc(n, m, __FILE__, __LINE__)
#define realloc(n, m) debug_mem_realloc(n, m, __FILE__, __LINE__)
#define free(n) debug_mem_free(n, __FILE__, __LINE__)
#define fopen(n, m) debug_mem_fopen(n, m, __FILE__, __LINE__)
#define fclose(n) debug_mem_fclose(n, __FILE__, __LINE__)
#endif /* __D_MEMORY_DEBUG */
#ifdef __D_ASSERT_DEBUG
#define assert(n) debug_assert(#n, __FILE__, __LINE__)
#endif /* __D_ASSERT_DEBUG */
#ifdef __D_EXIT_CRASH
#define exit(n) exit_crash(n)
#endif /* __D_EXIT_CRASH */

#endif /* !CSDS_DEBUG_H */
