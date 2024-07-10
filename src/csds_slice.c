#include "../include/csds_slice.h"

/* Memory allocation configuration */
void* CSDS_SLICE_ALLOC(size_t size) {
	return malloc(size);
}

void CSDS_SLICE_DEALLOC(void* ptr) {
	free(ptr);
}

struct csds_slice* slice_alloc(void* addr, size_t type_size, size_t start_idx, size_t end_idx) {
	struct csds_slice* slice;

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

        slice = (struct csds_slice*) CSDS_SLICE_ALLOC(sizeof(struct csds_slice));
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

void slice_dealloc(struct csds_slice* slice) {
	if (slice == NULL) {
		return;
	}

        CSDS_SLICE_DEALLOC(slice);
}

int slice_init(struct csds_slice* slice, void* addr, size_t type_size, size_t start_idx, size_t end_idx) {
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

void* slice_valueat(struct csds_slice* slice, size_t idx) {
	/* Handle if out of bounds */
	if (idx >= slice->len) {
		fprintf(stderr, "(WARN) slice_valueat: index %lu out of bounds for slice of length %lu\n",
				idx, slice->len);
		return (char*)slice->addr + (slice->len - 1) * slice->type_size;
	}

	return (char*)slice->addr + idx * slice->type_size;
}
