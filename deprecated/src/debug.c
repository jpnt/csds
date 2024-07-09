#include "../include/csds/debug.h"
#include <stdio.h>
#include <string.h>

DebugMem debug_mem_arr[__D_MAX_ALLOCATIONS];
uint debug_mem_arr_len = 0;
size_t bytes_allocated = 0;
size_t bytes_deallocated = 0;
/* mutex for concurrent programming */
void* debug_mem_mutex = NULL;
int (*debug_mem_mutex_lock)(void* mutex) = NULL;
int (*debug_mem_mutex_unlock)(void* mutex) = NULL;

void debug_mem_mutex_init(int (*lock)(void* mutex), int (*unlock)(void* mutex), void* mutex) {
	debug_mem_mutex = mutex;
	debug_mem_mutex_lock = lock;
	debug_mem_mutex_unlock = unlock;
}

void* debug_mem_malloc(size_t size, const char* file, uint line) {
	void* ptr = NULL;

	if (debug_mem_mutex != NULL) {
		debug_mem_mutex_lock(debug_mem_mutex);
	}

#ifdef __D_MEMORY_DEBUG_FULL
	printf("(DEBUG) debug_mem_malloc: Allocating %lu bytes at %p (%s:%u)\n", size, ptr, file, line);
#endif /* __D_MEMORY_DEBUG_FULL */

	ptr = malloc(size); /* //TODO: FIX INFINITE RECURSION */

	if (ptr == NULL) {
		fprintf(stderr, "(ERROR) debug_mem_malloc: Memory allocation of %u bytes failed (%s:%u)\n",
				(uint)size, file, line);
		if (debug_mem_mutex != NULL) {
			debug_mem_mutex_unlock(debug_mem_mutex);
			debug_exit_abort(1);
		}
	}
	/*  */
	/* if (debug_mem_init(debug_mem_arr_len, ptr, size, 0, file, NULL, line, 0) == -1) { */
	/* 	free(ptr); */
	/* 	debug_exit_abort(2); */
	/* } */

	debug_mem_arr_len+=1;

	if (debug_mem_mutex != NULL) {
		debug_mem_mutex_unlock(debug_mem_mutex);
	}

	return ptr;
}

/* //TODO */
void* debug_mem_calloc(size_t nmemb, size_t size, const char* file, uint line);

/* //TODO */
void* debug_mem_realloc(void* ptr, size_t size, const char* file, uint line);

void debug_mem_free(void* ptr, const char* file, uint line) {
	uint alloc_line = 0;
	char alloc_file[256];
	size_t alloc_size = 0;
	uint i = 0;

	if (debug_mem_mutex != NULL) {
		debug_mem_mutex_lock(debug_mem_mutex);
	}

	if (debug_mem_query(ptr, &i, &alloc_line, alloc_file, &alloc_size) == -1) {
		fprintf(stderr, "(ERROR) debug_mem_free: Data at %p was not found after debug_mem_query (%s:%u)\n",
				ptr, file, line);
		return;
	}

	/* fill dealloc_file and dealloc_line parameters in the alloc debug_mem struct to reference the dealloc struct */
	/* debug_mem_init(i, NULL, 0, 0, NULL, file, 0, line); */

	/* fill the dealloc debug_mem entry */
	/* debug_mem_init(debug_mem_arr_len, (void*)__D_MAGIC_NUMBER, 0, alloc_size, alloc_file, file, alloc_line, line); */
	/* debug_mem_arr_len+=1; */

#ifdef __D_MEMORY_DEBUG_FULL
	printf("(DEBUG) debug_mem_free: Deallocating %u bytes at %p (%s:%u)\n", (uint)alloc_size, ptr, file, line);
	printf("(DEBUG) debug_mem_free: Deallocation references allocation (%s:%u)\n", alloc_file, alloc_line);
#endif /* __D_MEMORY_DEBUG_FULL */

	free(ptr);
	if (debug_mem_mutex != NULL) {
		debug_mem_mutex_unlock(debug_mem_mutex);
	}
}

