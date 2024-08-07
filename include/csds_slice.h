#ifndef CSDS_SLICE_H
#define CSDS_SLICE_H

#include <stdio.h>	/* fprintf */
#include <stdlib.h>	/* malloc, free */
#include <inttypes.h>	/* for printing size_t to the screen */

#ifndef CSDS_SLICE_ALLOC
#define CSDS_SLICE_ALLOC(size)		malloc(size);
#endif /* !CSDS_SLICE_ALLOC */
#ifndef CSDS_SLICE_DEALLOC
#define CSDS_SLICE_DEALLOC(ptr)		free(ptr);
#endif /* !CSDS_SLICE_DEALLOC */

typedef struct csds_slice Slice;

struct csds_slice {
	void* addr; /* pointer without a type, simply an address */
	size_t type_size; /* sizeof(some_type), in order to do pointer arithmetic */
	size_t len; /* length of the slice to prevent out of bounds errors */
};

/* Allocate a new slice */
extern struct csds_slice* slice_alloc(void* addr, size_t type_size, size_t start_idx, size_t end_idx);
/* Free memory allocated for the slice */
extern void slice_dealloc(struct csds_slice* slice);
/* Sets/Initializes slice values */
extern int slice_init(struct csds_slice* slice, void* addr, size_t type_size, size_t start_idx, size_t end_idx);
/* Returns the value at the specified index in the slice */
extern void* slice_valueat(struct csds_slice* slice, size_t idx);

#endif /* !CSDS_SLICE_H */
