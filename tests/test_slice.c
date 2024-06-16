#include "../include/csds/slice.h"
#include <assert.h>

int main() {
	int array[7] = {1,2,3,4,5,6,7};

	Slice* slice = slice_create(array, sizeof(int), 1, 5);
	int len = slice->len;
	assert(len == 5);
	
	// Get the values in the slice
	int first = *(int*)slice_valueat(slice, 0);
	assert(first == 2);

	for (int i = 1; i < len; i++) {
		int value = *(int*)slice_valueat(slice, i);
		assert(value == i+2);;
	}
}
