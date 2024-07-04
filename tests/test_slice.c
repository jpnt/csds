#include "../include/csds/slice.h"
#include "../csds_femtotest.h"
#include <stdlib.h>

/* Slice in the heap */
void test_slice_heap()
{
	Slice* slice;
	char str[] = "address + type + length";
	size_t len;
	/* String to store a copy of the slice we create */
	char str_slice[10];

	slice = slice_alloc(str, sizeof(char), 10, 13);

	len = slice->len;

	ASSERT_EQUALS(len, 13-10+1);

	strncpy(str_slice, slice->addr, slice->len);
	str_slice[slice->len] = '\0';

	ASSERT_STR_EQUALS(str_slice, "type");

	slice_dealloc(slice);
}

/* Slice in the stack */
void test_slice_stack()
{
	Slice slice;
	int arr[] = {1,2,3,4,5,6,7};
	/*                 ^   ^    */
	/*              start  end  */
	int value, oobs;

	if (slice_init(&slice, arr, sizeof(int), 3, 5) == -1) {
		perror("slice_create_using_stack");
		exit(1);
	}

	ASSERT_EQUALS(3, slice.len);

	value = *(int*)slice_valueat(&slice, 0);
	ASSERT_EQUALS(4, value);

	value = *(int*)slice_valueat(&slice, 1);
	ASSERT_EQUALS(5, value);

	value =*(int*)slice_valueat(&slice, 2);
	ASSERT_EQUALS(6, value);

	/* Try to access out of bounds index */
	oobs = *(int*)slice_valueat(&slice, 69);
	/* Default behavior is to return last element of the slice */
	ASSERT_EQUALS(oobs, 6);
}

int main()
{
	TEST_RUN(test_slice_heap, "test_slice_heap");
	TEST_RUN(test_slice_stack, "test_slice_stack");

	TEST_REPORT();
}
