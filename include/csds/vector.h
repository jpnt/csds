#ifndef CSDS_VECTOR_H
#define CSDS_VECTOR_H

#include <stddef.h>

typedef struct {
	void** items;
	size_t size;
	size_t capacity;
} Vec;

Vec* vec_create(size_t capacity);
void vec_destroy(Vec* vec);
void vec_grow(Vec* vec);

void vec_insert(Vec* vec, size_t item_idx, void* item);
void* vec_remove(Vec* vec, size_t item_idx);

void vec_push(Vec* vec, void* item);
void* vec_pop(Vec* vec);

#endif // !CSDS_VECTOR_H
