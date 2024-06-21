#ifndef CSDS_SLICE_H
#define CSDS_SLICE_H

#include <stddef.h>

typedef struct {
	void* addr; /* pointer without a type, simply an address */
	size_t type_size; /* sizeof(some_type), in order to do pointer arithmetic */
	size_t len; /* length of the slice to prevent out of bounds errors */
} Slice;

/* allocates a new slice */
extern Slice* slice_alloc(void* addr, size_t type_size, size_t start, size_t end);
/* frees memory allocated for the slice */
extern void slice_dealloc(Slice* slice);
/* sets a slice on the stack */
extern int slice_init(Slice* slice, void* addr, size_t type_size, size_t start, size_t end);
/* returns the value at the specified index in the slice */
extern void* slice_valueat(Slice* slice, size_t idx);

#endif /* !CSDS_SLICE_H */
