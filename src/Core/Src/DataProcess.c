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

#ifdef __cplusplus
}	/* End of extern "C". */
#endif	__cplusplus
