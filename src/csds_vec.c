#include "../include/csds_vec.h"

/* Concurrent programming support, leave NULL to disable */
void* mutex = NULL;
int (*mutex_lock)(void* mutex) = NULL;
int (*mutex_unlock)(void* mutex) = NULL;

int vec_alloc(void** arr, size_t item_size, size_t init_cap)
{
	struct csds_vec_header* vhead;

	if (arr == NULL) return CSDS_ERROR_VEC_ARR_NULL;

	if (init_cap == 0) init_cap = CSDS_VEC_INITIAL_CAP;

	vhead = CSDS_VEC_ALLOC(sizeof(struct csds_vec_header) + item_size * init_cap);
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

	CSDS_VEC_DEALLOC(vhead);

	return 0;
}

int vec_grow(void** arr)
{
	struct csds_vec_header* vhead;
	size_t new_size, new_cap;
	void* new_vec;

	if (arr == NULL || *arr == NULL) return CSDS_ERROR_VEC_ARR_NULL;

	/* Lock */
	if (mutex_lock != NULL) mutex_lock(&mutex);

	vhead = VEC_HEADER_OF(*arr);
	if (vhead == NULL) {
		/* Unlock */
		if (mutex_unlock != NULL) mutex_unlock(&mutex);
		return CSDS_ERROR_VEC_HEADER_NULL;
	}

	new_cap = vhead->cap * CSDS_VEC_GROWTH_FACTOR + 1;
	new_size = (sizeof(struct csds_vec_header) + new_cap * vhead->item_size);

	/* Reallocate memory */
	new_vec = CSDS_VEC_REALLOC(vhead, new_size);
	if (new_vec == NULL) {
		/* Unlock */
		if (mutex_unlock != NULL) mutex_unlock(&mutex);
		return CSDS_ERROR_VEC_REALLOC_FAILED;
	}

	vhead = (struct csds_vec_header*)new_vec;
	vhead->cap = new_cap;
	*arr = (void*)(vhead + 1);

	/* Unlock */
	if (mutex_unlock != NULL) mutex_unlock(&mutex);

	return 0;
}

int vec_insert(void* arr, size_t item_idx, const void* item)
{
	struct csds_vec_header* vhead;

	/* Cannot automatically allocate when I do not use macros */
	if (arr == NULL) return CSDS_ERROR_VEC_ARR_NULL;

	/* Lock */
	if (mutex_lock != NULL) mutex_lock(&mutex);

	vhead = VEC_HEADER_OF(arr);
	if (vhead == NULL) {
		/* Unlock */
		if (mutex_unlock != NULL) mutex_unlock(&mutex);
		return CSDS_ERROR_VEC_HEADER_NULL;
	}

	while (vhead->cap <= item_idx) {
		if (vec_grow(&arr) != 0) {
			/* Unlock */
			if (mutex_unlock != NULL) mutex_unlock(&mutex);
			return CSDS_ERROR_VEC_REALLOC_FAILED;
		}

		if (arr == NULL) return CSDS_ERROR_VEC_ARR_NULL;
		vhead = VEC_HEADER_OF(arr);
	}

	memcpy((char*)arr + item_idx * vhead->item_size, item, vhead->item_size);

	if (vhead->len <= item_idx) {
		vhead->len = item_idx + 1;
	}

	/* Unlock */
	if (mutex_unlock != NULL) mutex_unlock(&mutex);

	return 0;
}

int vec_remove(void* arr, size_t item_idx, void* removed)
{
	struct csds_vec_header* vhead;
	/* int value_after = 0xDEADBEEF; */
	/* size_t i, len, item_size, limit; */
	size_t item_size, len;

	if (arr == NULL) return CSDS_ERROR_VEC_ARR_NULL;

	/* Lock */
	if (mutex_lock != NULL) mutex_lock(&mutex);

	vhead = VEC_HEADER_OF(arr);

	if (vhead == NULL) {
		/* Unlock */
		if (mutex_unlock != NULL) mutex_unlock(&mutex);
		return CSDS_ERROR_VEC_HEADER_NULL;
	}

	if (vhead->cap <= item_idx) {
		/* Unlock */
		if (mutex_unlock != NULL) mutex_unlock(&mutex);
		return CSDS_ERROR_VEC_OUT_OF_BOUNDS;
	}

	if (vhead->len == 0) {
		/* Unlock */
		if (mutex_unlock != NULL) mutex_unlock(&mutex);
		return CSDS_ERROR_VEC_EMPTY;
	}

	item_size = vhead->item_size;
	len = vhead->len;

	if (removed != NULL) {
		memcpy(removed, (char*)arr + item_idx * item_size, item_size);
	}

	/* Move items left after remove */
	if (item_idx < len - 1) {
		memmove((char*)arr + item_idx * item_size,
			(char*)arr + (item_idx + 1) * item_size,
			(len - item_idx - 1) * item_size);
	}

	vhead->len--;

	/* Unlock */
	if (mutex_unlock != NULL) mutex_unlock(&mutex);

	return 0;
}

int vec_push(void* arr, const void* item)
{
	const struct csds_vec_header* vhead;
	int result;

	if (arr == NULL) return CSDS_ERROR_VEC_ARR_NULL;
	
	/* Lock */
	if (mutex_lock != NULL) mutex_lock(&mutex);

	vhead = VEC_HEADER_OF(arr);
	if (vhead == NULL) {
		/* Unlock */
		if (mutex_unlock != NULL) mutex_unlock(&mutex);
		return CSDS_ERROR_VEC_HEADER_NULL;
	}

	result = vec_insert(arr, vhead->len, item);

	if (mutex_unlock != NULL) mutex_unlock(&mutex);
	
	return result;
}

int vec_pop(void* arr, void* popped)
{
	const struct csds_vec_header* vhead;
	int result;

	if (arr == NULL) return CSDS_ERROR_VEC_ARR_NULL;

	/* Lock */
	if (mutex_lock != NULL) mutex_lock(&mutex);

	vhead = VEC_HEADER_OF(arr);
	if (vhead == NULL) {
		/* Unlock */
		if (mutex_unlock != NULL) mutex_unlock(&mutex);
		return CSDS_ERROR_VEC_HEADER_NULL;
	}
	if (vhead->len == 0) {
		/* Unlock */
		if (mutex_unlock != NULL) mutex_unlock(&mutex);
		return CSDS_ERROR_VEC_EMPTY;
	}

	result = vec_remove(arr, vhead->len-1, popped);

	/* Unlock */
	if (mutex_unlock != NULL) mutex_unlock(&mutex);

	return result;
}
