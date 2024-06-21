#include "../include/csds/slice.h"
#include <assert.h>
#include <stdio.h>

int main() {
	Slice* slice;
	Slice stack_slice;
	int array[7] = {1,2,3,4,5,6,7};
	int i, len, first_value;

	/* Slice in the heap */

	slice = slice_alloc(array, sizeof(int), 1, 5);
	if (slice == NULL) {
		perror("slice_create");
		return 1;
	}

	len = slice->len;
	assert(len == 5);
	
	/* Get the values in the slice */
	first_value = *(int*)slice_valueat(slice, 0);
	assert(first_value == 2);

	for (i=0; i < len; i++) {
		int value = *(int*)slice_valueat(slice, i);
		/*  2, 3, 4, 5, 6 */
		/* printf("%d\n", value); */
		assert(value == i+2);
	}

	slice_dealloc(slice);



	/* Slice in the stack */
	
	if (slice_init(&stack_slice, array, sizeof(int), 3, 6) == -1) {
		perror("slice_create_using_stack");
		return 2;
	}

	len = stack_slice.len;
	assert(len == 4);

	first_value = *(int*)slice_valueat(&stack_slice, 0);
	assert(first_value == 4);

	for (i=0; i < len; i++) {
		int value = *(int*)slice_valueat(&stack_slice, i);
		/*  4, 5, 6, 7 */
		/* printf("%d\n", value); */
		assert(value == i+4);
	}

	return 0;
}
