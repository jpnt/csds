#include "../include/csds/slice.h"
#include <assert.h>

int main() {
	int array[7] = {1,2,3,4,5,6,7};

	// Slice in the heap

	Slice* slice = slice_create(array, sizeof(int), 1, 5);
	int len = slice->len;
	assert(len == 5);
	
	// Get the values in the slice
	int first = *(int*)slice_valueat(slice, 0);
	assert(first == 2);

	for (int i = 0; i < len; i++) {
		int value = *(int*)slice_valueat(slice, i);
		// 2, 3, 4, 5, 6
		//printf("%d\n", value);
		assert(value == i+2);;
	}

	slice_destroy(slice);



	// And a slice in the stack
	
	Slice stk_sl;
	slice_stack_create(&stk_sl, array, sizeof(int), 3, 6);
	len = stk_sl.len;
	assert(len == 4);

	first = *(int*)slice_valueat(&stk_sl, 0);
	assert(first == 4);

	for (int i = 0; i < len; i++) {
		int value = *(int*)slice_valueat(&stk_sl, i);
		// 4, 5, 6, 7
		//printf("%d\n", value);
		assert(value == i+4);
	}
}
