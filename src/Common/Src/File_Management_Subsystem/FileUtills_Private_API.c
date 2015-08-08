/*!
    Multiverse Engine Project 08/8/2015 FileUtills FileUtills_Private_API.c

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
#include "FileUtills.h"
#include "FileUtills_Private_API.h"

int FileUtills_IsAbsolutePathReference(const char * path, const size_t pathSize)
{
	/* Call FileUtills_IsAbsolutePathReference_absRef(). */
	return (FileUtills_IsAbsolutePathReference_absRef(path, pathSize, NULL, NULL));
}

int FileUtills_IsAbsolutePathReference_absRef(const char * path, const size_t pathSize, char ** absRef, size_t * absRefLength)
{
	/* Init vars. */
	int ret = COMMON_ERROR_UNKNOWN_ERROR;		/* Result of this function. */
	char * tempAbsRef = NULL;					/* Temporary variable for construction of absRef. */

	/* Check for a valid arguments. */
	if ((path != NULL) && (pathSize > 0))
	{
		/* Check for a valid string. */
		if (path[0] == '/')	/* Posix style path. */
		{
			/* Valid Posix style path. */
			ret = FILEUTILLS_ERROR_PATH_IS_ABSOLUTE;

			/* OPTIONAL: If absRef and absRefLength are non-NULL attempt to copy the absolute path reference. */
			if ((absRef != NULL) && (absRefLength != NULL))
			{
				/* Allocate memory for absRef. */
				tempAbsRef = (char*)malloc((sizeof(char) * 2));
				if (tempAbsRef != NULL)
				{
					/* Write the data. */
					tempAbsRef[0] = '/';
					tempAbsRef[1] = '\0';

					/* Copy the pointer. */
					(*absRef) = tempAbsRef;

					/* Update the absRefSize. */
					(*absRefSize) = (sizeof(char) * 2);
				}
				else
				{
					/* Could not allocate memory. */
					ret = COMMON_ERROR_MEMORY_ERROR;

					/* Log error. */
					COMMON_LOG_VERBOSE("FileUtills_IsAbsolutePathReference(): ");
					COMMON_LOG_VERBOSE(Common_Get_Error_Message(COMMON_ERROR_MEMORY_ERROR));
					COMMON_LOG_VERBOSE(" Unable to allocate memory for absRef buffer.");
				}
			}
		}
		else
		{
			/* Check for a Windows / DOS style path. */
			if ((pathSize > 2) && (path[0] != '\0') && (path[1] == ':') && (path[2] == '\\'))
			{
				/* Valid Windows / DOS style path. */
				ret = FILEUTILLS_ERROR_PATH_IS_ABSOLUTE;

				/* OPTIONAL: If absRef and absRefLength are non-NULL attempt to copy the absolute path reference. */
				if ((absRef != NULL) && (absRefLength != NULL))
				{
					/* Allocate memory for absRef. */
					tempAbsRef = (char*)malloc((sizeof(char) * 4));
					if (tempAbsRef != NULL)
					{
						/* Write the data. */
						tempAbsRef[0] = path[0];
						tempAbsRef[1] = path[1];
						tempAbsRef[2] = path[2];
						tempAbsRef[3] = '\0';

						/* Copy the pointer. */
						(*absRef) = tempAbsRef;

						/* Update the absRefSize. */
						(*absRefSize) = (sizeof(char) * 4);
					}
					else
					{
						/* Could not allocate memory. */
						ret = COMMON_ERROR_MEMORY_ERROR;

						/* Log error. */
						COMMON_LOG_VERBOSE("FileUtills_IsAbsolutePathReference(): ");
						COMMON_LOG_VERBOSE(Common_Get_Error_Message(COMMON_ERROR_MEMORY_ERROR));
						COMMON_LOG_VERBOSE(" Unable to allocate memory for absRef buffer.");
					}
				}
			}
			else
			{
				/* Path is not absolute. */
				ret = FILEUTILLS_ERROR_PATH_IS_RELATIVE;
			}
		}
	}
	else
	{
		/* Invalid pointer. */
		ret = COMMON_ERROR_INVALID_ARGUMENT;
		COMMON_LOG_VERBOSE("FileUtills_IsAbsolutePathReference(): ");
		COMMON_LOG_VERBOSE(Common_Get_Error_Message(COMMON_ERROR_INVALID_ARGUMENT));
	}

	/* Return the result. */
	return ret;
}
