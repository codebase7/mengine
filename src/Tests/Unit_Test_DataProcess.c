/*!
    Multiverse Engine Project 09/9/2015 Unit Tests Unit_Test_DataProcess.c

    Copyright (C) 2015 Multiverse Engine Project

    This program is free software;
    you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation;
    either version 2 of the License, or (at your option) any later version.

    This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY;
    without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
    See the GNU General Public License for more details.

    You should have received a copy of the GNU General Public License along with this program;
    if not, write to the Free Software Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA

    Official source repository and project information can be found at
    https://github.com/codebase7/mengine
*/

/* Internal includes. */
#include "Unit_Tests.h"

/*!
 *		Unit_Tests_DataProcess_TRNG()
 *
 *		Tests the DataProcess_Trivial_Random_Number_Generator() function.
 *		Function should return at least one different value in both runs for the test to be considered successful.
 *		
 *		Note: The number of values per run can be controlled by the TEST_ARRAY_SIZE #define within the function.
 *
 *		Note: The range of permissible values returned by the function can be controlled by the TEST_MIN_VAL and
 *		TEST_MAX_VAL #define(s) within the function, however the test code expects a result of zero (0) to be an error,
 *		so the range defined by TEST_MIN_VAL and TEST_MAX_VAL should NOT include zero (0) for it to work correctly.
 *		(The original range is 1 - 10000.)
 *
 *		Note: The number of test runs performed by the function can be controlled by the TEST_NUM_OF_RUNS #define
 *		within the function, however the test code expects that at least two (2) runs will be made, so TEST_NUM_OF_RUNS
 *		must be greater than two (2) for the function to work correctly.
 *
 *		Returns 0 if the test passes.
 *		Returns -1 if the initial function call does not return a valid value.
 *		Returns -2 if the TRNG function's seed could not be reset.
 *		Returns -3 if the output from the TRNG function for both runs was identical.
 *		Returns -9 if an unknown error occurs.
 *		Returns -10 if memory allocation fails.
 */
