/* #define CSDS_ARRAY_IMPL */
/* #include "../csds_array.h" */
#include "../csds_femtotest.h"
#include "../csds_array.h"
#include <stdlib.h>

/* quick and dirty testing before actual implementation */
void test1() {
	int INITIAL_CAPACITY=4;
	int i;  /*, cap = 4, len = 0;*/
	int elem_size = sizeof(int); /* first problem: get the size of the elements in a generic way */
	int* arr = NULL;
	ArrayHeader* ah;

	/* |_cap_|_len_|_elem1_|_elem2_|_elemN_| */
	ah = (ArrayHeader*) malloc(sizeof(ArrayHeader) + INITIAL_CAPACITY * sizeof(elem_size)); /* len + cap */
	ah->cap = INITIAL_CAPACITY;
	ah->len = 0;

	/* arr = malloc(cap * sizeof(elem_size)); */
	arr = (int*)ah+sizeof(ArrayHeader);


	/* access cap and len though the array */
	
	/* fill up array */
	for (i=0; i<ah->cap; ++i) {
		arr[i] = i+1;
		ah->len++;
	}

	/* print values */
	for (i=0;i<cap;++i){
		ASSERT_EQUALS(i+1,arr[i]);
		printf("%d\n",arr[i]);
	}

	ASSERT_EQUALS(len, 4);

}

int main(void) {
	TEST_RUN(test1, "test1");

	TEST_REPORT();
}
