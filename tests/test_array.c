/* #define CSDS_ARRAY_IMPL */
/* #include "../csds_array.h" */
#include "../csds_femtotest.h"
#include "../csds_array.h"
#include <stdlib.h>

/* quick and dirty testing before actual implementation */
void test1() {
	/*
	 * GOAL:
	 *
	 * int* arr = NULL;
	 * array_push(arr, 10);
	 * assay_ins(arr, 1, 20);
	 * assert(array_pop(arr) == 20);
	 * assert(arr[0] == 10);
	 * ...
	 */


	int INITIAL_CAPACITY=4;
	int i;  /*, cap = 4, len = 0;*/
	/* size_t cap, len; */
	/* int elem_size = sizeof(int); */
	int* arr = NULL;
	ArrayHeader* ah;
	
	printf("===============================\n");
	printf("DEBUG INFO:\n");
	printf("-------------------------------\n");
	printf("sizeof(ArrayHeader)=%lu\n",sizeof(ArrayHeader));
	printf("-------------------------------\n");
	printf("first problem: get size of the elements of the array\n");
	/* attempt 1: this just gives us the poiter (8B for 64bits) / by sizeof(int) 4 = 2 */
	printf("sizeof(arr)/sizeof(arr[0])=%lu\n", sizeof(arr)/sizeof(arr[0]));
	/* attempt 2: get the sizeof the first element */
	printf("sizeof(arr[0])=%lu\n", sizeof(arr[0]));
	printf("===============================\n");


	/* |_cap_|_len_|_elem1_|_elem2_|_elemN_| */
	ah = (ArrayHeader*) malloc(sizeof(ArrayHeader) + INITIAL_CAPACITY * sizeof(arr[0])); /* len + cap */
	if(!ah) {
		perror("Error");
		exit(1);
	}
	ah->cap = INITIAL_CAPACITY;
	ah->len = 0;

	/* arr = malloc(cap * sizeof(elem_size)); */

	/* assembly style */
	/* arr = (int*)((char*)ah+sizeof(ArrayHeader)); */

	/* C style: think: pointer is address + type */
	/* problem: how to we create a generic function that casts to (T*) */
	arr = (int*)(ah+1);


	/* access cap and len though the array */
	ArrayHeader* ah_from_arr = CSDS_ARRAYHEADER_OF(arr);
	
	/* fill up array */
	for (i=0; i<ah_from_arr->cap; ++i) {
		arr[i] = i+1;
		ah_from_arr->len++;
	}

	/* print values */
	for (i=0;i<ah_from_arr->len;++i){
		ASSERT_EQUALS(i+1,arr[i]);
		printf("%d\n",arr[i]);
	}

	ASSERT_EQUALS(ah_from_arr->len, 4);

	array_dealloc(arr);
}


void test2() {
	int* arr = NULL;
	array_alloc(arr, 0);

	ASSERT(arr != NULL, "arr should not be NULL at this point");

}

int main(void) {
	/* TEST_RUN(test1, "test1"); */
	TEST_RUN(test2, "test2");

	TEST_REPORT();
}