int debug_mem_query(void* ptr, uint* debug_mem_arr_idx, uint* line, char* file, size_t* size) {
	uint i;

	if (ptr == NULL) {
		fprintf(stderr, "(ERROR) debug_mem_query: Cannot pass a NULL ptr to query\n");
	}

	if (debug_mem_mutex != NULL) {
		debug_mem_mutex_lock(debug_mem_mutex);
	}

	for (i=0; i<debug_mem_arr_len; i++) {
		if (debug_mem_arr[i].ptr == ptr) {
			if (debug_mem_arr_idx != NULL) {
				*debug_mem_arr_idx = i;
			}
			/* if (line != NULL) { */
			/* 	*line = debug_mem_arr[i].alloc_line; */
			/* } */
			if (file != NULL) {
				/* strncpy(file, debug_mem_arr[i].alloc_file, sizeof(debug_mem_arr[i].alloc_file)-1); */
				/* debug_mem_arr[i].alloc_file[sizeof(debug_mem_arr[i].alloc_file)-1] = '\0'; */
			}
			if (size != NULL) {
				/* one of them will be zero, so just sum them up */
				/* *size = debug_mem_arr[i].alloc_size + debug_mem_arr[i].dealloc_size; */
			}
			if (debug_mem_mutex != NULL) {
				debug_mem_mutex_unlock(debug_mem_mutex);
			}
			return 0;
		}
	}

	if (debug_mem_mutex != NULL) {
		debug_mem_mutex_unlock(debug_mem_mutex);
	}
#ifdef __D_MEMORY_DEBUG_FULL
	printf("(DEBUG) debug_mem_query: Allocation at %p not found\n", ptr);
#endif /* __D_MEMORY_DEBUG_FULL */
	return -1;
}

/* //TODO */
int debug_mem_check(void);

/* int debug_mem_init(uint debug_mem_arr_idx, void* ptr, size_t alloc_size, size_t dealloc_size, */
/* 		const char* alloc_file, const char* dealloc_file, uint alloc_line, uint dealloc_line) { */
/* 	DebugMem* debug_mem; */
/*  */
/* 	if (debug_mem_arr_idx >= __D_MAX_ALLOCATIONS) { */
/* 		fprintf(stderr, "(ERROR) debug_mem_init: Exceeded maximum number of allocations (%d)\n", */
/* 				__D_MAX_ALLOCATIONS); */
/* 		return -1; */
/* 	} */
/*  */
/* 	debug_mem = &debug_mem_arr[debug_mem_arr_idx]; */
/*  */
/* 	if (ptr != NULL) { */
/* 		debug_mem->ptr = ptr; */
/* 	} */
/* 	if (alloc_file != NULL) { */
/* 		debug_mem_strncpy(debug_mem->alloc_file, alloc_file, sizeof(debug_mem->alloc_file) - 1); */
/* 	} */
/* 	if (dealloc_file != NULL) { */
/* 		debug_mem_strncpy(debug_mem->dealloc_file, dealloc_file, sizeof(debug_mem->dealloc_file) - 1); */
/* 	} */
/* 	if (alloc_size != 0) { */
/* 		debug_mem->alloc_size = alloc_size; */
/* 		bytes_allocated+=alloc_size; */
/* 	} */
/* 	if (dealloc_size != 0) { */
/* 		debug_mem->dealloc_size = dealloc_size; */
/* 		bytes_deallocted+=dealloc_size; */
/* 	} */
/* 	if (alloc_line != 0) { */
/* 		debug_mem->alloc_line = alloc_line; */
/* 	} */
/* 	if (dealloc_line != 0) { */
/* 		debug_mem->dealloc_line = dealloc_line; */
/* 	} */
/*  */
 	/* debug_mem_arr_len is incremented separately */ 
/* 	return 0; */
/* } */

char* debug_mem_strncpy(char* dest, const char* src, size_t dest_size) {
	char* ret;

	if (dest_size == 0) {
#ifdef __D_MEMORY_DEBUG_FULL
		printf("(DEBUG) debug_mem_strncpy: Did not copy anything (dest: %s, src: %s, size: %u)\n",
				dest, src, (uint)dest_size);
#endif /* __D_MEMORY_DEBUG_FULL */
		return NULL;
	}

	ret = strncpy(dest, src, dest_size);
	dest[dest_size - 1] = '\0';

#ifdef __D_MEMORY_DEBUG_FULL
	printf("(DEBUG) debug_mem_strncpy: Copied %s to %s (size: %lu)\n", src, dest, dest_size);
#endif /* __D_MEMORY_DEBUG_FULL */

	return ret;
}

void debug_exit_abort(int status) {
	fprintf(stderr, "(ERROR) debug_exit_crash: Exiting with abort (code: %d)\n", status);
	abort();
}

