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

/* Define TRNGUseMayFailMSG. */
const static char * TRNGUseMayFailMSG = "The remainder of these tests rely on the DataProcess_Trivial_Random_Number_Generator() function to work correctly and may fail or give false results if that function does not work correctly. Therefore the results for the remainder of the test should only be considered valid if the TRNG function works correctly.\n\n";

/* Define some common error messages. */
const static char * periodAndNewlineMSG = ".\n";
const static char * errorCodeReturnedMSG = "The function returned error code: ";
const static char * errorSuccessNoResultMSG = "The function returned success without producing a result.\n";
const static char * errorSamePtrMSG = "The function returned success, but the returned memory pointer is identical to the original one. (No actual allocation occured.)\n";
const static char * InvalidArgStringPointerTestMSG = "Attempting to get COMMON_ERROR_INVALID_ARGUMENT error code by passing a NULL string pointer to ";
const static char * InvalidArgStringPointerFailMSG = "Unable to get COMMON_ERROR_INVALID_ARGUMENT error code by passing a NULL string pointer to ";
const static char * InvalidArgLengthPointerTestMSG = "Attempting to get COMMON_ERROR_INVALID_ARGUMENT error code by passing a NULL length pointer to ";
const static char * InvalidArgLengthPointerFailMSG = "Unable to get COMMON_ERROR_INVALID_ARGUMENT error code by passing a NULL length pointer to ";

/*!
 *		int Unit_Tests_DataProcess_Random_String_Generator(char ** string, size_t * stringLength)
 *
 *		Generates a c-string using printable ASCII characters for use by other testing functions.
 *		The generated string should be deallocated by DataProcess_Deallocate_CString() when it is
 *		no longer needed.
 *
 *		Returns 0 if successful.
 *		Returns -1 if an argument pointer is NULL.
 *		Returns -2 if a random number could not be generated.
 *		Returns -3 if memory allocation fails.
 *
 *		This function will not modifiy the given arguments if it's return code is not zero (0).
 */
int Unit_Tests_DataProcess_Random_String_Generator(char ** string, size_t * stringLength)
{
	/* Define the error messaging macros. */
#define TEST_FAILURE_MSG_HEAD "TEST_FAILURE: Unit_Tests_DataProcess_Allocator_and_Deallocator(): "
#define TEST_ERROR_LOG_REAL(ERR_MSG) printf("%s", TEST_FAILURE_MSG_HEAD); printf("%s", ERR_MSG);
#define TEST_ERROR_LOG(ERR_MSG) TEST_ERROR_LOG_REAL(ERR_MSG)

	/* Define the range of ASCII values to use for the random string. */
#define TEST_PRINTABLE_ASCII_START 33
#define TEST_PRINTABLE_ASCII_END 126

	/* Define the range used to select the length of the randomly generated string. */
#define TEST_RANDOM_STRING_LENGTH_MINIMAL 3
#define TEST_RANDOM_STRING_LENGTH_MAXIMUM 100

	/* Init vars. */
	int ret = -999;										/* Result of the tests. */
	int retFromCall = COMMON_ERROR_UNKNOWN_ERROR;		/* Result code from engine function. */
	size_t x = 0;										/* Counter used in random string generation loop. */
	size_t randVal = 0;									/* Result from the call to TRNG() function. */
	size_t randomLength = 0;							/* Chosen length of the string to be generated. */
	char * randString = NULL;							/* Temporary pointer used to create the random string. */

	/* Check for invalid arguments. */
	if ((string != NULL) && (stringLength != NULL))
	{
		/* Randomly generate a length for the string. */
		randomLength = DataProcess_Trivial_Random_Number_Generator(TEST_RANDOM_STRING_LENGTH_MINIMAL, TEST_RANDOM_STRING_LENGTH_MAXIMUM, true);
		if (randomLength > 0)
		{
			/* Allocate memory for the TRNG String. */
			retFromCall = DataProcess_Reallocate_C_String(&randString, 0, randomLength);
			if ((retFromCall == COMMON_ERROR_SUCCESS) && (randString != NULL))
			{
				/* Use the TRNG to generate the source string. (Note the last character in the string should be a NULL byte.
					  Which it is if the string was allocated by DataProcess_Reallocate_C_String().)
				 */
				for (x = 0; (x < (randomLength - 1)); x++)
				{
					randVal = DataProcess_Trivial_Random_Number_Generator(TEST_PRINTABLE_ASCII_START, TEST_PRINTABLE_ASCII_END, false);
					randString[x] = (int)randVal;
				}

				/* Copy the string pointer, and length value. */
				(*string) = randString;
				(*stringLength) = (randomLength - 1);	/* Omit NULL termination byte from string length. */

				/* Done. */
				ret = 0;
			}
			else
			{
				/* Could not allocate memory? */
				ret = -3;
				TEST_ERROR_LOG("Unable to allocate memory for random string.\n");
				((retFromCall != COMMON_ERROR_SUCCESS) ? (printf("%s%i%s", errorCodeReturnedMSG, retFromCall, ".\n")) :
				(printf("%s", errorSuccessNoResultMSG)));
			}
		}
		else
		{
			/* Could not generate a random number. */
			ret = -2;
			TEST_ERROR_LOG("Could not generate a random number.\n");
		}
	}
	else
	{
		/* Invalid arguments. */
		ret = -1;
		TEST_ERROR_LOG("Invalid argument.\n");
	}

	/* Exit function. */
	return ret;

	/* Check for valid random string length. */
#if TEST_RANDOM_STRING_LENGTH_MINIMAL < 3
#error "Unit_Tests_DataProcess_Allocator_and_Deallocator(): TEST_RANDOM_STRING_LENGTH must be greater than two (2)."
#endif	/* TEST_RANDOM_STRING_LENGTH < 3 */

	/* Check for valid ASCII ranges. */
#if TEST_PRINTABLE_ASCII_START >= TEST_PRINTABLE_ASCII_END
#error "Unit_Tests_DataProcess_Allocator_and_Deallocator(): TEST_PRINTABLE_ASCII_START must be less than TEST_PRINTABLE_ASCII_END."
#endif	/* TEST_PRINTABLE_ASCII_START >= TEST_PRINTABLE_ASCII_END */
#if TEST_PRINTABLE_ASCII_START < 1
#error "Unit_Tests_DataProcess_Allocator_and_Deallocator(): TEST_PRINTABLE_ASCII_START must be a greater than or equal to one (1)."
#endif	/* TEST_PRINTABLE_ASCII_START < 1 */
#if TEST_PRINTABLE_ASCII_END < 2
#error "Unit_Tests_DataProcess_Allocator_and_Deallocator(): TEST_PRINTABLE_ASCII_END must be a greater than or equal to two (2)."
#endif /* TEST_PRINTABLE_ASCII_END < 2 */

	/* Undefine the macros. */
#undef TEST_RANDOM_STRING_LENGTH_MAXIMUM
#undef TEST_RANDOM_STRING_LENGTH_MINIMAL
#undef TEST_PRINTABLE_ASCII_END
#undef TEST_PRINTABLE_ASCII_START
#undef TEST_ERROR_LOG
#undef TEST_ERROR_LOG_REAL
#undef TEST_FAILURE_MSG_HEAD
}

