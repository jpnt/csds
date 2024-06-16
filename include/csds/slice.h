#ifndef CSDS_SLICE_H
#define CSDS_SLICE_H

#include <stddef.h>

typedef struct {
	void* ptr;
	size_t type_size;
	size_t len;
} Slice;

Slice* slice_create(void* ptr, size_t type_size, size_t start, size_t end);
int slice_stack_create(Slice* slice, void* ptr, size_t type_size, size_t start, size_t end);
void slice_destroy(Slice* slice);
void* slice_valueat(Slice* slice, size_t idx);

#endif // !CSDS_SLICE_H
