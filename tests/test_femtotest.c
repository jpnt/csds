#include "../include/csds_femtotest.h"

void test1() {
	ASSERT(1 == 1, "should not fail");

	ASSERT_EQUALS(1,1);

	/* ASSERT(1 == 2, "should fail!"); */

	/* ASSERT_STR_EQUALS("asd", "asd"); */
}


void test2() {
	ASSERT_FLOAT_EQUALS(10.0, 10.001);

	/* ASSERT_STR_EQUALS("asd", "ad"); */
}

int main()
{
	TEST_RUN(test1, "test1 of csds_femtotest");
	TEST_RUN(test2, "test2 of csds_femtotest");

	TEST_REPORT();
}