/*!
 *		int Unit_Tests_DataProcess_Allocator_and_Deallocator()
 *
 *		This function tests the DataProcess_Reallocate_C_String(),
 *		DataProcess_Reallocate_C_String_With_NULL_Terminator(),
 *		and DataProcess_Deallocate_CString() functions.
 *
 *		Note: This test function depends on a working DataProcess_Trivial_Random_Number_Generator()
 *		function to work correctly, and may produce inaccurate results if
 *		DataProcess_Trivial_Random_Number_Generator() does not work correctly.
 */
int Unit_Tests_DataProcess_Allocator_and_Deallocator()
{
	/* Define the passed test message. */
#define TEST_PASSED_MSG "Unit_Tests_DataProcess_Allocator_and_Deallocator(): TEST_PASSED"

	/* Define the error messaging macros. */
#define TEST_FAILURE_MSG_HEAD "TEST_FAILURE: Unit_Tests_DataProcess_Allocator_and_Deallocator(): "
#define TEST_ERROR_LOG_REAL(ERR_MSG) printf("%s", TEST_FAILURE_MSG_HEAD); printf("%s", ERR_MSG);
#define TEST_ERROR_LOG(ERR_MSG) TEST_ERROR_LOG_REAL(ERR_MSG)

	/* Init vars. */
	int ret = -999;										/* Result of the tests. */
	int retFromCall = COMMON_ERROR_UNKNOWN_ERROR;		/* Result code from engine function. */
	size_t x = 0;										/* Counter used in random string generation loop. */
	size_t randVal = 0;									/* Result from the call to TRNG() function. */
	size_t randStringLength = 0;						/* Length of the random string. */
	char * currentString = NULL;						/* The current string pointer. */
	char * previousString = NULL;						/* The previous string pointer. */
	char * randString = NULL;							/* A random string. */
	const char * byteAllocationTestMSG = "Attempting to allocate one (1) byte using DataProcess_Reallocate_C_String().\n";
	const char * byteAllocationFailMSG = "Unable to allocate one (1) byte. ";
	const char * byteReallocationTestMSG = "Attempting to reallocate the byte using DataProcess_Reallocate_C_String().\n";
	const char * byteReallocationFailMSG = "Unable to reallocate the byte. ";
	const char * byteDeallocationTestMSG = "Attempting to deallocate the byte using DataProcess_Deallocate_CString().\n";
	const char * byteDeallocationFailMSG = "Unable to deallocate the byte.\n";
	const char * useAsAllocatorTestMSG = "Attempting to use DataProcess_Reallocate_C_String() as a memory allocator.\n";
	const char * useAsAllocatorFailMSG = "Unable to use DataProcess_Reallocate_C_String() as a memory allocator.\n";
	const char * rangeTest1MSG = "Attempting to reallocate the following string < ";
	const char * rangeTest2MSG = " > using only the first ";
	const char * rangeTest3MSG = " bytes";
	const char * rangeFailMSG = "Unable to reallocate the following string < ";
	const char * dataMismatch1FailMSG = "Copied string < ";
	const char * dataMismatch2FailMSG = " > does not match the source string.\n";
	const char * reallocationWithNullTermTestMSG = "Attempting to reallocate the random string with a NULL termination byte using DataProcess_Reallocate_C_String_With_NULL_Terminator().\n";
	const char * reallocationWithNullTermFailMSG = "Unable to reallocate the random string with a NULL termination byte.\n";
	const char * reallocationWithNullTermFailInvalidSize1MSG = "Expected length of NULL terminated string was: ";
	const char * reallocationWithNullTermFailInvalidSize2MSG = ". The returned length was: ";
	const char * reallocationWithNullTermFailNoNullMSG = "The reallocated string is not null byte terminated.";
	const char * reallocationWithPreExistingNullTermTestMSG = "Attempting to reallocate the random string using DataProcess_Reallocate_C_String_With_NULL_Terminator() with a NULL termination byte already present.\n";
	const char * reallocationWithPreExistingNullTermFailMSG = "Unable to reallocate the random string with a pre-existing NULL termination byte using DataProcess_Reallocate_C_String_With_NULL_Terminator().\n";
	const char * reallocateCStringFunctMSG = "DataProcess_Reallocate_C_String()";
	const char * reallocateCStringWithNullFunctMSG = "DataProcess_Reallocate_C_String_With_NULL_Terminator()";

	/* Start test section. */
	printf("%s", START_TEST_SECTION);

	/* Attempt to allocate a small amount of memory. */
	printf("%s", byteAllocationTestMSG);
	retFromCall = DataProcess_Reallocate_C_String(&currentString, 0, 1);
	if ((retFromCall == COMMON_ERROR_SUCCESS) && (currentString != NULL))
	{
		/* Copy the pointer. */
		previousString = currentString;

		/* Now attempt to reallocate the string. */
		printf("%s", byteReallocationTestMSG);
		retFromCall = retFromCall = DataProcess_Reallocate_C_String(&currentString, 1, 1);
		if ((retFromCall == COMMON_ERROR_SUCCESS) && (currentString != NULL) && (currentString != previousString))
		{
			/* Set previousString to NULL.
				(The string was deallocated by DataProcess_Reallocate_C_String() as it was a copy of currentString's pointer value.)
			*/
			previousString = NULL;

			/* Test the deallocation function. */
			printf("%s", byteDeallocationTestMSG);
			DataProcess_Deallocate_CString(&currentString);
			if (currentString == NULL)
			{
				/* Warn user about TRNG use. */
				printf("%s", TRNGUseMayFailMSG);
				fflush(stdout);

				/* Create the TRNG String. */
				retFromCall = Unit_Tests_DataProcess_Random_String_Generator(&randString, &randStringLength);
				if ((retFromCall == 0) && (randString != NULL) && (randStringLength > 0))
				{
					/* Reset retFromCall. */
					retFromCall = COMMON_ERROR_UNKNOWN_ERROR;

					/* Allocate memory to copy the random string into. */
					printf("%s", useAsAllocatorTestMSG);
					retFromCall = DataProcess_Reallocate_C_String(&currentString, 0, randStringLength);
					if ((retFromCall == COMMON_ERROR_SUCCESS) && (currentString != NULL))
					{
						/* Copy the random string, because reallocating it will loose data. */
						memcpy(currentString, randString, randStringLength);

						/* Copy the pointer. (To make sure a new allocation is made.) */
						previousString = currentString;

						/* Generate one final random number to determine how much of the random string should be copied. */
						randVal = DataProcess_Trivial_Random_Number_Generator(2, (randStringLength - 1), false);

						/* Check and see if giving a range of the source string outputs the correct sub-string. */
						printf("%s%s%s%i%s%s", rangeTest1MSG, randString, rangeTest2MSG, randVal, rangeTest3MSG, periodAndNewlineMSG);
						retFromCall = DataProcess_Reallocate_C_String(&currentString, randStringLength, randVal);
						if ((retFromCall == COMMON_ERROR_SUCCESS) && (currentString != previousString) && (currentString != randString))
						{
							/* Set previousString to NULL.
								(The string was deallocated by DataProcess_Reallocate_C_String() as it was a copy of currentString's pointer value.)
							 */
							previousString = NULL;

							/* Begin verification loop. */
							for (x = 0; ((x < randVal) && (x < randStringLength)); x++)
							{
								/* Check for identical data in both strings. */
								if (randString[x] != currentString[x])
								{
									/* Data mismatch. */
									break;
								}
							}

							/* Check result of verification loop. */
							if ((x == randVal) || (x == randStringLength))
							{
								/* Test the DataProcess_Reallocate_C_String_With_NULL_Terminator() function by setting the
									last byte of the currentString to a non-zero value.
								*/
								if (currentString[(randVal - 1)] == 0x0)
								{
									currentString[(randVal - 1)] = 0x1;
								}

								/* Copy the string pointer. (To verifiy a new allocation was made.) */
								previousString = currentString;

								/* Abuse x to store the current random value. */
								x = randVal;

								/* Now reallocate the string. */
								printf("%s", reallocationWithNullTermTestMSG);
								retFromCall = DataProcess_Reallocate_C_String_With_NULL_Terminator(&currentString, randVal, &x);
								if ((retFromCall == COMMON_ERROR_SUCCESS) && (currentString != NULL) && (currentString != previousString) &&
									(currentString[(randVal)] == '\0'))
								{
									/* Set previousString to NULL.
										(The string was deallocated by DataProcess_Reallocate_C_String() as it was a copy of currentString's pointer value.)
									 */
									previousString = NULL;

									/* Begin verification loop. */
									for (x = 0; ((x < randVal) && (x < randStringLength)); x++)
									{
										/* Check for identical data in both strings. */
										if (randString[x] != currentString[x])
										{
											/* Data mismatch. */
											break;
										}
									}

									/* Check result of verification loop. */
									if ((x == randVal) || (x == randStringLength))
									{
										/* Copy the pointer. */
										previousString = currentString;

										/* Recall DataProcess_Reallocate_C_String_With_NULL_Terminator() with a NULL'd string.
										   The size of the string should not change in this case.
										 */
										printf("%s", reallocationWithPreExistingNullTermTestMSG);
										retFromCall = DataProcess_Reallocate_C_String_With_NULL_Terminator(&currentString, randVal, &x);
										if ((retFromCall == COMMON_ERROR_SUCCESS) && (currentString != NULL) && (currentString != previousString) &&
											((randVal < randStringLength) ? (currentString[(randVal)] == '\0') : (currentString[(randStringLength + 1)])))
										{
											/* Set previousString to NULL.
												(The string was deallocated by DataProcess_Reallocate_C_String() as it was a copy of currentString's pointer value.)
											 */
											previousString = NULL;

											/* Begin verification loop. */
											for (x = 0; ((x < randVal) && (x < randStringLength)); x++)
											{
												/* Check for identical data in both strings. */
												if (randString[x] != currentString[x])
												{
													/* Data mismatch. */
													break;
												}
											}

											/* Check result of verification loop. */
											if ((x == randVal) || (x == randStringLength))
											{
												/* Test for invalid argument caused by invalid pointer to pointer. */
												printf("%s%s%s", InvalidArgStringPointerTestMSG, reallocateCStringFunctMSG, periodAndNewlineMSG);
												retFromCall = DataProcess_Reallocate_C_String(NULL, 0, x);
												if (retFromCall == COMMON_ERROR_INVALID_ARGUMENT)
												{
													/* Test for invalid argument caused by invalid pointer to pointer. */
													printf("%s%s%s", InvalidArgStringPointerTestMSG, reallocateCStringWithNullFunctMSG, periodAndNewlineMSG);
													retFromCall = DataProcess_Reallocate_C_String_With_NULL_Terminator(NULL, 0, &x);
													if (retFromCall == COMMON_ERROR_INVALID_ARGUMENT)
													{
														/* Test for invalid argument caused by invalid pointer to pointer. */
														printf("%s%s%s", InvalidArgLengthPointerTestMSG, reallocateCStringWithNullFunctMSG, periodAndNewlineMSG);
														retFromCall = DataProcess_Reallocate_C_String_With_NULL_Terminator(&currentString, 0, NULL);
														if (retFromCall == COMMON_ERROR_INVALID_ARGUMENT)
														{
															/* Test successful. */
															printf("%s%s", TEST_PASSED_MSG, periodAndNewlineMSG);
															ret = 0;
														}
														else
														{
															/* Did not get COMMON_ERROR_INVALID_ARGUMENT error code from () due to invalid newLength pointer. */
															ret = -14;
															printf("%s%s%s", InvalidArgLengthPointerFailMSG, reallocateCStringWithNullFunctMSG, periodAndNewlineMSG);
														}
													}
													else
													{
														/* Did not get COMMON_ERROR_INVALID_ARGUMENT error code from () due to invalid string pointer. */
														ret = -13;
														printf("%s%s%s", InvalidArgStringPointerFailMSG, reallocateCStringWithNullFunctMSG, periodAndNewlineMSG);
													}
												}
												else
												{
													/* Did not get COMMON_ERROR_INVALID_ARGUMENT error code from DataProcess_Reallocate_C_String(). */
													ret = -12;
													printf("%s%s%s", InvalidArgStringPointerFailMSG, reallocateCStringFunctMSG, periodAndNewlineMSG);
												}
											}
											else
											{
												/* Reallocation with NULL byte failed. Data Mismatch. */
												ret = -11;
												TEST_ERROR_LOG(reallocationWithPreExistingNullTermFailMSG);
												printf("%s%s%s", dataMismatch1FailMSG, currentString, dataMismatch2FailMSG);
											}
										}
										else
										{
											/* Reallocation with NULL byte failed. */
											ret = -10;
											TEST_ERROR_LOG(reallocationWithPreExistingNullTermFailMSG);
											((retFromCall != COMMON_ERROR_SUCCESS) ? (printf("%s%i%s", errorCodeReturnedMSG, retFromCall, ".\n")) :
												(currentString == NULL) ? (printf("%s", errorSuccessNoResultMSG)) :
												(currentString == previousString) ? (printf("%s", errorSamePtrMSG)) :
												(printf(reallocationWithNullTermFailNoNullMSG)));
										}
									}
									else
									{
										/* Reallocation with NULL byte failed. Data Mismatch. */
										ret = -9;
										TEST_ERROR_LOG(reallocationWithNullTermFailMSG);
										printf("%s%s%s", dataMismatch1FailMSG, currentString, dataMismatch2FailMSG);
									}
								}
								else
								{
									/* Reallocation with NULL byte failed. */
									ret = -8;
									TEST_ERROR_LOG(reallocationWithNullTermFailMSG);
									((retFromCall != COMMON_ERROR_SUCCESS) ? (printf("%s%i%s", errorCodeReturnedMSG, retFromCall, ".\n")) :
										(currentString == NULL) ? (printf("%s", errorSuccessNoResultMSG)) :
										(currentString == previousString) ? (printf("%s", errorSamePtrMSG)) :
										(x != randVal) ? (printf("%s%i%s%i%s" , reallocationWithNullTermFailInvalidSize1MSG, randVal,
										reallocationWithNullTermFailInvalidSize2MSG, x, periodAndNewlineMSG)) : (printf(reallocationWithNullTermFailNoNullMSG)));
								}
							}
							else
							{
								/* Error data mismatch. */
								ret = -7;
								TEST_ERROR_LOG(rangeFailMSG);
								printf("%s%s%i%s%s%s%s%s", randString, rangeTest2MSG, randVal, rangeTest3MSG, periodAndNewlineMSG, dataMismatch1FailMSG, currentString, dataMismatch2FailMSG);
							}
						}
						else
						{
							/* Could not complete range test. */
							ret = -6;
							TEST_ERROR_LOG(rangeFailMSG);
							printf("%s%s%i%s", randString, rangeTest2MSG, randVal, rangeTest3MSG);
							((retFromCall != COMMON_ERROR_SUCCESS) ? (printf("%s%i%s", errorCodeReturnedMSG, retFromCall, ".\n")) :
								(currentString == NULL) ? (printf("%s", errorSuccessNoResultMSG)) : (printf("%s", errorSamePtrMSG)));
						}
					}
					else
					{
						/* Could not allocate memory? */
						ret = -5;
						TEST_ERROR_LOG(useAsAllocatorFailMSG);
						((retFromCall != COMMON_ERROR_SUCCESS) ? (printf("%s%i%s", errorCodeReturnedMSG, retFromCall, ".\n")) :
							(printf("%s", errorSuccessNoResultMSG)));
					}
				}
				else
				{
					/* Could not allocate memory? */
					ret = -4;
					TEST_ERROR_LOG(useAsAllocatorFailMSG);
					((retFromCall != COMMON_ERROR_SUCCESS) ? (printf("%s%i%s", errorCodeReturnedMSG, retFromCall, ".\n")) :
						(printf("%s", errorSuccessNoResultMSG)));
				}
			}
			else
			{
				/* Could not deallocate the byte. */
				ret = -3;
				TEST_ERROR_LOG(byteDeallocationFailMSG);
			}
		}
		else
		{
			/* Could not reallocate the byte. */
			ret = -2;
			TEST_ERROR_LOG(byteReallocationFailMSG);
			((retFromCall != COMMON_ERROR_SUCCESS) ? (printf("%s%i%s", errorCodeReturnedMSG, retFromCall, ".\n")) :
				((currentString != NULL) ? (printf("%s", errorSuccessNoResultMSG)) : (printf("%s", errorSamePtrMSG))));
		}

		/* Flush output buffer. */
		fflush(stdout);

		/* Make sure to release memory if needed. */
		if (currentString != NULL)
		{
			DataProcess_Deallocate_CString(&currentString);
		}
		if (previousString != NULL)
		{
			DataProcess_Deallocate_CString(&previousString);
		}
		if (randString != NULL)
		{
			DataProcess_Deallocate_CString(&randString);
		}
	}
	else
	{
		/* Could not allocate a byte? */
		ret = -1;
		TEST_ERROR_LOG(byteAllocationFailMSG);
		((retFromCall != COMMON_ERROR_SUCCESS) ? (printf("%s%i%s", errorCodeReturnedMSG, retFromCall, ".\n")) :
			(printf("%s", errorSuccessNoResultMSG)));
	}

	/* End test section. */
	printf("%s", END_TEST_SECTION);

	/* Exit function. */
	return ret;

	/* Undefine the macros. */
#undef TEST_ERROR_LOG
#undef TEST_ERROR_LOG_REAL
#undef TEST_FAILURE_MSG_HEAD
#undef TEST_PASSED_MSG
}

