/*!
    Multiverse Engine Project DataProcess DataProcess_Memory_Functions.c	21/12/2015

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

#ifdef __cplusplus
}	/* End of extern "C". */
#endif	/* __cplusplus */
