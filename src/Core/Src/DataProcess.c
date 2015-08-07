/*!
    Multiverse Engine Project DataProcess DataProcess.c	07/8/2015

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

/* Set extern C. */
#ifdef __cplusplus
extern "C" {
#endif	/* __cplusplus */

/* Internal includes. */
#include "DataProcess.h"
#include "../../Common/Src/Error_Handler/Common_Error_Handler_Error_Codes.h"	/* Defines Common Error Codes. */

/* External includes. */
#include <time>

size_t DataProcess_Trivial_Random_Number_Generator(const size_t min_value, const size_t max_value, const bool reset_rand)
{
	/* NO, it's not 4..... (Although it could be. I won't lie.) */

	/* Set static. */
	static bool rand_set;

	/* Check if we need to set the RNG. */
	if ((!rand_set) || (reset_rand))
	{
		/* Seed random number generator. */
		srand(time(NULL));

		/* Set rand_set. */
		rand_set = true;
	}

	/* Return the result. */
	return (rand() % max_value + min_value);
}

int DataProcess_Reallocate_C_String(char ** str, const size_t strLength, const size_t newLength)
{
	/* Init vars. */
	int ret = COMMON_ERROR_UNKNOWN_ERROR;	/* The result code for this function. */
	char * tempStr = NULL;					/* Temporary string pointer used during reallocation.*/

	/* Check for invalid arguments. */
	if (str != NULL)
	{
		/* Allocate memory for new string. (If needed.) */
		if (newLength > 0)
		{
			tempStr = (char *)malloc(newLength);
			if (tempStr != NULL)
			{
				/* NULL out the new string. */
				memset(tempStr, '\0', newLength);

				/* Check and see if we need to copy the old data. */
				if (((*str) != NULL) && (strLength > 0))
				{
					/* Determine which length is longer. */
					if (newLength < strLength)
					{
						/* Copy the old data. */
						memcpy(tempStr, (*str), newLength);
					}
					else
					{
						/* Copy the old data. */
						memcpy(tempStr, (*str), strLength);
					}

					/* Make sure the tempStr is NULL terminated. */
					tempStr[(newLength - 1)] = '\0';
				}
			}
			else
			{
				/* Could not allocate memory. */
				ret = COMMON_ERROR_MEMORY_ERROR;
			}
		}

		/* Deallocate the old string. (If needed.) */
		if ((*str) != NULL)
		{
			free((*str));
			(*str) = NULL;
		}

		/* Copy the new string pointer if needed. */
		if ((newLength > 0) && (ret == COMMON_ERROR_UNKNOWN_ERROR) && (tempStr != NULL))
		{
			(*str) = tempStr;
		}

		/* Done. */
		ret = COMMON_ERROR_SUCCESS;
	}
	else
	{
		/* Invalid argument. */
		ret = COMMON_ERROR_INVALID_ARGUMENT;
	}

	/* Exit function. */
	return ret;
}

void DataProcess_Deallocate_CString(char ** str)
{
	/* Check for invalid arguments. */
	if ((str != NULL) && ((*str) != NULL))
	{
		/* Deallocate (*str) and set it to NULL. */
		free((*str));
		(*str) = NULL;
	}

	/* Exit function. */
	return;
}

int DataProcess_getCStringFromSizeT(const size_t number, char ** str, size_t * strLength)
{
	/* Init vars. */
	size_t currentNum = 0;						/* Temporary value used to store the current number we are working on. */
	char outputValue = '\0';					/* The value that we need to write into the output buffer. (Calculated from currentNum.) */
	int ret = COMMON_ERROR_UNKNOWN_ERROR;		/* The result code of this function. */
	char * result = NULL;						/* The resulting string of this function. */
	char * previousResult = NULL;				/* Temporary pointer used to copy previously generated data into the current result. */
	size_t resultLength = 1;					/* The size of the result string. Set to one by default to allow the string to be NULL terminated. */
	const char outputValues[10] = "0123456789";	/* C-String used to map a generated value to it's corresponding character. */

	/* Check for invalid arguments. */
	if ((str != NULL) && (strLength != NULL))
	{
		/* Allocate memory for result. */
		result = (char *)malloc(resultLength);
		if (result != NULL)
		{
			/* Set currentNum. */
			currentNum = number;

			/* Begin value parsing loop. */
			do
			{
				/* Read the current byte's value from right to left. (Mod is a reduction operation.) */
				outputValue = (currentNum % 10);

				/* Copy the current buffer's pointer because we are about to create a new one. */
				previousResult = result;

				/* Increment the size of the new buffer. */
				resultLength++;

				/* Allocate the new buffer. */
				result = (char*)malloc(resultLength);

				/* Check for successful memory allocation. */
				if (result != NULL)
				{
					/* Blank out the new buffer. */
					memset(result, '\0', resultLength);

					/* Set the first value as the previous data comes after it. */
					result[0] = outputValues[outputValue];

					/* If we have any previous data we need to copy it into the new buffer and deallocate the previous one. */
					if (previousResult != NULL)
					{
						memcpy((result + 1), previousResult, (resultLength - 1));
						free(previousResult);
						previousResult = NULL;
					}

					/* Get the next value by chopping off the "ones place", aka divide by the current base. */
					currentNum /= 10;
				}
				else
				{
					/* Could not allocate memory for output buffer. */
					ret = COMMON_ERROR_MEMORY_ERROR;
				}
			} while ((currentNum) && (ret != COMMON_ERROR_MEMORY_ERROR));

			/* Check for success. */
			if ((ret == COMMON_ERROR_UNKNOWN_ERROR) && (result != NULL) && (resultLength > 0))
			{
				/* Copy result pointer, and length. */
				(*str) = result;
				(*strLength) = resultLength;

				/* Done. */
				ret = COMMON_ERROR_SUCCESS;
			}
			else
			{
				/* Deallocate result if needed. */
				if (result != NULL)
				{
					free(result);
					result = NULL;
				}
				resultLength = 0;
			}
		}
		else
		{
			/* Could not allocate memory for result string. */
			ret = COMMON_ERROR_MEMORY_ERROR;
		}
	}
	else
	{
		/* Invalid argument(s). */
		ret = COMMON_ERROR_INVALID_ARGUMENT;
	}

	/* Exit function. */
	return ret;
}

#ifdef __cplusplus
}	/* End of extern "C". */
#endif	__cplusplus
