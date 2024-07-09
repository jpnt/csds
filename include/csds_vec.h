#ifndef CSDS_VEC_H
#define CSDS_VEC_H

#include "csds_error.h"
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

#ifndef CSDS_VEC_INITIAL_CAP
#define CSDS_VEC_INITIAL_CAP	16
#endif /* !CSDS_VEC_INITIAL_CAP */

#ifndef CSDS_VEC_GROWTH_FACTOR
#define CSDS_VEC_GROWTH_FACTOR	1.5
#endif /* !CSDS_VEC_GROWTH_FACTOR */

/* Get the header from the array pointer */
#define VEC_HEADER_OF(arr) (struct csds_vec_header*)(arr)-1

typedef struct csds_vec_header VecHeader;

struct csds_vec_header {
	size_t len; /* Length/Number of elements present in the vector */
	size_t cap; /* Current capacity of elements in the vector */
	size_t item_size; /* Size of each item in the vector */
	/* T* arr */
};

/* Allocate new vector with the specified initial capacity */
extern int vec_alloc(void** arr, size_t item_size, size_t init_cap);
/* Free the vector and optionally free all associated memory */
extern int vec_dealloc(void* arr);
/* Grow/Reallocate the vector to accommodate more items */
extern int vec_grow(void** arr);
/* Insert an item at the specified index */
extern int vec_insert(void* arr, size_t item_idx, const void* item);
/* Remove the item at the specified index and copy it to removed */
extern int vec_remove(void* arr, size_t item_idx, void* removed);
/* Push an item onto the end of the vector */
extern int vec_push(void* arr, const void* item);
/* Pop and the item from the end of the vector and copy it to popped */
extern int vec_pop(void* arr, void* popped);

#endif /* !CSDS_VEC_H */
