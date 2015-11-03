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
#include <time.h>

size_t DataProcess_Trivial_Random_Number_Generator(const size_t min_value, const size_t max_value, const bool reset_rand)
{
	/* Define MAX_MODIFIER */
#define MAX_MODIFIER 100000 /* Used to prevent overflowing the static modifier variable below. */

	/* NO, it's not 4..... (Although it could be. I won't lie.) */

	/* Init vars. */
	static bool rand_set;			/* Whether or not the random seed has been set or not. */
	static size_t modifier;			/* Used to ensure that the random seed is unique if the function is called more than once within the timeframe of a second. */
	time_t tt;						/* The current system time as a time_t. */
	struct tm * timeM = NULL;		/* The current system time as a tm structure. */

	/* Check if we need to set the RNG. */
	if ((!rand_set) || (reset_rand))
	{
		/* Increment modifier. */
		modifier = ((modifier < MAX_MODIFIER) ? (modifier + 1) : (0));

		/* Get the current system time. */
		time(&tt);

		/* Convert the current system time to a tm structure. */
		timeM = gmtime(&tt);

		/* Check for NULL pointer. */
		if (timeM != NULL)
		{
			/* Seed random number generator. */
			srand(((timeM->tm_sec) + (timeM->tm_min) + (timeM->tm_hour) + (timeM->tm_yday) + (timeM->tm_year) + (timeM->tm_mon) + (modifier)));

			/* Set rand_set. */
			rand_set = true;
		}
		else
		{
			/* Clear rand_set, so we can try again on the next call. */
			rand_set = false;
		}
	}

	/* Return the result. */
	return ((rand_set) ? (rand() % max_value + min_value) : (0));

/* Undef MAX_MODIFIER. */
#undef MAX_MODIFIER
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
			DataProcess_Deallocate_CString(str);
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

int DataProcess_Reallocate_C_String_With_NULL_Terminator(char ** str, const size_t strLength, size_t * newLength)
{
	/* Init vars. */
	int ret = COMMON_ERROR_UNKNOWN_ERROR;	/* The result of this function. */
	size_t newSize = 0;						/* The modified size if needed. */

	/* Check for valid args. */
	if ((str != NULL) && (newLength != NULL) && (((*str) == NULL) || (strLength > 0)))
	{
		/* Check and see if new length is greater than zero (0). */
		/* Safety check on newSize.... */
		newSize = ((*newLength) > 0) ? (((*newLength) < (SIZE_MAX - (sizeof(char)))) ? ((*newLength) + (sizeof(char))) : (*newLength)) : (0);

		/* Call DataProcess_Reallocate_C_String(). (It will NULL out the allocated buffer before copying data.) */
		ret = DataProcess_Reallocate_C_String(str, strLength, newSize);
		if ((ret == COMMON_ERROR_SUCCESS) && (str != NULL) && ((*str) != NULL))
		{
			/* See if the string is NULL terminated. */
			if ((newSize > 0) && (((*str)[(newSize - 1)]) != '\0'))
			{
				/* Set the last byte to NULL, because it should be.
					(The last byte is always NULL if this function returns COMMON_ERROR_SUCCESS.)
				 */
				((*str)[(newSize - 1)]) = '\0';
			}
		}
	}
	else
	{
		/* Invalid arguments. */
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
	size_t currentNum = 0;							/* Temporary value used to store the current number we are working on. */
	char outputValue = '\0';						/* The value that we need to write into the output buffer. (Calculated from currentNum.) */
	int ret = COMMON_ERROR_UNKNOWN_ERROR;			/* The result code of this function. */
	int retFromCall = COMMON_ERROR_UNKNOWN_ERROR;	/* The result code of a call to an engine function. */
	char * result = NULL;							/* The resulting string of this function. */
	char * previousResult = NULL;					/* Temporary pointer used to copy previously generated data into the current result. */
	size_t resultLength = 1;						/* The size of the result string. Set to one by default to allow the string to be NULL terminated. */
	const char outputValues[10] = "0123456789";		/* C-String used to map a generated value to it's corresponding character. */

	/* Check for invalid arguments. */
	if ((str != NULL) && (strLength != NULL))
	{
		/* Allocate memory for result. */
		retFromCall = DataProcess_Reallocate_C_String(&result, 0, resultLength);
		if ((retFromCall == COMMON_ERROR_SUCCESS) && (result != NULL))
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

				/* Reset the current buffer's pointer. (Otherwise Reallocate_C_String() will deallocate it.) */
				result = NULL;

				/* Increment the size of the new buffer. */
				resultLength++;

				/* Allocate the new buffer. */
				retFromCall = DataProcess_Reallocate_C_String(&result, 0, resultLength);

				/* Check for successful memory allocation. */
				if ((retFromCall == COMMON_ERROR_SUCCESS) && (result != NULL))
				{
					/* Set the first value as the previous data comes after it. */
					result[0] = outputValues[outputValue];

					/* If we have any previous data we need to copy it into the new buffer and deallocate the previous one. */
					if (previousResult != NULL)
					{
						memcpy((result + 1), previousResult, (resultLength - 1));
						DataProcess_Deallocate_CString(&previousResult);
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
					DataProcess_Deallocate_CString(&result);
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

int DataProcess_Get_SubString_Using_Delimiter(const char * src, const size_t srcLength, const char * delim, const size_t delimLength,
												char ** subStr, size_t * subStrLength, const int searchFromEnd, const int getPriorData)
{
	/* Init vars. */
	int foundDelim = 0;								/* Whether or not we have found the delim. */
	int ret = COMMON_ERROR_UNKNOWN_ERROR;			/* The result code of this function. */
	int retFromCall = COMMON_ERROR_UNKNOWN_ERROR;	/* The result code of a call to an engine function. */
	char * tempSubStr = NULL;						/* Used to create the substr. */
	size_t x = 0;									/* Counter used in search loop. */
	size_t y = 0;									/* Counter used in search subloop. */
	size_t tempSubStrLength = 0;					/* Size of the tempSubString. */

	/* Check for invalid arguments. */
	if ((src != NULL) && (srcLength > 0) && (delim != NULL) && (delimLength > 0) && (subStr != NULL) && (subStrLength != NULL))
	{
		/* Begin search loop. */
		for (x = 0; ((x < srcLength) && (!foundDelim) && (ret == COMMON_ERROR_UNKNOWN_ERROR));)
		{
			/* Reset foundDelim. */
			foundDelim = 1;

			/* Begin search subloop for the delim. */
			for (y = 0; ((y < delimLength) && (foundDelim)); y++)
			{
				/* Determine if we are searching from the end of the search string or not. */
				if (searchFromEnd)
				{
					/* Check and see if the current byte is a match to the delim. */
					if (src[((srcLength - 1) - (x + y))] != delim[((delimLength - 1) - y)])
					{
						/* Mismatch, have not found delim. */
						foundDelim = 0;
					}
				}
				else
				{
					/* Check and see if the current byte is a match to the delim. */
					if (src[(x + y)] != delim[y])
					{
						/* Mismatch, have not found delim. */
						foundDelim = 0;
					}
				}
			}

			/* Add the y value to the current x value. (Update the counters.) */
			x += y;
		}	/* End of search loop. */

		/* Check and see if we have found the delim. */
		if ((foundDelim) && (y == delimLength))
		{
			/* We found the delim, Check and see if we need the data after the delimiter or before it. */
			if ((getPriorData) ? ((srcLength - x) > 0) : (((x - delimLength) > 0) && (x < (srcLength - 1))))
			{
				/* Set the size for the new substring. */
				tempSubStrLength = ((getPriorData) ? (srcLength - x) : (x - delimLength));

				/* Allocate memory for the substring. */
				retFromCall = DataProcess_Reallocate_C_String(&tempSubStr, 0, tempSubStrLength);
				if ((retFromCall == COMMON_ERROR_SUCCESS) && (tempSubStr != NULL))
				{
					/* Copy the bytes, before the delimiter if getPriorData is true, otherwise
						Copy the bytes after the delimiter.
					*/
					memcpy(tempSubStr, ((getPriorData) ? (src) :
							(searchFromEnd ? (src + ((srcLength + 1) - x)) : (src + x))),
							tempSubStrLength);

					/* Copy the pointer and size. */
					(*subStr) = tempSubStr;
					(*subStrLength) = tempSubStrLength;

					/* Done. */
					ret = COMMON_ERROR_SUCCESS;
				}
				else
				{
					/* Could not allocate memory for substring. */
					ret = COMMON_ERROR_MEMORY_ERROR;
				}
			}
			else
			{
				/* No bytes remaining to create substring. */
				ret = COMMON_ERROR_END_OF_DATA;
			}
		}
		else
		{
			/* Delim not found in search string. */
			ret = COMMON_ERROR_RANGE_ERROR;
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

int DataProcess_Get_SubString_Using_Offset(const char * src, const size_t srcLength, const size_t offset,
												char ** subStr, size_t * subStrLength, const int searchFromEnd, const int getPriorData)
{
	/* Init vars. */
	int ret = COMMON_ERROR_UNKNOWN_ERROR;			/* The result code of this function. */
	int retFromCall = COMMON_ERROR_UNKNOWN_ERROR;	/* The result code of a call to an engine function. */
	char * tempSubStr = NULL;						/* Used to create the substr. */
	size_t tempRealOffset = 0;						/* Used to hold the real starting offset in the given string. */
	size_t tempSubStrLength = 0;					/* Size of the tempSubString. */

	/* Check for invalid arguments. */
	if ((src != NULL) && (srcLength > 0) && (offset >= 0) && (offset < srcLength) && (subStr != NULL) && (subStrLength != NULL))
	{
		/*
		 *		---------------------------------------------------------------------------------------------------------
		 *		|	searchFromEnd:	|	getPriorData:	|	substring contents:	(Starting and ending offset ranges.)	|
		 *		---------------------------------------------------------------------------------------------------------
		 *		|	FALSE			|	FALSE			|	offset <--> end of string									|
		 *		|	TRUE			|	FALSE			|	(end of string - offset) <--> end of string					|
		 *		|	FALSE			|	TRUE			|	start of string <--> offset									|
		 *		|	TRUE			|	TRUE			|	start of string <--> (end of string - offset)				|
		 *		---------------------------------------------------------------------------------------------------------
		 *
		 *		Note:	searchFromEnd only controls the offset's point of origin. (I.e. which end of the given
		 *				string the offset is based at.) searchFromEnd does NOT control what substring is selected
		 *				based on the given offset; the selection is made based on getPriorData.
		 */

		/* Determine the real starting offset and sub-string length. */
		tempRealOffset = ((searchFromEnd) ? ((getPriorData) ? (0) : ((srcLength - offset))) : ((getPriorData) ? (0) : (offset)));
		tempSubStrLength = ((searchFromEnd) ? ((getPriorData) ? ((srcLength - offset)) : ((srcLength - 1))) : ((getPriorData) ? (offset) : ((srcLength - 1))));

		/* Make sure the temp values are within the given string's buffer. */
		if ((tempRealOffset >= 0) && (tempRealOffset < srcLength) && (tempSubStrLength > 0) && ((tempRealOffset + tempSubStrLength) < srcLength))
		{
			/* Allocate memory for the substring. Using DataProcess_Reallocate_C_String(). */
			retFromCall = DataProcess_Reallocate_C_String(&tempSubStr, 0, tempSubStrLength);
			if ((retFromCall == COMMON_ERROR_SUCCESS) && (tempSubStr != NULL))
			{
				/* Copy the data. */
				memcpy(tempSubStr, (src + tempRealOffset), tempSubStrLength);

				/* Copy the pointer and data length. */
				(*subStr) = tempSubStr;
				(*subStrLength) = tempSubStrLength;

				/* Done. */
				ret = COMMON_ERROR_SUCCESS;
			}
			else
			{
				/* Could not allocate memory for substring. */
				ret = COMMON_ERROR_MEMORY_ERROR;
			}
		}
		else
		{
			/* Invalid temp vars. */
			if (tempSubStrLength <= 0)
			{
				/* No data to create substring with. */
				ret = COMMON_ERROR_END_OF_DATA;
			}
			else
			{
				/* Internal calculation error. (Could not calculate a valid offset and / or substring length.) */
				ret = COMMON_ERROR_RANGE_ERROR;
			}
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
