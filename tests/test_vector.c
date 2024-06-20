#include "../include/csds/vector.h"
#include <assert.h>
#include <stdio.h>

int main() {

	Vec* vec = vec_create(10);
	assert(vec->capacity == 10);

	/* Use as a stack */

	vec_push(vec, (__V_ITEM_TYPE)0x1);
	vec_push(vec, (__V_ITEM_TYPE)0x2);
	vec_push(vec, (__V_ITEM_TYPE)0x3);
	vec_push(vec, (__V_ITEM_TYPE)0x4);
	assert(vec->len == 4);

	assert(vec->items[0] == (__V_ITEM_TYPE)0x1);
	assert(vec->items[1] == (__V_ITEM_TYPE)0x2);
	assert(vec->items[2] == (__V_ITEM_TYPE)0x3);
	assert(vec->items[3] == (__V_ITEM_TYPE)0x4);

	assert(vec_pop(vec) == (__V_ITEM_TYPE)0x4);
	assert(vec_pop(vec) == (__V_ITEM_TYPE)0x3);
	assert(vec_pop(vec) == (__V_ITEM_TYPE)0x2);
	assert(vec_pop(vec) == (__V_ITEM_TYPE)0x1);

	assert(vec->len == 0);


	/* Use as a queue */

	vec_push(vec, (__V_ITEM_TYPE)0x2);
	vec_push(vec, (__V_ITEM_TYPE)0x4);
	vec_push(vec, (__V_ITEM_TYPE)0x8);
	
	assert(vec_remove(vec, 0) == (__V_ITEM_TYPE)0x2);
	assert(vec_remove(vec, 0) == (__V_ITEM_TYPE)0x4);
	assert(vec_remove(vec, 0) == (__V_ITEM_TYPE)0x8);


	/* Item insertion */
	vec_insert(vec, 4, (__V_ITEM_TYPE)0x9);
	assert(vec->items[4] == (__V_ITEM_TYPE)0x9);


	/* Dynamic grow */
	vec_insert(vec, 10, (__V_ITEM_TYPE)0xA);
	assert(vec->capacity > 10); /* new capacity depends on growth factor */
	/* printf("vec->capacity = %zu\n",vec->capacity); */


	/* Free memory */
	vec_destroy(vec);

	return 0;
}