/*!
 *	int Unit_Tests_DataProcess_sizet_cstring_converter_string_verification_number_conversion_function()
 *
 *	Takes a given number between zero (0) and ten (10) and returns it's arabic numeral text character.
 *
 *	If the given number is outside the range of zero (0) and ten (10) then -1 is returned.
 */
int Unit_Tests_DataProcess_sizet_cstring_converter_string_verification_number_conversion_function(const size_t number)
{
	/* Define numbersLength. */
#define NUMBERSLENGTH 11

	/* Init vars. */
	int ret = -1;		/* The result of this function. */
	const char numbers[NUMBERSLENGTH] = {"0123456789"};		/* Array to contain the text versions of the given numbers. */

	/* Check given number argument. */
	if ((0 <= number) && (number < 10))
	{
		/* Get the number so we can return it. */
		ret = (char)(numbers[number]);
	}

	/* Exit function. */
	return ret;

	/* Undef NUMBERSLENGTH. */
#undef NUMBERSLENGTH
}

/*!
 *	int Unit_Tests_DataProcess_sizet_cstring_converter_string_verification_function(const size_t randomNumber, const char * string, const size_t stringLength)
 *
 *	Ok, the purpose of this function is to verify that a generated string matches the number it was made from.
 *
 *	To that extent, we wind up reimplimenting the functionality of DataProcess_getCStringFromSizeT(),
 *	but instead of creating a string we are checking it for accuracy.
 */