int Unit_Tests_DataProcess_TRNG()
{
#define TEST_ARRAY_SIZE 10	/* Size of the test arrays, (also defines the number of calls per test run of the tested function.) */
#define TEST_MIN_VAL 1		/* Minimal value that the test function may return. (Do NOT set this to zero the test code below will fail to work correctly if you do.) */
#define TEST_MAX_VAL 10000	/* Maximum value that the test function may return. (This value should be bigger than TEST_MIN_VAL.) */
#define TEST_NUM_OF_RUNS 10	/* Number of test runs to make. */

	/* Init vars. */
	int ret = -9;										/* Result of this test. */
	size_t retFromTRNG = 0;								/* The result of the call to the TRNG. */
	size_t x = 0;										/* Counter used in the outer for loops. */
	size_t y = 0;										/* Counter used in the inner for loops. */
	size_t ** testArrays[TEST_NUM_OF_RUNS] = { NULL };	/* Holds the pointer to the test result arrays. */
	const char * ERR_MSG_INVALID_VAL = "TEST FAILURE: Unit_Tests_DataProcess_TRNG(): Call to DataProcess_Trivial_Random_Number_Generator() returned an invalid value.\n";
	const char * ERR_MSG_INVALID_VAL_RESET = "TEST FAILURE: Unit_Tests_DataProcess_TRNG(): Unable to reset TRNG, call to DataProcess_Trivial_Random_Number_Generator() returned an invalid value.\n";
	const char * STAT_MSG_RESET_TRNG = "TEST INFO: Unit_Tests_DataProcess_TRNG(): Resetting TRNG.\n";
	const char * STAT_MSG_BEGIN_RUN = "TEST INFO: Unit_Tests_DataProcess_TRNG(): Begining test run, please wait.\n";
	const char * STAT_MSG_CHECK_RETVALS = "TEST INFO: Unit_Tests_DataProcess_TRNG(): Checking results of the test runs to see if they do not match. Please wait.\n";
	const char * STAT_MSG_INITIAL_CALL = "TEST INFO: Unit_Tests_DataProcess_TRNG(): Makeing initial test call to DataProcess_Trivial_Random_Number_Generator(). Please Wait.\n";
	const char * STAT_MSG_TEST_PASS = "TEST INFO: Unit_Tests_DataProcess_TRNG(): TEST PASSED.\n";
	const char * STAT_MSG_TEST_FAIL = "TEST INFO: Unit_Tests_DataProcess_TRNG(): TEST FAILED, generated numbers were identical despite TRNG reset.\n";
	const char * ERR_MSG_MEM_ALLOC_FAIL = "TEST FAILURE: Unit_Tests_DataProcess_TRNG(): Unable to allocate memory for test.\n";
	const char * ERR_MSG_INVALID_PTR_TO_ARRAYS = "TEST FAILURE: Unit_Tests_DataProcess_TRNG(): Invalid pointer to result arrays.\n";
	const char * ERR_MSG_INVALID_ARRAY = "TEST FAILURE: Unit_Tests_DataProcess_TRNG(): Invalid result array pointer.\n";

	/* Start test section. */
	printf("%s", START_TEST_SECTION);

	/* Run call. */
	printf("%s", STAT_MSG_INITIAL_CALL);
	retFromTRNG = DataProcess_Trivial_Random_Number_Generator(TEST_MIN_VAL, TEST_MAX_VAL, false);
	if ((retFromTRNG >= TEST_MIN_VAL) && (retFromTRNG <= TEST_MAX_VAL))
	{
		/* Begin test run memory allocation outer loop. */
		printf("%s", STAT_MSG_BEGIN_RUN);
		for (x = 0; ((x < TEST_NUM_OF_RUNS) && (ret == -9)); x++)
		{
			/* Allocate memory for test array pointer. */
			testArrays[x] = (size_t **)malloc(((sizeof(size_t *)) * TEST_ARRAY_SIZE));
			if (testArrays[x] != NULL)
			{
				/* Set the pointers to NULL, and allocate them. */
				memset(testArrays[x], 0, ((sizeof(size_t *)) * TEST_ARRAY_SIZE));

				/* Allocate the test array values. */
				for (y = 0; ((y < TEST_ARRAY_SIZE) && (ret == -9)); y++)
				{
					(testArrays[x])[y] = (size_t *)malloc(sizeof(size_t));
					if ((testArrays[x])[y] != NULL)
					{
						/* Set the allocated value to zero. (0). */
						*((testArrays[x])[y]) = 0;
					}
					else
					{
						/* Memory allocation error. */
						ret = -10;
						printf("%s", ERR_MSG_MEM_ALLOC_FAIL);
					}
				}
			}

			/* Check for mem alloc success. */
			if (ret == -9)
			{
				/* Reset the TRNG. */
				printf("%s", STAT_MSG_RESET_TRNG);
				retFromTRNG = DataProcess_Trivial_Random_Number_Generator(TEST_MIN_VAL, TEST_MAX_VAL, true);
				if ((retFromTRNG >= TEST_MIN_VAL) && (retFromTRNG <= TEST_MAX_VAL))
				{
					/* Begin test run inner loop. */
					for (y = 0; ((y < TEST_ARRAY_SIZE) && ((retFromTRNG >= TEST_MIN_VAL) && (retFromTRNG <= TEST_MAX_VAL))); y++)
					{
						retFromTRNG = DataProcess_Trivial_Random_Number_Generator(TEST_MIN_VAL, TEST_MAX_VAL, false);
						if ((retFromTRNG >= TEST_MIN_VAL) && (retFromTRNG <= TEST_MAX_VAL))
						{
							/* Copy the value to the array. */
							(*((testArrays[x])[y])) = retFromTRNG;
						}
						else
						{
							/* Test failure, invalid value. */
							ret = -1;
							printf("%s", ERR_MSG_INVALID_VAL);
						}
					}
				}
				else
				{
					/* Could not reset the TRNG. */
					ret = -2;
					printf("%s", ERR_MSG_INVALID_VAL_RESET);
				}
			}
		}	/* End of test run outer loop. */

		/* Check for valid data. */
		if ((ret == -9) && (testArrays != NULL))
		{
			/* Begin test result loop. */
			for (x = 0; (x < TEST_NUM_OF_RUNS); x++)
			{
				/* Check for NULL. */
				if (testArrays[x] == NULL)
				{
					/* Invalid test result arrays. */
					ret = -10;
					printf("%s", ERR_MSG_INVALID_ARRAY);
				}
			}

			/* Check for success. */
			if (ret == -9)
			{
				/* Set failure code to bad RNG source. */
				ret = -3;

				/* A note about the verify loop structure:
				 *
				 *	The outer loop runs through each value in the result array,
				 *	and the inner loop loops through each result array.
				 *
				 *	The reason why is that we are looking for a value to be different
				 *	at some point in each array. I.e. We care about the order in which the
				 *	values appear, not the values themselves. As long as at least one pair of
				 *	values at the exact same position in the arrays do not match each other,
				 *	the test is considered successful.
				 */
				/* Begin outer verify loop. (Loops through each value.) */
				for (y = 0; ((y < TEST_ARRAY_SIZE) && (ret == -3)); y++)
				{
					/* Begin inner verify loop. (Loops through each result array.) */
					for (x = 0; ((x < (TEST_NUM_OF_RUNS - 1)) && (ret == -3)); x++)
					{
						/* Check the results of each run to see if they match exactly, (they should not.)  */
						if ((*((testArrays[x])[y])) != (*((testArrays[(x + 1)])[y])))
						{
							/* Set ret to success. */
							ret = 0;
						}
					}
				}

				/* Print out the arrays for verification. */
				printf("%s", "Random value table:\n|Run Number:|Random values:|\n");
				for (x = 0; (x < TEST_NUM_OF_RUNS); x++)
				{
					printf("|%u|", x);
					for (y = 0; (y < TEST_ARRAY_SIZE); y++)
					{
						printf("%u ", (*((testArrays[x])[y])));
					}
					printf("%s", "|\n");
				}

				/* Check for failure. */
				if (ret == 0)
				{
					printf("%s", STAT_MSG_TEST_PASS);
				}
				else
				{
					printf("%s", STAT_MSG_TEST_FAIL);
				}
			}
		}
		else
		{
			/* Invalid test result arrays. */
			ret = -10;
			printf("%s", ERR_MSG_INVALID_PTR_TO_ARRAYS);
		}
	}
	else
	{
		/* Test failure. */
		ret = -1;
		printf("%s", ERR_MSG_INVALID_VAL);
	}

	/* Deallocate memory. */
	for (x = 0; (x < TEST_NUM_OF_RUNS); x++)
	{
		/* Check for NULL. */
		if (testArrays[x] != NULL)
		{
			/* Deallocate the test array values. */
			for (y = 0; ((y < TEST_ARRAY_SIZE) && (ret == -9)); y++)
			{
				if ((testArrays[x])[y] != NULL)
				{
					free((testArrays[x])[y]);
					(testArrays[x])[y] = NULL;
				}
			}

			/* Deallocate the pointer to the array. */
			free(testArrays[x]);
			testArrays[x] = NULL;
		}
	}

	/* End test section. */
	printf("%s", END_TEST_SECTION);

	/* Return ret. */
	return ret;

/* Run sanity checks on defines here, and abort build if they fail. */
#if TEST_NUM_OF_RUNS < 2
#error __FILE__ "Unit_Tests_DataProcess_TRNG(): TEST_NUM_OF_RUNS must be greater than one (1)."
#endif
#if TEST_MIN_VAL <= 0
#error __FILE__ "Unit_Tests_DataProcess_TRNG(): TEST_MIN_VAL cannot be less than or equal to zero (0)."
#endif
#if (TEST_MAX_VAL <= TEST_MIN_VAL)
#error __FILE__ "Unit_Tests_DataProcess_TRNG(): TEST_MAX_VAL must be greater than TEST_MIN_VAL."
#endif

#undef TEST_NUM_OF_RUNS
#undef TEST_MAX_VAL
#undef TEST_MIN_VAL
#undef TEST_ARRAY_SIZE
}

int Unit_Tests_DataProcess_Main()
{
	/* Init vars. */
	int ret = 0;				/* Result of the tests. */
	int retFromTRNGTest = 0;	/* Result of the TRNG test. */

	/* Begin tests for DataProcess_Trivial_Random_Number_Generator(). */
	retFromTRNGTest = Unit_Tests_DataProcess_TRNG();


	/* Return ret. */
	return ret;
}
