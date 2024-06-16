#include "../include/csds/slice.h"
#include <stdio.h>
#include <stdlib.h>

Slice* slice_create(void* ptr, size_t type_size, size_t start_idx, size_t end_idx) {
	// Invalid arguments
	if (ptr == NULL) {
		return NULL;
	}

	if (type_size < 1) {
		return NULL;
	}

	if (end_idx < start_idx) {
		return NULL;
	}

	Slice* slice = (Slice*) malloc(sizeof(Slice));
	if (slice == NULL) {
		perror("Error allocating memory for slice");
		exit(EXIT_FAILURE);
	}

	slice->ptr = ptr + start_idx * type_size;
	slice->type_size = type_size;
	end_idx+=1;
	slice->len = end_idx - start_idx;

	return slice;
}

void slice_destroy(Slice* slice) {
	if (slice == NULL) {
		return;
	}

	free(slice);
}

void* slice_valueat(Slice* slice, size_t idx) {
	if (idx >= slice->len) {
		perror("slice_valueat: invalid argument: slice length is smaller than index provided");
		exit(EXIT_FAILURE);
	}

	return slice->ptr + idx * slice->type_size;
}