int Unit_Tests_DataProcess_sizet_cstring_converter_string_verification_function(const size_t randomNumber, const char * string, const size_t stringLength)
{
		/* Define the error messaging macros. */
#define TEST_FAILURE_MSG_HEAD "TEST_FAILURE: Unit_Tests_DataProcess_sizet_cstring_converter_string_verification_function(): "
#define TEST_ERROR_LOG_REAL(ERR_MSG) printf("%s", TEST_FAILURE_MSG_HEAD); printf("%s", ERR_MSG);
#define TEST_ERROR_LOG(ERR_MSG) TEST_ERROR_LOG_REAL(ERR_MSG)

	/* Define the numeric base of DataProcess_getCStringFromSizeT(). */
#define TEST_NUMERIC_BASE 10

	/* Init vars. */
	char cNumber = '0';			/* Used to hold the current number we are checking for in the given string. */
	int ret = -1;				/* The result of this function. */
	size_t currentValue = 0;	/* The current number being verified. */
	size_t x = 0;				/* Counter used in verififcation loop. */

	/* Check for invalid arguments. */
	if ((string != NULL) && (stringLength > 0))
	{
		/* Set current value. */
		currentValue = randomNumber;

		/* Begin verification loop. */
		for (x = 0; ((ret == -1) && (x < (stringLength - 1)) && (((stringLength - 2) - x) >= 0) && (currentValue > 0)); x++)
		{
			/* Devide off the last digit and convert it to a text character. */
			cNumber = Unit_Tests_DataProcess_sizet_cstring_converter_string_verification_number_conversion_function((currentValue % TEST_NUMERIC_BASE));

			/* Check the text character for a match in the given string. */
			if (string[((stringLength - 2) - x)] == cNumber)
			{
				/* Proceed to the next value in the string. */
				currentValue /= TEST_NUMERIC_BASE;
			}
			else
			{
				/* Invalid text string. */
				ret = -3;
			}
		}

		/* Check counter value for success. */
		if ((ret == -1) && (x == (stringLength - 1)))
		{
			/* String matches the number. */
			ret = 0;
		}
		else
		{
			/* Invalid string. */
			ret = -3;
		}
	}
	else
	{
		/* Invalid argument. */
		ret = -2;
		TEST_ERROR_LOG("Invalid argument.\n");
	}

	/* Exit function. */
	return ret;

	/* Undef macros. */
#undef TEST_NUMERIC_BASE
#undef TEST_ERROR_LOG_REAL
#undef TEST_ERROR_LOG
#undef TEST_FAILURE_MSG_HEAD
}

