/**
 * @file	csds_femtotest.h
 * @brief	Small-as-possible, no-hassle, single-header ANSI C unit-testing "framework"
 * 		Based on 'tinytest.h´ by Joe Walnes and 'minctest.h´ by Lewis Van Winkle
 */
#ifndef CSDS_FEMTOTEST_H
#define CSDS_FEMTOTEST_H

#include <stdio.h>
#include <stddef.h>
#include <string.h>
#include <math.h>
#include <time.h>

/* Float comparison tolerance */
#ifndef FT_FLOAT_TOLERANCE
#define FT_FLOAT_TOLERANCE	0.001
#endif /* !FT_FLOAT_TOLERANCE */

/* Color variable macros */
#define FT_COLOR_CODE	0x1B
#define FT_COLOR_RED	"[1;31m"
#define FT_COLOR_GREEN	"[1;32m"
#define FT_COLOR_RESET	"[0m"

/* Track number of tests and fails */
static int ft_tests = 0;
static int ft_fails = 0;
static long ft_ticks = 0;

/* Base assert macro */
#define ASSERT(expr, msg) do {\
	ft_tests++;\
	if(!(expr)) {\
		ft_fails++;\
		printf("Assert failed: %s (%s:%d) \n", msg, __FILE__, __LINE__);\
	}\
} while(0)

#define ASSERT_EQUALS(expected, actual)	ASSERT((expected) == (actual), (#actual))

#define ASSERT_STR_EQUALS(expected, actual) ASSERT(strcmp((expected),(actual))==0, (#actual))

#define ASSERT_FLOAT_EQUALS(expected, actual) ASSERT(fabs((double)(expected)-(double)(actual)) <= FT_FLOAT_TOLERANCE, (#actual))

#define TEST_RUN(test_fn, test_name) do{\
	int ft_tests_before = ft_tests;\
	int ft_fails_before = ft_fails;\
	clock_t end, start = clock();\
	test_fn();\
	end = clock()-start;\
	ft_ticks+=end;\
	printf("%s -- %d passed; %d failed; %ld ticks\n",\
			test_name, ft_tests-ft_tests_before-ft_fails+ft_fails_before,\
			ft_fails-ft_fails_before, end);\
} while(0)

#define TEST_REPORT() do{\
	printf("REPORT: %s: %d passed; %d failed; %ld ticks -- ",\
			__FILE__, ft_tests-ft_fails, ft_fails, ft_ticks);\
	if (ft_fails != 0) {\
		printf("%c%sFAILED!%c%s\n\n",\
			FT_COLOR_CODE, FT_COLOR_RED, FT_COLOR_CODE, FT_COLOR_RESET);\
		return 1;\
	} else {\
		printf("%c%sPASSED!%c%s\n\n",\
			FT_COLOR_CODE, FT_COLOR_GREEN, FT_COLOR_CODE, FT_COLOR_RESET);\
		return 0;\
	}\
} while(0)

#endif /* !CSDS_FEMTOTEST_H */
