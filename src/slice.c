#include "../include/csds/slice.h"
#include <stdio.h>
#include <stdlib.h>

Slice* slice_alloc(void* addr, size_t type_size, size_t start_idx, size_t end_idx) {
	Slice* slice;

	/* Invalid arguments */
	if (addr == NULL) {
		return NULL;
	}

	if (type_size < 1) {
		return NULL;
	}

	if (end_idx < start_idx) {
		return NULL;
	}

	slice = (Slice*) malloc(sizeof(Slice));
	if (slice == NULL) {
		perror("Error allocating memory for slice");
		exit(EXIT_FAILURE);
	}

	slice->addr = (char*)addr + start_idx * type_size;
	slice->type_size = type_size;
	end_idx+=1;
	slice->len = end_idx - start_idx;

	return slice;
}

void slice_dealloc(Slice* slice) {
	if (slice == NULL) {
		return;
	}

	free(slice);
}

int slice_init(Slice* slice, void* addr, size_t type_size, size_t start_idx, size_t end_idx) {
	if (addr == NULL) {
		return -1;
	}

	if (type_size < 1) {
		return -1;
	}

	if (end_idx < start_idx) {
		return -1;
	}

	slice->addr = (char*)addr + start_idx * type_size;
	slice->type_size = type_size;
	end_idx+=1;
	slice->len = end_idx - start_idx;

	return 0;
}

void* slice_valueat(Slice* slice, size_t idx) {
	/* Handle if out of bounds */
	if (idx >= slice->len) {
		fprintf(stderr, "(WARN) slice_valueat: index %lu out of bounds for slice of length %lu\n",
				idx, slice->len);
		return (char*)slice->addr + (slice->len - 1) * slice->type_size;
	}

	return (char*)slice->addr + idx * slice->type_size;
}