/*!
 *		int Unit_Tests_DataProcess_sizet_cstring_converter()
 *
 *		This function tests the DataProcess_getCStringFromSizeT() function.
 */
int Unit_Tests_DataProcess_sizet_cstring_converter()
{
	/* Define the name of the function. */
#define MSYS_FUNCT_NAME	"Unit_Tests_DataProcess_sizet_cstring_converter()"
#define MSYS_TESTING_FUNCT_NAME "DataProcess_getCStringFromSizeT()"

	/* Define the passed test message. */
#define TEST_PASSED_MSG "Unit_Tests_DataProcess_sizet_cstring_converter(): TEST_PASSED"

	/* Define the error messaging macros. */
#define TEST_FAILURE_MSG_HEAD "TEST_FAILURE: Unit_Tests_DataProcess_sizet_cstring_converter(): "
#define TEST_ERROR_LOG_REAL(ERR_MSG) printf("%s", TEST_FAILURE_MSG_HEAD); printf("%s", ERR_MSG);
#define TEST_ERROR_LOG(ERR_MSG) TEST_ERROR_LOG_REAL(ERR_MSG)

	/* Define the limits on the random number range. (MINIMAL value should be less than the MAXIMUM value and both should be positive.) */
#define TEST_MINIMAL_RANDOM_NUMBER_VALUE 1
#define TEST_MAXIMUM_RANDOM_NUMBER_VALUE 100

	/* Init vars. */
	int ret = 0;									/* The result of this test function. */
	int retFromCall = COMMON_ERROR_UNKNOWN_ERROR;	/* The result of a call to an engine function. */
	size_t randVal = 0;								/* Used to generate a random number to use with DataProcess_getCStringFromSizeT(). */
	size_t currentStringLength = 0;					/* The length of the currentString.... string. */
	char * currentString = NULL;						/* The current string pointer. */
	char * previousString = NULL;						/* The previous string pointer. */

	/* Start test section. */
	printf("%s", START_TEST_SECTION);

	/* Warn user about TRNG use. */
	printf("%s", TRNGUseMayFailMSG);
	fflush(stdout);

	/* Generate a random number. */
	printf("%s%s", MSYS_FUNCT_NAME, " Attempting to generate a random number.\n");
	randVal = DataProcess_Trivial_Random_Number_Generator(TEST_MINIMAL_RANDOM_NUMBER_VALUE, TEST_MAXIMUM_RANDOM_NUMBER_VALUE, true);
	if (randVal != 0)
	{
		/* Attempt to generate the string version of the random number. */
		printf("%s%s%i%s", MSYS_FUNCT_NAME, " Attempting to generate the string version of the random number: <", randVal, ">.\n");
		retFromCall = DataProcess_getCStringFromSizeT(randVal, &currentString, &currentStringLength);
		if ((retFromCall == COMMON_ERROR_SUCCESS) && (currentString != NULL) && (currentStringLength > 0))
		{
			/* Check the result.... */
			printf("%s%s", MSYS_FUNCT_NAME, " checking result.\n");
			ret = Unit_Tests_DataProcess_sizet_cstring_converter_string_verification_function(randVal, currentString, currentStringLength);
			if (ret == 0)
			{
				/* Copy the pointer. */
				previousString = currentString;

				/* Reset currentStringLength. */
				currentStringLength = 0;

				/* Check and see if the function will overwrite the given pointer. */
				printf("%s%s%s%s", MSYS_FUNCT_NAME, " checking to see if the given string pointer will be overwritten by ", MSYS_TESTING_FUNCT_NAME, periodAndNewlineMSG);
				retFromCall = DataProcess_getCStringFromSizeT(randVal, &currentString, &currentStringLength);
				if ((retFromCall == COMMON_ERROR_SUCCESS) && (currentString != NULL) && (currentString != previousString) && (currentStringLength > 0))
				{
					/* Deallocate the strings. */
					DataProcess_Deallocate_CString(&previousString);
					DataProcess_Deallocate_CString(&currentString);
					currentStringLength = 0;

					/* Check for INVALID_ARGUMENT error code if DataProcess_getCStringFromSizeT() is given a bad string pointer. */
					printf("%s%s%s", InvalidArgStringPointerTestMSG, MSYS_TESTING_FUNCT_NAME, periodAndNewlineMSG);
					retFromCall = DataProcess_getCStringFromSizeT(randVal, NULL, &currentStringLength);
					if (retFromCall == COMMON_ERROR_INVALID_ARGUMENT)
					{
						/* Check for INVALID_ARGUMENT error code if DataProcess_getCStringFromSizeT() is given a bad stringLength pointer. */
						printf("%s%s%s", InvalidArgLengthPointerTestMSG, MSYS_TESTING_FUNCT_NAME, periodAndNewlineMSG);
						retFromCall = DataProcess_getCStringFromSizeT(randVal, &currentString, NULL);
						if (retFromCall == COMMON_ERROR_INVALID_ARGUMENT)
						{
							/* Test successful. */
							printf("%s%s", TEST_PASSED_MSG, periodAndNewlineMSG);
							ret = 0;
						}
						else
						{
							/* Did not get invalid argument error code for bad string length pointer. */
							ret = -6;
							TEST_ERROR_LOG(InvalidArgLengthPointerFailMSG);
							printf("%s%s", MSYS_TESTING_FUNCT_NAME, periodAndNewlineMSG);
							printf("%s%i%s", errorCodeReturnedMSG, retFromCall, periodAndNewlineMSG);
						}
					}
					else
					{
						/* Did not get invalid argument error code for bad string pointer. */
						ret = -5;
						TEST_ERROR_LOG(InvalidArgStringPointerFailMSG);
						printf("%s%s", MSYS_TESTING_FUNCT_NAME, periodAndNewlineMSG);
						printf("%s%i%s", errorCodeReturnedMSG, retFromCall, periodAndNewlineMSG);
					}
				}
				else
				{
					/* Test of overwriting the given pointer failed. */
					ret = -4;
					TEST_ERROR_LOG("overwriting the given pointer failed.\n");
					((retFromCall != COMMON_ERROR_SUCCESS) ? (printf("%s%i%s", errorCodeReturnedMSG, retFromCall, periodAndNewlineMSG)) :
					 (currentString == previousString) ? (printf("%s", errorSamePtrMSG)) :
					 (printf("%s", errorSuccessNoResultMSG)));
				}
			}
			else
			{
				/* Verification of string failed. */
				ret = -3;
				TEST_ERROR_LOG("Verification of string failed.\n");
				printf("%s%i%s%s%s", "The random number <", randVal, "> does not match the generated string <", currentString, ">.\n");
			}

			/* Deallocate the result if needed. */
			if (currentString != NULL)
			{
				DataProcess_Deallocate_CString(&currentString);
				currentStringLength = 0;
			}
		}
		else
		{
			/* Could not generate c-string. */
			ret = -2;
			TEST_ERROR_LOG("Could not generate c-string.\n");
			((retFromCall != COMMON_ERROR_SUCCESS) ? (printf("%s%i%s", errorCodeReturnedMSG, retFromCall, periodAndNewlineMSG)) :
				(printf("%s", errorSuccessNoResultMSG)));
		}
	}
	else
	{
		/* Could not generate a random number. */
		ret = -1;
		TEST_ERROR_LOG("Could not generate a random number.\n");
	}

	/* End test section. */
	printf("%s", END_TEST_SECTION);

	/* Flush output buffer. */
	fflush(stdout);

	/* Exit function. */
	return ret;

	/* Check for invalid random number range. */
#if TEST_MINIMAL_RANDOM_NUMBER_VALUE < 1
#error "Unit_Tests_DataProcess_sizet_cstring_converter(): TEST_MINIMAL_RANDOM_NUMBER_VALUE must be a greater than or equal to one (1)."
#endif	/* TEST_MINIMAL_RANDOM_NUMBER_VALUE < 1 */
#if TEST_MAXIMUM_RANDOM_NUMBER_VALUE < 2
#error "Unit_Tests_DataProcess_sizet_cstring_converter(): TEST_MAXIMUM_RANDOM_NUMBER_VALUE must be a greater than or equal to two (2)."
#endif /* TEST_MAXIMUM_RANDOM_NUMBER_VALUE < 2 */

	/* Undefine the macros. */
#undef TEST_MAXIMUM_RANDOM_NUMBER_VALUE
#undef TEST_MINIMAL_RANDOM_NUMBER_VALUE
#undef TEST_ERROR_LOG_REAL
#undef TEST_ERROR_LOG
#undef TEST_FAILURE_MSG_HEAD
#undef TEST_PASSED_MSG
#undef MSYS_FUNCT_NAME
}

int Unit_Tests_DataProcess_Main()
{
	/* Init vars. */
	int ret = 0;								/* Result of the tests. */
	int retFromTRNGTest = 0;					/* Result of the TRNG test. */
	int retFromAllocatorTest = 0;				/* Result of the allocator and deallocator tests. */
	int retFromSizeTCStringConversionTest = 0;	/* Result of the size_t to c-string conversion tests. */

	/* Begin tests for DataProcess_Trivial_Random_Number_Generator(). */
	retFromTRNGTest = Unit_Tests_DataProcess_TRNG();

	/* Begin tests for DataProcess_Reallocate_C_String() and DataProcess_Deallocate_CString(). */
	retFromAllocatorTest = Unit_Tests_DataProcess_Allocator_and_Deallocator();

	/* Begin tests for DataProcess_getCStringFromSizeT(). */
	retFromSizeTCStringConversionTest = Unit_Tests_DataProcess_sizet_cstring_converter();

	/* Return ret. */
	return ret;
}
