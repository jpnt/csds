/**
 * @file	csds_array.h
 * @brief	Header file for dynamic array implementation.
 */
#ifndef CSDS_ARRAY_H
#define CSDS_ARRAY_H

#include <stddef.h>

#ifndef CSDS_ARRAY_INITIAL_CAP
#define CSDS_ARRAY_INITIAL_CAP 4
#endif /* !CSDS_ARRAY_INITIAL_CAP */

/* concern: after realloc/grow can we get the header? */
typedef struct {
	size_t len;
	size_t cap;
} ArrayHeader;

#endif /* !CSDS_ARRAY_H */

/* Define ONCE in one of your C files */
#define CSDS_ARRAY_IMPL
#ifdef CSDS_ARRAY_IMPL

/* Get the header from the data pointer */
#define CSDS_ARRAY_HEADER_OF(ptr) ((ArrayHeader*)((char*)(ptr) - offsetof(ArrayHeader, data)))
#define array_len(arr) ((arr) ? CSDS_ARRAY_HEADER_OF(arr)->len : 0)
#define array_cap(arr) ((arr) ? CSDS_ARRAY_HEADER_OF(arr)->cap : 0)
#define array_dealloc(arr) ((arr) ? (free(CSDS_ARRAY_HEADER_OF(arr)), (arr)), (arr) = NULL : (void)0)

#endif /* CSDS_ARRAY_IMPL */
