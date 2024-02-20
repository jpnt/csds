#ifndef CSDS_VECTOR_H
#define CSDS_VECTOR_H

#include <stddef.h>

typedef struct {
	void** items;
	size_t size;
	size_t capacity;
} Vec;

extern Vec* vec_create(size_t capacity);
extern void vec_destroy(Vec* vec);
extern void vec_grow(Vec* vec);

extern void vec_insert(Vec* vec, size_t item_idx, void* item);
extern void* vec_remove(Vec* vec, size_t item_idx);

extern void vec_push(Vec* vec, void* item);
extern void* vec_pop(Vec* vec);

#endif // !CSDS_VECTOR_H
