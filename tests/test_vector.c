#include "../include/csds/vector.h"
#include <assert.h>

int main() {

	Vec* vec = vec_create(10);
	assert(vec->capacity == 10);

	// Use as a stack

	vec_push(vec, (void*)0x1);
	vec_push(vec, (void*)0x2);
	vec_push(vec, (void*)0x3);
	vec_push(vec, (void*)0x4);
	assert(vec->len == 4);

	assert(vec->items[0] == (void*)0x1);
	assert(vec->items[1] == (void*)0x2);
	assert(vec->items[2] == (void*)0x3);
	assert(vec->items[3] == (void*)0x4);

	assert(vec_pop(vec) == (void*)0x4);
	assert(vec_pop(vec) == (void*)0x3);
	assert(vec_pop(vec) == (void*)0x2);
	assert(vec_pop(vec) == (void*)0x1);

	assert(vec->len == 0);


	// Use as a queue

	vec_push(vec, (void*)0x2);
	vec_push(vec, (void*)0x4);
	vec_push(vec, (void*)0x8);
	
	assert(vec_remove(vec, 0) == (void*)0x2);
	assert(vec_remove(vec, 0) == (void*)0x4);
	assert(vec_remove(vec, 0) == (void*)0x8);


	// Item insertion
	vec_insert(vec, 4, (void*)0x9);
	assert(vec->items[4] == (void*)0x9);


	// Dynamic grow
	vec_insert(vec, 10, (void*)0xA);
	assert(vec->capacity == 20);


	// Free memory
	vec_destroy(vec);

	return 0;
}
