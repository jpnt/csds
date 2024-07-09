#include "../include/csds_vec.h"

/* Memory allocation configuration */
void* VEC_ALLOC(size_t size) {
	return malloc(size);
}
void VEC_DEALLOC(void* ptr) {
	free(ptr);
}
void* VEC_REALLOC(void* ptr, size_t new_size) {
	return realloc(ptr, new_size);
}

/* Concurrent programming support, leave NULL to disable */
void* mutex = NULL;
int (*mutex_lock)(void* mutex) = NULL;
int (*mutex_unlock)(void* mutex) = NULL;

int vec_alloc(void** arr, size_t item_size, size_t init_cap)
{
	struct csds_vec_header* vhead;

	if (arr == NULL) return CSDS_ERROR_VEC_ARR_NULL;

	if (init_cap <= 0) init_cap = CSDS_VEC_INITIAL_CAP;

	vhead = VEC_ALLOC(sizeof(struct csds_vec_header) + item_size * init_cap);
	if (vhead == NULL) return CSDS_ERROR_VEC_MALLOC_FAILED;

	vhead->len = 0;
	vhead->cap = init_cap;
	vhead->item_size = item_size;

	*arr = vhead+1;

	return 0;
}

int vec_dealloc(void* arr)
{
	struct csds_vec_header* vhead;

	if (arr == NULL) return CSDS_ERROR_VEC_ARR_NULL;

	vhead = VEC_HEADER_OF(arr);
	if (vhead == NULL) return CSDS_ERROR_VEC_HEADER_NULL;

	VEC_DEALLOC(vhead);

	return 0;
}

int vec_grow(void** arr)
{
	struct csds_vec_header* vhead;
	size_t new_size, new_cap;

	if (arr == NULL || *arr == NULL) return CSDS_ERROR_VEC_ARR_NULL;

	vhead = VEC_HEADER_OF(*arr);
	if (vhead == NULL) return CSDS_ERROR_VEC_HEADER_NULL;

	new_cap = vhead->cap * CSDS_VEC_GROWTH_FACTOR + 1;
	new_size = (sizeof(struct csds_vec_header) + new_cap * vhead->item_size);

	vhead = VEC_REALLOC(vhead, new_size);
	vhead->cap = new_cap;

	if (vhead == NULL) return CSDS_ERROR_VEC_REALLOC_FAILED;

	*arr = (void*)(vhead+1);

	return 0;
}

int vec_insert(void* arr, size_t item_idx, const void* item)
{
	struct csds_vec_header* vhead;

	/* Cannot automatically allocate when I do not use macros */
	if (arr == NULL) return CSDS_ERROR_VEC_ARR_NULL;

	vhead = VEC_HEADER_OF(arr);
	if (vhead == NULL) return CSDS_ERROR_VEC_HEADER_NULL;

	while (vhead->cap <= item_idx) {
		if (vec_grow(&arr) != 0) return CSDS_ERROR_VEC_REALLOC_FAILED;
		if (arr == NULL) return CSDS_ERROR_VEC_ARR_NULL;
		vhead = VEC_HEADER_OF(arr);
	}

	memcpy((char*)arr + item_idx * vhead->item_size, item, vhead->item_size);

	if (vhead->len <= item_idx) {
		vhead->len = item_idx + 1;
	}

	return 0;
}

int vec_remove(void* arr, size_t item_idx, void* removed)
{
	struct csds_vec_header* vhead;
	int value_after = 0xDEADBEEF;
	size_t i, cap, limit;

	if (arr == NULL) return CSDS_ERROR_VEC_ARR_NULL;

	vhead = VEC_HEADER_OF(arr);
	if (vhead == NULL) return CSDS_ERROR_VEC_HEADER_NULL;
	if (vhead->cap <= item_idx) return CSDS_ERROR_VEC_OUT_OF_BOUNDS;
	if (vhead->len <= 0) return CSDS_ERROR_VEC_EMPTY;

	if (removed != NULL) {
		memcpy(removed, (char*)arr + item_idx * vhead->item_size, vhead->item_size);
	}

	memcpy((char*)arr + item_idx * vhead->item_size, &value_after, vhead->item_size);

	/* Move items left after remove */
	cap = vhead->cap;
	limit = cap - 1;
	for (i=item_idx; i<limit; i+=2) {
		memcpy((char*)arr + i * vhead->item_size,
			(char*)arr + (i+1) * vhead->item_size, vhead->item_size);

		memcpy((char*)arr + (i+1) * vhead->item_size,
			(char*)arr + (i+2) * vhead->item_size, vhead->item_size);
	}

	vhead->len--;

	return 0;
}

int vec_push(void* arr, const void* item)
{
	struct csds_vec_header* vhead;

	if (arr == NULL) return CSDS_ERROR_VEC_ARR_NULL;

	vhead = VEC_HEADER_OF(arr);
	if (vhead == NULL) return CSDS_ERROR_VEC_HEADER_NULL;

	return vec_insert(arr, vhead->len, item);
}

int vec_pop(void* arr, void* popped)
{
	struct csds_vec_header* vhead;

	if (arr == NULL) return CSDS_ERROR_VEC_ARR_NULL;

	vhead = VEC_HEADER_OF(arr);
	if (vhead == NULL || vhead->len == 0) return CSDS_ERROR_VEC_HEADER_NULL;

	return vec_remove(arr, vhead->len-1, popped);
}
